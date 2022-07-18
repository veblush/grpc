//
// Copyright 2020 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// Implementation of the Route Lookup Service (RLS) LB policy
//
// The policy queries a route lookup service for the name of the actual service
// to use. A child policy that recognizes the name as a field of its
// configuration will take further load balancing action on the request.

#include <grpc/support/port_platform.h>

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <deque>
#include <list>
#include <map>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/hash/hash.h"
#include "absl/memory/memory.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "absl/types/optional.h"
#include "upb/upb.h"
#include "upb/upb.hpp"

#include <grpc/byte_buffer.h>
#include <grpc/byte_buffer_reader.h>
#include <grpc/grpc.h>
#include <grpc/impl/codegen/connectivity_state.h>
#include <grpc/impl/codegen/grpc_types.h>
#include <grpc/impl/codegen/propagation_bits.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/log.h>

#include "src/core/ext/filters/client_channel/client_channel.h"
#include "src/core/ext/filters/client_channel/lb_policy.h"
#include "src/core/ext/filters/client_channel/lb_policy/child_policy_handler.h"
#include "src/core/ext/filters/client_channel/lb_policy_factory.h"
#include "src/core/ext/filters/client_channel/lb_policy_registry.h"
#include "src/core/ext/filters/client_channel/subchannel_interface.h"
#include "src/core/lib/backoff/backoff.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channelz.h"
#include "src/core/lib/config/core_configuration.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/gprpp/debug_location.h"
#include "src/core/lib/gprpp/dual_ref_counted.h"
#include "src/core/lib/gprpp/orphanable.h"
#include "src/core/lib/gprpp/ref_counted_ptr.h"
#include "src/core/lib/gprpp/sync.h"
#include "src/core/lib/gprpp/time.h"
#include "src/core/lib/gprpp/work_serializer.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/iomgr/timer.h"
#include "src/core/lib/json/json.h"
#include "src/core/lib/json/json_util.h"
#include "src/core/lib/resolver/resolver_registry.h"
#include "src/core/lib/resolver/server_address.h"
#include "src/core/lib/security/credentials/credentials.h"
#include "src/core/lib/security/credentials/fake/fake_credentials.h"
#include "src/core/lib/service_config/service_config_impl.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/slice/slice_refcount.h"
#include "src/core/lib/surface/call.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/lib/transport/error_utils.h"
#include "src/core/lib/uri/uri_parser.h"
#include "src/proto/grpc/lookup/v1/rls.upb.h"

namespace grpc_core {

TraceFlag grpc_lb_rls_trace(false, "rls_lb");

namespace {

const char* kRls = "rls_experimental";
const char kGrpc[] = "grpc";
const char* kRlsRequestPath = "/grpc.lookup.v1.RouteLookupService/RouteLookup";
const char* kFakeTargetFieldValue = "fake_target_field_value";
const char* kRlsHeaderKey = "X-Google-RLS-Data";

const Duration kDefaultLookupServiceTimeout = Duration::Seconds(10);
const Duration kMaxMaxAge = Duration::Minutes(5);
const Duration kMinExpirationTime = Duration::Seconds(5);
const Duration kCacheBackoffInitial = Duration::Seconds(1);
const double kCacheBackoffMultiplier = 1.6;
const double kCacheBackoffJitter = 0.2;
const Duration kCacheBackoffMax = Duration::Minutes(2);
const Duration kDefaultThrottleWindowSize = Duration::Seconds(30);
const double kDefaultThrottleRatioForSuccesses = 2.0;
const int kDefaultThrottlePadding = 8;
const Duration kCacheCleanupTimerInterval = Duration::Minutes(1);
const int64_t kMaxCacheSizeBytes = 5 * 1024 * 1024;

// Parsed RLS LB policy configuration.
class RlsLbConfig : public LoadBalancingPolicy::Config {
 public:
  struct KeyBuilder {
    std::map<std::string /*key*/, std::vector<std::string /*header*/>>
        header_keys;
    std::string host_key;
    std::string service_key;
    std::string method_key;
    std::map<std::string /*key*/, std::string /*value*/> constant_keys;
  };
  using KeyBuilderMap = std::unordered_map<std::string /*path*/, KeyBuilder>;

  struct RouteLookupConfig {
    KeyBuilderMap key_builder_map;
    std::string lookup_service;
    Duration lookup_service_timeout;
    Duration max_age;
    Duration stale_age;
    int64_t cache_size_bytes = 0;
    std::string default_target;
  };

  RlsLbConfig(RouteLookupConfig route_lookup_config,
              std::string rls_channel_service_config, Json child_policy_config,
              std::string child_policy_config_target_field_name,
              RefCountedPtr<LoadBalancingPolicy::Config>
                  default_child_policy_parsed_config)
      : route_lookup_config_(std::move(route_lookup_config)),
        rls_channel_service_config_(std::move(rls_channel_service_config)),
        child_policy_config_(std::move(child_policy_config)),
        child_policy_config_target_field_name_(
            std::move(child_policy_config_target_field_name)),
        default_child_policy_parsed_config_(
            std::move(default_child_policy_parsed_config)) {}

  const char* name() const override { return kRls; }

  const KeyBuilderMap& key_builder_map() const {
    return route_lookup_config_.key_builder_map;
  }
  const std::string& lookup_service() const {
    return route_lookup_config_.lookup_service;
  }
  Duration lookup_service_timeout() const {
    return route_lookup_config_.lookup_service_timeout;
  }
  Duration max_age() const { return route_lookup_config_.max_age; }
  Duration stale_age() const { return route_lookup_config_.stale_age; }
  int64_t cache_size_bytes() const {
    return route_lookup_config_.cache_size_bytes;
  }
  const std::string& default_target() const {
    return route_lookup_config_.default_target;
  }
  const std::string& rls_channel_service_config() const {
    return rls_channel_service_config_;
  }
  const Json& child_policy_config() const { return child_policy_config_; }
  const std::string& child_policy_config_target_field_name() const {
    return child_policy_config_target_field_name_;
  }
  RefCountedPtr<LoadBalancingPolicy::Config>
  default_child_policy_parsed_config() const {
    return default_child_policy_parsed_config_;
  }

 private:
  RouteLookupConfig route_lookup_config_;
  std::string rls_channel_service_config_;
  Json child_policy_config_;
  std::string child_policy_config_target_field_name_;
  RefCountedPtr<LoadBalancingPolicy::Config>
      default_child_policy_parsed_config_;
};

// RLS LB policy.
class RlsLb : public LoadBalancingPolicy {
 public:
  explicit RlsLb(Args args);

  const char* name() const override { return kRls; }
  void UpdateLocked(UpdateArgs args) override;
  void ExitIdleLocked() override;
  void ResetBackoffLocked() override;

 private:
  // Key to access entries in the cache and the request map.
  struct RequestKey {
    std::map<std::string, std::string> key_map;

    bool operator==(const RequestKey& rhs) const {
      return key_map == rhs.key_map;
    }

    template <typename H>
    friend H AbslHashValue(H h, const RequestKey& key) {
      std::hash<std::string> string_hasher;
      for (auto& kv : key.key_map) {
        h = H::combine(std::move(h), string_hasher(kv.first),
                       string_hasher(kv.second));
      }
      return h;
    }

    size_t Size() const {
      size_t size = sizeof(RequestKey);
      for (auto& kv : key_map) {
        size += kv.first.length() + kv.second.length();
      }
      return size;
    }

    std::string ToString() const {
      return absl::StrCat(
          "{", absl::StrJoin(key_map, ",", absl::PairFormatter("=")), "}");
    }
  };

  // Data from an RLS response.
  struct ResponseInfo {
    absl::Status status;
    std::vector<std::string> targets;
    std::string header_data;

    std::string ToString() const {
      return absl::StrFormat("{status=%s, targets=[%s], header_data=\"%s\"}",
                             status.ToString(), absl::StrJoin(targets, ","),
                             header_data);
    }
  };

  // Wraps a child policy for a given RLS target.
  class ChildPolicyWrapper : public DualRefCounted<ChildPolicyWrapper> {
   public:
    ChildPolicyWrapper(RefCountedPtr<RlsLb> lb_policy, std::string target);

    // Note: We are forced to disable lock analysis here because
    // Orphan() is called by OrphanablePtr<>, which cannot have lock
    // annotations for this particular caller.
    void Orphan() override ABSL_NO_THREAD_SAFETY_ANALYSIS;

    const std::string& target() const { return target_; }

    PickResult Pick(PickArgs args) ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
      return picker_->Pick(args);
    }

    // Updates for the child policy are handled in two phases:
    // 1. In StartUpdate(), we parse and validate the new child policy
    //    config and store the parsed config.
    // 2. In MaybeFinishUpdate(), we actually pass the parsed config to the
    //    child policy's UpdateLocked() method.
    //
    // The reason we do this is to avoid deadlocks.  In StartUpdate(),
    // if the new config fails to validate, then we need to set
    // picker_ to an instance that will fail all requests, which
    // requires holding the lock.  However, we cannot call the child
    // policy's UpdateLocked() method from MaybeFinishUpdate() while
    // holding the lock, since that would cause a deadlock: the child's
    // UpdateLocked() will call the helper's UpdateState() method, which
    // will try to acquire the lock to set picker_.  So StartUpdate() is
    // called while we are still holding the lock, but MaybeFinishUpdate()
    // is called after releasing it.
    //
    // Both methods grab the data they need from the parent object.
    void StartUpdate() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);
    void MaybeFinishUpdate() ABSL_LOCKS_EXCLUDED(&RlsLb::mu_);

    void ExitIdleLocked() {
      if (child_policy_ != nullptr) child_policy_->ExitIdleLocked();
    }

    void ResetBackoffLocked() {
      if (child_policy_ != nullptr) child_policy_->ResetBackoffLocked();
    }

    // Gets the connectivity state of the child policy. Once the child policy
    // reports TRANSIENT_FAILURE, the function will always return
    // TRANSIENT_FAILURE state instead of the actual state of the child policy
    // until the child policy reports another READY state.
    grpc_connectivity_state connectivity_state() const
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
      return connectivity_state_;
    }

   private:
    // ChannelControlHelper object that allows the child policy to update state
    // with the wrapper.
    class ChildPolicyHelper : public LoadBalancingPolicy::ChannelControlHelper {
     public:
      explicit ChildPolicyHelper(WeakRefCountedPtr<ChildPolicyWrapper> wrapper)
          : wrapper_(std::move(wrapper)) {}
      ~ChildPolicyHelper() override {
        wrapper_.reset(DEBUG_LOCATION, "ChildPolicyHelper");
      }

      RefCountedPtr<SubchannelInterface> CreateSubchannel(
          ServerAddress address, const ChannelArgs& args) override;
      void UpdateState(grpc_connectivity_state state,
                       const absl::Status& status,
                       std::unique_ptr<SubchannelPicker> picker) override;
      void RequestReresolution() override;
      absl::string_view GetAuthority() override;
      void AddTraceEvent(TraceSeverity severity,
                         absl::string_view message) override;

     private:
      WeakRefCountedPtr<ChildPolicyWrapper> wrapper_;
    };

    RefCountedPtr<RlsLb> lb_policy_;
    std::string target_;

    bool is_shutdown_ = false;

    OrphanablePtr<ChildPolicyHandler> child_policy_;
    RefCountedPtr<LoadBalancingPolicy::Config> pending_config_;

    grpc_connectivity_state connectivity_state_ ABSL_GUARDED_BY(&RlsLb::mu_) =
        GRPC_CHANNEL_IDLE;
    std::unique_ptr<LoadBalancingPolicy::SubchannelPicker> picker_
        ABSL_GUARDED_BY(&RlsLb::mu_);
  };

  // A picker that uses the cache and the request map in the LB policy
  // (synchronized via a mutex) to determine how to route requests.
  class Picker : public LoadBalancingPolicy::SubchannelPicker {
   public:
    explicit Picker(RefCountedPtr<RlsLb> lb_policy);
    ~Picker() override;

    PickResult Pick(PickArgs args) override;

   private:
    RefCountedPtr<RlsLb> lb_policy_;
    RefCountedPtr<RlsLbConfig> config_;
    RefCountedPtr<ChildPolicyWrapper> default_child_policy_;
  };

  // An LRU cache with adjustable size.
  class Cache {
   public:
    using Iterator = std::list<RequestKey>::iterator;

    class Entry : public InternallyRefCounted<Entry> {
     public:
      Entry(RefCountedPtr<RlsLb> lb_policy, const RequestKey& key);

      // Notify the entry when it's evicted from the cache. Performs shut down.
      // Note: We are forced to disable lock analysis here because
      // Orphan() is called by OrphanablePtr<>, which cannot have lock
      // annotations for this particular caller.
      void Orphan() override ABSL_NO_THREAD_SAFETY_ANALYSIS;

      const absl::Status& status() const
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        return status_;
      }
      Timestamp backoff_time() const
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        return backoff_time_;
      }
      Timestamp backoff_expiration_time() const
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        return backoff_expiration_time_;
      }
      Timestamp data_expiration_time() const
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        return data_expiration_time_;
      }
      const std::string& header_data() const
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        return header_data_;
      }
      Timestamp stale_time() const ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        return stale_time_;
      }
      Timestamp min_expiration_time() const
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        return min_expiration_time_;
      }

      std::unique_ptr<BackOff> TakeBackoffState()
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        return std::move(backoff_state_);
      }

      // Cache size of entry.
      size_t Size() const ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

      // Pick subchannel for request based on the entry's state.
      PickResult Pick(PickArgs args) ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

      // If the cache entry is in backoff state, resets the backoff and, if
      // applicable, its backoff timer. The method does not update the LB
      // policy's picker; the caller is responsible for that if necessary.
      void ResetBackoff() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

      // Check if the entry should be removed by the clean-up timer.
      bool ShouldRemove() const ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

      // Check if the entry can be evicted from the cache, i.e. the
      // min_expiration_time_ has passed.
      bool CanEvict() const ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

      // Updates the entry upon reception of a new RLS response.
      // Returns a list of child policy wrappers on which FinishUpdate()
      // needs to be called after releasing the lock.
      std::vector<ChildPolicyWrapper*> OnRlsResponseLocked(
          ResponseInfo response, std::unique_ptr<BackOff> backoff_state)
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

      // Moves entry to the end of the LRU list.
      void MarkUsed() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

     private:
      class BackoffTimer : public InternallyRefCounted<BackoffTimer> {
       public:
        BackoffTimer(RefCountedPtr<Entry> entry, Timestamp backoff_time);

        // Note: We are forced to disable lock analysis here because
        // Orphan() is called by OrphanablePtr<>, which cannot have lock
        // annotations for this particular caller.
        void Orphan() override ABSL_NO_THREAD_SAFETY_ANALYSIS;

       private:
        static void OnBackoffTimer(void* args, absl::Status error);

        RefCountedPtr<Entry> entry_;
        bool armed_ ABSL_GUARDED_BY(&RlsLb::mu_) = true;
        grpc_timer backoff_timer_;
        grpc_closure backoff_timer_callback_;
      };

      RefCountedPtr<RlsLb> lb_policy_;

      bool is_shutdown_ ABSL_GUARDED_BY(&RlsLb::mu_) = false;

      // Backoff states
      absl::Status status_ ABSL_GUARDED_BY(&RlsLb::mu_);
      std::unique_ptr<BackOff> backoff_state_ ABSL_GUARDED_BY(&RlsLb::mu_);
      Timestamp backoff_time_ ABSL_GUARDED_BY(&RlsLb::mu_) =
          Timestamp::InfPast();
      Timestamp backoff_expiration_time_ ABSL_GUARDED_BY(&RlsLb::mu_) =
          Timestamp::InfPast();
      OrphanablePtr<BackoffTimer> backoff_timer_;

      // RLS response states
      std::vector<RefCountedPtr<ChildPolicyWrapper>> child_policy_wrappers_
          ABSL_GUARDED_BY(&RlsLb::mu_);
      std::string header_data_ ABSL_GUARDED_BY(&RlsLb::mu_);
      Timestamp data_expiration_time_ ABSL_GUARDED_BY(&RlsLb::mu_) =
          Timestamp::InfPast();
      Timestamp stale_time_ ABSL_GUARDED_BY(&RlsLb::mu_) = Timestamp::InfPast();

      Timestamp min_expiration_time_ ABSL_GUARDED_BY(&RlsLb::mu_);
      Cache::Iterator lru_iterator_ ABSL_GUARDED_BY(&RlsLb::mu_);
    };

    explicit Cache(RlsLb* lb_policy);

    // Finds an entry from the cache that corresponds to a key. If an entry is
    // not found, nullptr is returned. Otherwise, the entry is considered
    // recently used and its order in the LRU list of the cache is updated.
    Entry* Find(const RequestKey& key)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    // Finds an entry from the cache that corresponds to a key. If an entry is
    // not found, an entry is created, inserted in the cache, and returned to
    // the caller. Otherwise, the entry found is returned to the caller. The
    // entry returned to the user is considered recently used and its order in
    // the LRU list of the cache is updated.
    Entry* FindOrInsert(const RequestKey& key)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    // Resizes the cache. If the new cache size is greater than the current size
    // of the cache, do nothing. Otherwise, evict the oldest entries that
    // exceed the new size limit of the cache.
    void Resize(size_t bytes) ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    // Resets backoff of all the cache entries.
    void ResetAllBackoff() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    // Shutdown the cache; clean-up and orphan all the stored cache entries.
    void Shutdown() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

   private:
    static void OnCleanupTimer(void* arg, absl::Status error);

    // Returns the entry size for a given key.
    static size_t EntrySizeForKey(const RequestKey& key);

    // Evicts oversized cache elements when the current size is greater than
    // the specified limit.
    void MaybeShrinkSize(size_t bytes)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    RlsLb* lb_policy_;

    size_t size_limit_ ABSL_GUARDED_BY(&RlsLb::mu_) = 0;
    size_t size_ ABSL_GUARDED_BY(&RlsLb::mu_) = 0;

    std::list<RequestKey> lru_list_ ABSL_GUARDED_BY(&RlsLb::mu_);
    std::unordered_map<RequestKey, OrphanablePtr<Entry>, absl::Hash<RequestKey>>
        map_ ABSL_GUARDED_BY(&RlsLb::mu_);
    grpc_timer cleanup_timer_;
    grpc_closure timer_callback_;
  };

  // Channel for communicating with the RLS server.
  // Contains throttling logic for RLS requests.
  class RlsChannel : public InternallyRefCounted<RlsChannel> {
   public:
    explicit RlsChannel(RefCountedPtr<RlsLb> lb_policy);

    // Shuts down the channel.
    void Orphan() override;

    // Starts an RLS call.
    // If stale_entry is non-null, it points to the entry containing
    // stale data for the key.
    void StartRlsCall(const RequestKey& key, Cache::Entry* stale_entry)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    // Reports the result of an RLS call to the throttle.
    void ReportResponseLocked(bool response_succeeded)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    // Checks if a proposed RLS call should be throttled.
    bool ShouldThrottle() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
      return throttle_.ShouldThrottle();
    }

    // Resets the channel's backoff.
    void ResetBackoff();

    grpc_channel* channel() const { return channel_; }

   private:
    // Watches the state of the RLS channel. Notifies the LB policy when
    // the channel was previously in TRANSIENT_FAILURE and then becomes READY.
    class StateWatcher : public AsyncConnectivityStateWatcherInterface {
     public:
      explicit StateWatcher(RefCountedPtr<RlsChannel> rls_channel)
          : AsyncConnectivityStateWatcherInterface(
                rls_channel->lb_policy_->work_serializer()),
            rls_channel_(std::move(rls_channel)) {}

     private:
      void OnConnectivityStateChange(grpc_connectivity_state new_state,
                                     const absl::Status& status) override;

      RefCountedPtr<RlsChannel> rls_channel_;
      bool was_transient_failure_ = false;
    };

    // Throttle state for RLS requests.
    class Throttle {
     public:
      explicit Throttle(
          Duration window_size = kDefaultThrottleWindowSize,
          float ratio_for_successes = kDefaultThrottleRatioForSuccesses,
          int padding = kDefaultThrottlePadding)
          : window_size_(window_size),
            ratio_for_successes_(ratio_for_successes),
            padding_(padding) {}

      bool ShouldThrottle() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

      void RegisterResponse(bool success)
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

     private:
      Duration window_size_;
      double ratio_for_successes_;
      int padding_;
      std::mt19937 rng_{std::random_device()()};

      // Logged timestamp of requests.
      std::deque<Timestamp> requests_ ABSL_GUARDED_BY(&RlsLb::mu_);

      // Logged timestamps of failures.
      std::deque<Timestamp> failures_ ABSL_GUARDED_BY(&RlsLb::mu_);
    };

    RefCountedPtr<RlsLb> lb_policy_;
    bool is_shutdown_ = false;

    grpc_channel* channel_ = nullptr;
    RefCountedPtr<channelz::ChannelNode> parent_channelz_node_;
    StateWatcher* watcher_ = nullptr;
    Throttle throttle_ ABSL_GUARDED_BY(&RlsLb::mu_);
  };

  // A pending RLS request.  Instances will be tracked in request_map_.
  class RlsRequest : public InternallyRefCounted<RlsRequest> {
   public:
    // Asynchronously starts a call on rls_channel for key.
    // Stores backoff_state, which will be transferred to the data cache
    // if the RLS request fails.
    RlsRequest(RefCountedPtr<RlsLb> lb_policy, RlsLb::RequestKey key,
               RefCountedPtr<RlsChannel> rls_channel,
               std::unique_ptr<BackOff> backoff_state,
               grpc_lookup_v1_RouteLookupRequest_Reason reason,
               std::string stale_header_data);
    ~RlsRequest() override;

    // Shuts down the request.  If the request is still in flight, it is
    // cancelled, in which case no response will be added to the cache.
    void Orphan() override;

   private:
    // Callback to be invoked to start the call.
    static void StartCall(void* arg, absl::Status error);

    // Helper for StartCall() that runs within the WorkSerializer.
    void StartCallLocked();

    // Callback to be invoked when the call is completed.
    static void OnRlsCallComplete(void* arg, absl::Status error);

    // Call completion callback running on LB policy WorkSerializer.
    void OnRlsCallCompleteLocked(absl::Status error);

    grpc_byte_buffer* MakeRequestProto();
    ResponseInfo ParseResponseProto();

    RefCountedPtr<RlsLb> lb_policy_;
    RlsLb::RequestKey key_;
    RefCountedPtr<RlsChannel> rls_channel_;
    std::unique_ptr<BackOff> backoff_state_;
    grpc_lookup_v1_RouteLookupRequest_Reason reason_;
    std::string stale_header_data_;

    // RLS call state.
    Timestamp deadline_;
    grpc_closure call_start_cb_;
    grpc_closure call_complete_cb_;
    grpc_call* call_ = nullptr;
    grpc_byte_buffer* send_message_ = nullptr;
    grpc_metadata_array recv_initial_metadata_;
    grpc_byte_buffer* recv_message_ = nullptr;
    grpc_metadata_array recv_trailing_metadata_;
    grpc_status_code status_recv_;
    grpc_slice status_details_recv_;
  };

  void ShutdownLocked() override;

  // Returns a new picker to the channel to trigger reprocessing of
  // pending picks.  Schedules the actual picker update on the ExecCtx
  // to be run later, so it's safe to invoke this while holding the lock.
  void UpdatePickerAsync();
  // Hops into work serializer and calls UpdatePickerLocked().
  static void UpdatePickerCallback(void* arg, absl::Status error);
  // Updates the picker in the work serializer.
  void UpdatePickerLocked() ABSL_LOCKS_EXCLUDED(&mu_);

  // The name of the server for the channel.
  std::string server_name_;

  // Mutex to guard LB policy state that is accessed by the picker.
  Mutex mu_;
  bool is_shutdown_ ABSL_GUARDED_BY(mu_) = false;
  bool update_in_progress_ = false;
  Cache cache_ ABSL_GUARDED_BY(mu_);
  // Maps an RLS request key to an RlsRequest object that represents a pending
  // RLS request.
  std::unordered_map<RequestKey, OrphanablePtr<RlsRequest>,
                     absl::Hash<RequestKey>>
      request_map_ ABSL_GUARDED_BY(mu_);
  // The channel on which RLS requests are sent.
  // Note that this channel may be swapped out when the RLS policy gets
  // an update.  However, when that happens, any existing entries in
  // request_map_ will continue to use the previous channel.
  OrphanablePtr<RlsChannel> rls_channel_ ABSL_GUARDED_BY(mu_);

  // Accessed only from within WorkSerializer.
  absl::StatusOr<ServerAddressList> addresses_;
  ChannelArgs channel_args_;
  RefCountedPtr<RlsLbConfig> config_;
  RefCountedPtr<ChildPolicyWrapper> default_child_policy_;
  std::map<std::string /*target*/, ChildPolicyWrapper*> child_policy_map_;
};

//
// RlsLb::ChildPolicyWrapper
//

RlsLb::ChildPolicyWrapper::ChildPolicyWrapper(RefCountedPtr<RlsLb> lb_policy,
                                              std::string target)
    : DualRefCounted<ChildPolicyWrapper>(
          GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace) ? "ChildPolicyWrapper"
                                                     : nullptr),
      lb_policy_(lb_policy),
      target_(std::move(target)),
      picker_(absl::make_unique<QueuePicker>(std::move(lb_policy))) {
  lb_policy_->child_policy_map_.emplace(target_, this);
}

void RlsLb::ChildPolicyWrapper::Orphan() {
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO, "[rlslb %p] ChildPolicyWrapper=%p [%s]: shutdown",
            lb_policy_.get(), this, target_.c_str());
  }
  is_shutdown_ = true;
  lb_policy_->child_policy_map_.erase(target_);
  if (child_policy_ != nullptr) {
    grpc_pollset_set_del_pollset_set(child_policy_->interested_parties(),
                                     lb_policy_->interested_parties());
    child_policy_.reset();
  }
  picker_.reset();
}

absl::Status InsertOrUpdateChildPolicyField(const std::string& field,
                                                 const std::string& value,
                                                 Json* config) {
  if (config->type() != Json::Type::ARRAY) {
    return GRPC_ERROR_CREATE_FROM_STATIC_STRING(
        "child policy configuration is not an array");
  }
  std::vector<absl::Status> error_list;
  for (Json& child_json : *config->mutable_array()) {
    if (child_json.type() != Json::Type::OBJECT) {
      error_list.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
          "child policy item is not an object"));
    } else {
      Json::Object& child = *child_json.mutable_object();
      if (child.size() != 1) {
        error_list.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
            "child policy item contains more than one field"));
      } else {
        Json& child_config_json = child.begin()->second;
        if (child_config_json.type() != Json::Type::OBJECT) {
          error_list.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
              "child policy item config is not an object"));
        } else {
          Json::Object& child_config = *child_config_json.mutable_object();
          child_config[field] = Json(value);
        }
      }
    }
  }
  return GRPC_ERROR_CREATE_FROM_VECTOR_AND_CPP_STRING(
      absl::StrCat("errors when inserting field \"", field,
                   "\" for child policy"),
      &error_list);
}

void RlsLb::ChildPolicyWrapper::StartUpdate() {
  Json child_policy_config = lb_policy_->config_->child_policy_config();
  absl::Status error = InsertOrUpdateChildPolicyField(
      lb_policy_->config_->child_policy_config_target_field_name(), target_,
      &child_policy_config);
  GPR_ASSERT(error.ok());
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(
        GPR_INFO,
        "[rlslb %p] ChildPolicyWrapper=%p [%s]: validating update, config: %s",
        lb_policy_.get(), this, target_.c_str(),
        child_policy_config.Dump().c_str());
  }
  pending_config_ = LoadBalancingPolicyRegistry::ParseLoadBalancingConfig(
      child_policy_config, &error);
  // Returned RLS target fails the validation.
  if (!error.ok()) {
    if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
      gpr_log(GPR_INFO,
              "[rlslb %p] ChildPolicyWrapper=%p [%s]: config failed to parse: "
              "%s; config: %s",
              lb_policy_.get(), this, target_.c_str(),
              grpc_error_std_string(error).c_str(),
              child_policy_config.Dump().c_str());
    }
    pending_config_.reset();
    picker_ = absl::make_unique<TransientFailurePicker>(
        grpc_error_to_absl_status(error));
    child_policy_.reset();
  }
}

void RlsLb::ChildPolicyWrapper::MaybeFinishUpdate() {
  // If pending_config_ is not set, that means StartUpdate() failed, so
  // there's nothing to do here.
  if (pending_config_ == nullptr) return;
  // If child policy doesn't yet exist, create it.
  if (child_policy_ == nullptr) {
    Args create_args;
    create_args.work_serializer = lb_policy_->work_serializer();
    create_args.channel_control_helper = absl::make_unique<ChildPolicyHelper>(
        WeakRef(DEBUG_LOCATION, "ChildPolicyHelper"));
    create_args.args = lb_policy_->channel_args_;
    child_policy_ = MakeOrphanable<ChildPolicyHandler>(std::move(create_args),
                                                       &grpc_lb_rls_trace);
    if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
      gpr_log(GPR_INFO,
              "[rlslb %p] ChildPolicyWrapper=%p [%s], created new child policy "
              "handler %p",
              lb_policy_.get(), this, target_.c_str(), child_policy_.get());
    }
    grpc_pollset_set_add_pollset_set(child_policy_->interested_parties(),
                                     lb_policy_->interested_parties());
  }
  // Send the child the updated config.
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO,
            "[rlslb %p] ChildPolicyWrapper=%p [%s], updating child policy "
            "handler %p",
            lb_policy_.get(), this, target_.c_str(), child_policy_.get());
  }
  UpdateArgs update_args;
  update_args.config = std::move(pending_config_);
  update_args.addresses = lb_policy_->addresses_;
  update_args.args = lb_policy_->channel_args_;
  child_policy_->UpdateLocked(std::move(update_args));
}

//
// RlsLb::ChildPolicyWrapper::ChildPolicyHelper
//

RefCountedPtr<SubchannelInterface>
RlsLb::ChildPolicyWrapper::ChildPolicyHelper::CreateSubchannel(
    ServerAddress address, const ChannelArgs& args) {
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO,
            "[rlslb %p] ChildPolicyWrapper=%p [%s] ChildPolicyHelper=%p: "
            "CreateSubchannel() for %s",
            wrapper_->lb_policy_.get(), wrapper_.get(),
            wrapper_->target_.c_str(), this, address.ToString().c_str());
  }
  if (wrapper_->is_shutdown_) return nullptr;
  return wrapper_->lb_policy_->channel_control_helper()->CreateSubchannel(
      std::move(address), args);
}

void RlsLb::ChildPolicyWrapper::ChildPolicyHelper::UpdateState(
    grpc_connectivity_state state, const absl::Status& status,
    std::unique_ptr<SubchannelPicker> picker) {
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO,
            "[rlslb %p] ChildPolicyWrapper=%p [%s] ChildPolicyHelper=%p: "
            "UpdateState(state=%s, status=%s, picker=%p)",
            wrapper_->lb_policy_.get(), wrapper_.get(),
            wrapper_->target_.c_str(), this, ConnectivityStateName(state),
            status.ToString().c_str(), picker.get());
  }
  {
    MutexLock lock(&wrapper_->lb_policy_->mu_);
    if (wrapper_->is_shutdown_) return;
    if (wrapper_->connectivity_state_ == GRPC_CHANNEL_TRANSIENT_FAILURE &&
        state != GRPC_CHANNEL_READY) {
      return;
    }
    wrapper_->connectivity_state_ = state;
    GPR_DEBUG_ASSERT(picker != nullptr);
    if (picker != nullptr) {
      wrapper_->picker_ = std::move(picker);
    }
  }
  wrapper_->lb_policy_->UpdatePickerLocked();
}

void RlsLb::ChildPolicyWrapper::ChildPolicyHelper::RequestReresolution() {
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO,
            "[rlslb %p] ChildPolicyWrapper=%p [%s] ChildPolicyHelper=%p: "
            "RequestReresolution",
            wrapper_->lb_policy_.get(), wrapper_.get(),
            wrapper_->target_.c_str(), this);
  }
  if (wrapper_->is_shutdown_) return;
  wrapper_->lb_policy_->channel_control_helper()->RequestReresolution();
}

absl::string_view RlsLb::ChildPolicyWrapper::ChildPolicyHelper::GetAuthority() {
  return wrapper_->lb_policy_->channel_control_helper()->GetAuthority();
}

void RlsLb::ChildPolicyWrapper::ChildPolicyHelper::AddTraceEvent(
    TraceSeverity severity, absl::string_view message) {
  if (wrapper_->is_shutdown_) return;
  wrapper_->lb_policy_->channel_control_helper()->AddTraceEvent(severity,
                                                                message);
}

//
// RlsLb::Picker
//

// Builds the key to be used for a request based on path and initial_metadata.
std::map<std::string, std::string> BuildKeyMap(
    const RlsLbConfig::KeyBuilderMap& key_builder_map, absl::string_view path,
    const std::string& host,
    const LoadBalancingPolicy::MetadataInterface* initial_metadata) {
  size_t last_slash_pos = path.npos;  // May need this a few times, so cache it.
  // Find key builder for this path.
  auto it = key_builder_map.find(std::string(path));
  if (it == key_builder_map.end()) {
    // Didn't find exact match, try method wildcard.
    last_slash_pos = path.rfind("/");
    GPR_DEBUG_ASSERT(last_slash_pos != path.npos);
    if (GPR_UNLIKELY(last_slash_pos == path.npos)) return {};
    std::string service(path.substr(0, last_slash_pos + 1));
    it = key_builder_map.find(service);
    if (it == key_builder_map.end()) return {};
  }
  const RlsLbConfig::KeyBuilder* key_builder = &it->second;
  // Construct key map using key builder.
  std::map<std::string, std::string> key_map;
  // Add header keys.
  for (const auto& p : key_builder->header_keys) {
    const std::string& key = p.first;
    const std::vector<std::string>& header_names = p.second;
    for (const std::string& header_name : header_names) {
      std::string buffer;
      absl::optional<absl::string_view> value =
          initial_metadata->Lookup(header_name, &buffer);
      if (value.has_value()) {
        key_map[key] = std::string(*value);
        break;
      }
    }
  }
  // Add constant keys.
  key_map.insert(key_builder->constant_keys.begin(),
                 key_builder->constant_keys.end());
  // Add host key.
  if (!key_builder->host_key.empty()) {
    key_map[key_builder->host_key] = host;
  }
  // Add service key.
  if (!key_builder->service_key.empty()) {
    if (last_slash_pos == path.npos) {
      last_slash_pos = path.rfind("/");
      GPR_DEBUG_ASSERT(last_slash_pos != path.npos);
      if (GPR_UNLIKELY(last_slash_pos == path.npos)) return {};
    }
    key_map[key_builder->service_key] =
        std::string(path.substr(1, last_slash_pos - 1));
  }
  // Add method key.
  if (!key_builder->method_key.empty()) {
    if (last_slash_pos == path.npos) {
      last_slash_pos = path.rfind("/");
      GPR_DEBUG_ASSERT(last_slash_pos != path.npos);
      if (GPR_UNLIKELY(last_slash_pos == path.npos)) return {};
    }
    key_map[key_builder->method_key] =
        std::string(path.substr(last_slash_pos + 1));
  }
  return key_map;
}

RlsLb::Picker::Picker(RefCountedPtr<RlsLb> lb_policy)
    : lb_policy_(std::move(lb_policy)), config_(lb_policy_->config_) {
  if (lb_policy_->default_child_policy_ != nullptr) {
    default_child_policy_ =
        lb_policy_->default_child_policy_->Ref(DEBUG_LOCATION, "Picker");
  }
}

RlsLb::Picker::~Picker() {
  // It's not safe to unref the default child policy in the picker,
  // since that needs to be done in the WorkSerializer.
  if (default_child_policy_ != nullptr) {
    auto* default_child_policy = default_child_policy_.release();
    lb_policy_->work_serializer()->Run(
        [default_child_policy]() {
          default_child_policy->Unref(DEBUG_LOCATION, "Picker");
        },
        DEBUG_LOCATION);
  }
}

LoadBalancingPolicy::PickResult RlsLb::Picker::Pick(PickArgs args) {
  // Construct key for request.
  RequestKey key = {BuildKeyMap(config_->key_builder_map(), args.path,
                                lb_policy_->server_name_,
                                args.initial_metadata)};
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO, "[rlslb %p] picker=%p: request keys: %s",
            lb_policy_.get(), this, key.ToString().c_str());
  }
  Timestamp now = ExecCtx::Get()->Now();
  MutexLock lock(&lb_policy_->mu_);
  if (lb_policy_->is_shutdown_) {
    return PickResult::Fail(
        absl::UnavailableError("LB policy already shut down"));
  }
  // Check if there's a cache entry.
  Cache::Entry* entry = lb_policy_->cache_.Find(key);
  // If there is no cache entry, or if the cache entry is not in backoff
  // and has a stale time in the past, and there is not already a
  // pending RLS request for this key, then try to start a new RLS request.
  if ((entry == nullptr ||
       (entry->stale_time() < now && entry->backoff_time() < now)) &&
      lb_policy_->request_map_.find(key) == lb_policy_->request_map_.end()) {
    // Check if requests are being throttled.
    if (lb_policy_->rls_channel_->ShouldThrottle()) {
      // Request is throttled.
      // If there is no non-expired data in the cache, then we use the
      // default target if set, or else we fail the pick.
      if (entry == nullptr || entry->data_expiration_time() < now) {
        if (default_child_policy_ != nullptr) {
          if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
            gpr_log(GPR_INFO,
                    "[rlslb %p] picker=%p: RLS call throttled; "
                    "using default target",
                    lb_policy_.get(), this);
          }
          return default_child_policy_->Pick(args);
        }
        if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
          gpr_log(GPR_INFO,
                  "[rlslb %p] picker=%p: RLS call throttled; failing pick",
                  lb_policy_.get(), this);
        }
        return PickResult::Fail(
            absl::UnavailableError("RLS request throttled"));
      }
    }
    // Start the RLS call.
    lb_policy_->rls_channel_->StartRlsCall(
        key, (entry == nullptr || entry->data_expiration_time() < now) ? nullptr
                                                                       : entry);
  }
  // If the cache entry exists, see if it has usable data.
  if (entry != nullptr) {
    // If the entry has non-expired data, use it.
    if (entry->data_expiration_time() >= now) {
      if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
        gpr_log(GPR_INFO, "[rlslb %p] picker=%p: using cache entry %p",
                lb_policy_.get(), this, entry);
      }
      return entry->Pick(args);
    }
    // If the entry is in backoff, then use the default target if set,
    // or else fail the pick.
    if (entry->backoff_time() >= now) {
      if (default_child_policy_ != nullptr) {
        if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
          gpr_log(
              GPR_INFO,
              "[rlslb %p] picker=%p: RLS call in backoff; using default target",
              lb_policy_.get(), this);
        }
        return default_child_policy_->Pick(args);
      }
      if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
        gpr_log(GPR_INFO,
                "[rlslb %p] picker=%p: RLS call in backoff; failing pick",
                lb_policy_.get(), this);
      }
      return PickResult::Fail(absl::UnavailableError(
          absl::StrCat("RLS request failed: ", entry->status().ToString())));
    }
  }
  // RLS call pending.  Queue the pick.
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO, "[rlslb %p] picker=%p: RLS request pending; queuing pick",
            lb_policy_.get(), this);
  }
  return PickResult::Queue();
}

//
// RlsLb::Cache::Entry::BackoffTimer
//

RlsLb::Cache::Entry::BackoffTimer::BackoffTimer(RefCountedPtr<Entry> entry,
                                                Timestamp backoff_time)
    : entry_(std::move(entry)) {
  GRPC_CLOSURE_INIT(&backoff_timer_callback_, OnBackoffTimer, this, nullptr);
  Ref(DEBUG_LOCATION, "BackoffTimer").release();
  grpc_timer_init(&backoff_timer_, backoff_time, &backoff_timer_callback_);
}

void RlsLb::Cache::Entry::BackoffTimer::Orphan() {
  if (armed_) {
    armed_ = false;
    grpc_timer_cancel(&backoff_timer_);
  }
  Unref(DEBUG_LOCATION, "Orphan");
}

void RlsLb::Cache::Entry::BackoffTimer::OnBackoffTimer(
    void* arg, absl::Status /*error*/) {
  auto* self = static_cast<BackoffTimer*>(arg);
  self->entry_->lb_policy_->work_serializer()->Run(
      [self]() {
        RefCountedPtr<BackoffTimer> backoff_timer(self);
        {
          MutexLock lock(&self->entry_->lb_policy_->mu_);
          if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
            gpr_log(GPR_INFO,
                    "[rlslb %p] cache entry=%p %s, armed_=%d: "
                    "backoff timer fired",
                    self->entry_->lb_policy_.get(), self->entry_.get(),
                    self->entry_->is_shutdown_
                        ? "(shut down)"
                        : self->entry_->lru_iterator_->ToString().c_str(),
                    self->armed_);
          }
          bool cancelled = !self->armed_;
          self->armed_ = false;
          if (cancelled) return;
        }
        // The pick was in backoff state and there could be a pick queued if
        // wait_for_ready is true. We'll update the picker for that case.
        self->entry_->lb_policy_->UpdatePickerLocked();
      },
      DEBUG_LOCATION);
}

//
// RlsLb::Cache::Entry
//

std::unique_ptr<BackOff> MakeCacheEntryBackoff() {
  return absl::make_unique<BackOff>(
      BackOff::Options()
          .set_initial_backoff(kCacheBackoffInitial)
          .set_multiplier(kCacheBackoffMultiplier)
          .set_jitter(kCacheBackoffJitter)
          .set_max_backoff(kCacheBackoffMax));
}

RlsLb::Cache::Entry::Entry(RefCountedPtr<RlsLb> lb_policy,
                           const RequestKey& key)
    : InternallyRefCounted<Entry>(
          GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace) ? "CacheEntry" : nullptr),
      lb_policy_(std::move(lb_policy)),
      backoff_state_(MakeCacheEntryBackoff()),
      min_expiration_time_(ExecCtx::Get()->Now() + kMinExpirationTime),
      lru_iterator_(lb_policy_->cache_.lru_list_.insert(
          lb_policy_->cache_.lru_list_.end(), key)) {}

void RlsLb::Cache::Entry::Orphan() {
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO, "[rlslb %p] cache entry=%p %s: cache entry evicted",
            lb_policy_.get(), this, lru_iterator_->ToString().c_str());
  }
  is_shutdown_ = true;
  lb_policy_->cache_.lru_list_.erase(lru_iterator_);
  lru_iterator_ = lb_policy_->cache_.lru_list_.end();  // Just in case.
  backoff_state_.reset();
  if (backoff_timer_ != nullptr) {
    backoff_timer_.reset();
    lb_policy_->UpdatePickerAsync();
  }
  child_policy_wrappers_.clear();
  Unref(DEBUG_LOCATION, "Orphan");
}

size_t RlsLb::Cache::Entry::Size() const {
  // lru_iterator_ is not valid once we're shut down.
  GPR_ASSERT(!is_shutdown_);
  return lb_policy_->cache_.EntrySizeForKey(*lru_iterator_);
}

LoadBalancingPolicy::PickResult RlsLb::Cache::Entry::Pick(PickArgs args) {
  size_t i = 0;
  ChildPolicyWrapper* child_policy_wrapper = nullptr;
  // Skip targets before the last one that are in state TRANSIENT_FAILURE.
  for (; i < child_policy_wrappers_.size(); ++i) {
    child_policy_wrapper = child_policy_wrappers_[i].get();
    if (child_policy_wrapper->connectivity_state() ==
            GRPC_CHANNEL_TRANSIENT_FAILURE &&
        i < child_policy_wrappers_.size() - 1) {
      if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
        gpr_log(GPR_INFO,
                "[rlslb %p] cache entry=%p %s: target %s (%" PRIuPTR
                " of %" PRIuPTR ") in state TRANSIENT_FAILURE; skipping",
                lb_policy_.get(), this, lru_iterator_->ToString().c_str(),
                child_policy_wrapper->target().c_str(), i,
                child_policy_wrappers_.size());
      }
      continue;
    }
    break;
  }
  // Child policy not in TRANSIENT_FAILURE or is the last target in
  // the list, so delegate.
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO,
            "[rlslb %p] cache entry=%p %s: target %s (%" PRIuPTR " of %" PRIuPTR
            ") in state %s; delegating",
            lb_policy_.get(), this, lru_iterator_->ToString().c_str(),
            child_policy_wrapper->target().c_str(), i,
            child_policy_wrappers_.size(),
            ConnectivityStateName(child_policy_wrapper->connectivity_state()));
  }
  // Add header data.
  // Note that even if the target we're using is in TRANSIENT_FAILURE,
  // the pick might still succeed (e.g., if the child is ring_hash), so
  // we need to pass the right header info down in all cases.
  if (!header_data_.empty()) {
    char* copied_header_data =
        static_cast<char*>(args.call_state->Alloc(header_data_.length() + 1));
    strcpy(copied_header_data, header_data_.c_str());
    args.initial_metadata->Add(kRlsHeaderKey, copied_header_data);
  }
  return child_policy_wrapper->Pick(args);
}

void RlsLb::Cache::Entry::ResetBackoff() {
  backoff_time_ = Timestamp::InfPast();
  backoff_timer_.reset();
}

bool RlsLb::Cache::Entry::ShouldRemove() const {
  Timestamp now = ExecCtx::Get()->Now();
  return data_expiration_time_ < now && backoff_expiration_time_ < now;
}

bool RlsLb::Cache::Entry::CanEvict() const {
  Timestamp now = ExecCtx::Get()->Now();
  return min_expiration_time_ < now;
}

void RlsLb::Cache::Entry::MarkUsed() {
  auto& lru_list = lb_policy_->cache_.lru_list_;
  auto new_it = lru_list.insert(lru_list.end(), *lru_iterator_);
  lru_list.erase(lru_iterator_);
  lru_iterator_ = new_it;
}

std::vector<RlsLb::ChildPolicyWrapper*>
RlsLb::Cache::Entry::OnRlsResponseLocked(
    ResponseInfo response, std::unique_ptr<BackOff> backoff_state) {
  // Move the entry to the end of the LRU list.
  MarkUsed();
  // If the request failed, store the failed status and update the
  // backoff state.
  if (!response.status.ok()) {
    status_ = response.status;
    if (backoff_state != nullptr) {
      backoff_state_ = std::move(backoff_state);
    } else {
      backoff_state_ = MakeCacheEntryBackoff();
    }
    backoff_time_ = backoff_state_->NextAttemptTime();
    Timestamp now = ExecCtx::Get()->Now();
    backoff_expiration_time_ = now + (backoff_time_ - now) * 2;
    backoff_timer_ = MakeOrphanable<BackoffTimer>(
        Ref(DEBUG_LOCATION, "BackoffTimer"), backoff_time_);
    lb_policy_->UpdatePickerAsync();
    return {};
  }
  // Request succeeded, so store the result.
  header_data_ = std::move(response.header_data);
  Timestamp now = ExecCtx::Get()->Now();
  data_expiration_time_ = now + lb_policy_->config_->max_age();
  stale_time_ = now + lb_policy_->config_->stale_age();
  status_ = absl::OkStatus();
  backoff_state_.reset();
  backoff_time_ = Timestamp::InfPast();
  backoff_expiration_time_ = Timestamp::InfPast();
  // Check if we need to update this list of targets.
  bool targets_changed = [&]() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
    if (child_policy_wrappers_.size() != response.targets.size()) return true;
    for (size_t i = 0; i < response.targets.size(); ++i) {
      if (child_policy_wrappers_[i]->target() != response.targets[i]) {
        return true;
      }
    }
    return false;
  }();
  if (!targets_changed) {
    // Targets didn't change, so we're not updating the list of child
    // policies.  Return a new picker so that any queued requests can be
    // re-processed.
    lb_policy_->UpdatePickerAsync();
    return {};
  }
  // Target list changed, so update it.
  std::set<absl::string_view> old_targets;
  for (RefCountedPtr<ChildPolicyWrapper>& child_policy_wrapper :
       child_policy_wrappers_) {
    old_targets.emplace(child_policy_wrapper->target());
  }
  bool update_picker = false;
  std::vector<ChildPolicyWrapper*> child_policies_to_finish_update;
  std::vector<RefCountedPtr<ChildPolicyWrapper>> new_child_policy_wrappers;
  new_child_policy_wrappers.reserve(response.targets.size());
  for (std::string& target : response.targets) {
    auto it = lb_policy_->child_policy_map_.find(target);
    if (it == lb_policy_->child_policy_map_.end()) {
      auto new_child = MakeRefCounted<ChildPolicyWrapper>(
          lb_policy_->Ref(DEBUG_LOCATION, "ChildPolicyWrapper"), target);
      new_child->StartUpdate();
      child_policies_to_finish_update.push_back(new_child.get());
      new_child_policy_wrappers.emplace_back(std::move(new_child));
    } else {
      new_child_policy_wrappers.emplace_back(
          it->second->Ref(DEBUG_LOCATION, "CacheEntry"));
      // If the target already existed but was not previously used for
      // this key, then we'll need to update the picker, since we
      // didn't actually create a new child policy, which would have
      // triggered an RLS picker update when it returned its first picker.
      if (old_targets.find(target) == old_targets.end()) {
        update_picker = true;
      }
    }
  }
  child_policy_wrappers_ = std::move(new_child_policy_wrappers);
  if (update_picker) {
    lb_policy_->UpdatePickerAsync();
  }
  return child_policies_to_finish_update;
}

//
// RlsLb::Cache
//

RlsLb::Cache::Cache(RlsLb* lb_policy) : lb_policy_(lb_policy) {
  Timestamp now = ExecCtx::Get()->Now();
  lb_policy_->Ref(DEBUG_LOCATION, "CacheCleanupTimer").release();
  GRPC_CLOSURE_INIT(&timer_callback_, OnCleanupTimer, this, nullptr);
  grpc_timer_init(&cleanup_timer_, now + kCacheCleanupTimerInterval,
                  &timer_callback_);
}

RlsLb::Cache::Entry* RlsLb::Cache::Find(const RequestKey& key) {
  auto it = map_.find(key);
  if (it == map_.end()) return nullptr;
  it->second->MarkUsed();
  return it->second.get();
}

RlsLb::Cache::Entry* RlsLb::Cache::FindOrInsert(const RequestKey& key) {
  auto it = map_.find(key);
  // If not found, create new entry.
  if (it == map_.end()) {
    size_t entry_size = EntrySizeForKey(key);
    MaybeShrinkSize(size_limit_ - std::min(size_limit_, entry_size));
    Entry* entry =
        new Entry(lb_policy_->Ref(DEBUG_LOCATION, "CacheEntry"), key);
    map_.emplace(key, OrphanablePtr<Entry>(entry));
    size_ += entry_size;
    if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
      gpr_log(GPR_INFO, "[rlslb %p] key=%s: cache entry added, entry=%p",
              lb_policy_, key.ToString().c_str(), entry);
    }
    return entry;
  }
  // Entry found, so use it.
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO, "[rlslb %p] key=%s: found cache entry %p", lb_policy_,
            key.ToString().c_str(), it->second.get());
  }
  it->second->MarkUsed();
  return it->second.get();
}

void RlsLb::Cache::Resize(size_t bytes) {
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO, "[rlslb %p] resizing cache to %" PRIuPTR " bytes",
            lb_policy_, bytes);
  }
  size_limit_ = bytes;
  MaybeShrinkSize(size_limit_);
}

void RlsLb::Cache::ResetAllBackoff() {
  for (auto& p : map_) {
    p.second->ResetBackoff();
  }
  lb_policy_->UpdatePickerAsync();
}

void RlsLb::Cache::Shutdown() {
  map_.clear();
  lru_list_.clear();
  grpc_timer_cancel(&cleanup_timer_);
}

void RlsLb::Cache::OnCleanupTimer(void* arg, absl::Status error) {
  Cache* cache = static_cast<Cache*>(arg);
  cache->lb_policy_->work_serializer()->Run(
      [cache, error]() {
        RefCountedPtr<RlsLb> lb_policy(cache->lb_policy_);
        if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
          gpr_log(GPR_INFO, "[rlslb %p] cache cleanup timer fired (%s)",
                  cache->lb_policy_, grpc_error_std_string(error).c_str());
        }
        if (error == GRPC_ERROR_CANCELLED) return;
        MutexLock lock(&lb_policy->mu_);
        if (lb_policy->is_shutdown_) return;
        for (auto it = cache->map_.begin(); it != cache->map_.end();) {
          if (GPR_UNLIKELY(it->second->ShouldRemove() &&
                           it->second->CanEvict())) {
            cache->size_ -= it->second->Size();
            it = cache->map_.erase(it);
          } else {
            ++it;
          }
        }
        Timestamp now = ExecCtx::Get()->Now();
        lb_policy.release();
        grpc_timer_init(&cache->cleanup_timer_,
                        now + kCacheCleanupTimerInterval,
                        &cache->timer_callback_);
      },
      DEBUG_LOCATION);
}

size_t RlsLb::Cache::EntrySizeForKey(const RequestKey& key) {
  // Key is stored twice, once in LRU list and again in the cache map.
  return (key.Size() * 2) + sizeof(Entry);
}

void RlsLb::Cache::MaybeShrinkSize(size_t bytes) {
  while (size_ > bytes) {
    auto lru_it = lru_list_.begin();
    if (GPR_UNLIKELY(lru_it == lru_list_.end())) break;
    auto map_it = map_.find(*lru_it);
    GPR_ASSERT(map_it != map_.end());
    if (!map_it->second->CanEvict()) break;
    if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
      gpr_log(GPR_INFO, "[rlslb %p] LRU eviction: removing entry %p %s",
              lb_policy_, map_it->second.get(), lru_it->ToString().c_str());
    }
    size_ -= map_it->second->Size();
    map_.erase(map_it);
  }
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO,
            "[rlslb %p] LRU pass complete: desired size=%" PRIuPTR
            " size=%" PRIuPTR,
            lb_policy_, bytes, size_);
  }
}

//
// RlsLb::RlsChannel::StateWatcher
//

void RlsLb::RlsChannel::StateWatcher::OnConnectivityStateChange(
    grpc_connectivity_state new_state, const absl::Status& status) {
  auto* lb_policy = rls_channel_->lb_policy_.get();
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO,
            "[rlslb %p] RlsChannel=%p StateWatcher=%p: "
            "state changed to %s (%s)",
            lb_policy, rls_channel_.get(), this,
            ConnectivityStateName(new_state), status.ToString().c_str());
  }
  if (rls_channel_->is_shutdown_) return;
  MutexLock lock(&lb_policy->mu_);
  if (new_state == GRPC_CHANNEL_READY && was_transient_failure_) {
    was_transient_failure_ = false;
    // Reset the backoff of all cache entries, so that we don't
    // double-penalize if an RLS request fails while the channel is
    // down, since the throttling for the channel being down is handled
    // at the channel level instead of in the individual cache entries.
    lb_policy->cache_.ResetAllBackoff();
  } else if (new_state == GRPC_CHANNEL_TRANSIENT_FAILURE) {
    was_transient_failure_ = true;
  }
}

//
// RlsLb::RlsChannel::Throttle
//

bool RlsLb::RlsChannel::Throttle::ShouldThrottle() {
  Timestamp now = ExecCtx::Get()->Now();
  while (!requests_.empty() && now - requests_.front() > window_size_) {
    requests_.pop_front();
  }
  while (!failures_.empty() && now - failures_.front() > window_size_) {
    failures_.pop_front();
  }
  // Compute probability of throttling.
  float num_requests = requests_.size();
  float num_successes = num_requests - failures_.size();
  // Note: it's possible that this ratio will be negative, in which case
  // no throttling will be done.
  float throttle_probability =
      (num_requests - (num_successes * ratio_for_successes_)) /
      (num_requests + padding_);
  // Generate a random number for the request.
  std::uniform_real_distribution<float> dist(0, 1.0);
  // Check if we should throttle the request.
  bool throttle = dist(rng_) < throttle_probability;
  // If we're throttling, record the request and the failure.
  if (throttle) {
    requests_.push_back(now);
    failures_.push_back(now);
  }
  return throttle;
}

void RlsLb::RlsChannel::Throttle::RegisterResponse(bool success) {
  Timestamp now = ExecCtx::Get()->Now();
  requests_.push_back(now);
  if (!success) failures_.push_back(now);
}

//
// RlsLb::RlsChannel
//

RlsLb::RlsChannel::RlsChannel(RefCountedPtr<RlsLb> lb_policy)
    : InternallyRefCounted<RlsChannel>(
          GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace) ? "RlsChannel" : nullptr),
      lb_policy_(std::move(lb_policy)) {
  // Get channel creds from parent channel.
  // TODO(roth): Once we eliminate insecure builds, get this via a
  // method on the helper instead of digging through channel args.
  auto* creds = lb_policy_->channel_args_.GetObject<grpc_channel_credentials>();
  // Use the parent channel's authority.
  std::string authority(lb_policy_->channel_control_helper()->GetAuthority());
  ChannelArgs args = ChannelArgs()
                         .Set(GRPC_ARG_DEFAULT_AUTHORITY, authority)
                         .Set(GRPC_ARG_CHANNELZ_IS_INTERNAL_CHANNEL, 1);
  // Propagate fake security connector expected targets, if any.
  // (This is ugly, but it seems better than propagating all channel args
  // from the parent channel by default and then having a giant
  // exclude list of args to strip out, like we do in grpclb.)
  absl::optional<absl::string_view> fake_security_expected_targets =
      lb_policy_->channel_args_.GetString(
          GRPC_ARG_FAKE_SECURITY_EXPECTED_TARGETS);
  if (fake_security_expected_targets.has_value()) {
    args = args.Set(GRPC_ARG_FAKE_SECURITY_EXPECTED_TARGETS,
                    *fake_security_expected_targets);
  }
  // Add service config args if needed.
  const std::string& service_config =
      lb_policy_->config_->rls_channel_service_config();
  if (!service_config.empty()) {
    args = args.Set(GRPC_ARG_SERVICE_CONFIG, service_config)
               .Set(GRPC_ARG_SERVICE_CONFIG_DISABLE_RESOLUTION, 1);
  }
  channel_ = grpc_channel_create(lb_policy_->config_->lookup_service().c_str(),
                                 creds, args.ToC().get());
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO, "[rlslb %p] RlsChannel=%p: created channel %p for %s",
            lb_policy_.get(), this, channel_,
            lb_policy_->config_->lookup_service().c_str());
  }
  if (channel_ != nullptr) {
    // Set up channelz linkage.
    channelz::ChannelNode* child_channelz_node =
        grpc_channel_get_channelz_node(channel_);
    channelz::ChannelNode* parent_channelz_node =
        lb_policy_->channel_args_.GetObject<channelz::ChannelNode>();
    if (child_channelz_node != nullptr && parent_channelz_node != nullptr) {
      parent_channelz_node->AddChildChannel(child_channelz_node->uuid());
      parent_channelz_node_ = parent_channelz_node->Ref();
    }
    // Start connectivity watch.
    ClientChannel* client_channel =
        ClientChannel::GetFromChannel(Channel::FromC(channel_));
    GPR_ASSERT(client_channel != nullptr);
    watcher_ = new StateWatcher(Ref(DEBUG_LOCATION, "StateWatcher"));
    client_channel->AddConnectivityWatcher(
        GRPC_CHANNEL_IDLE,
        OrphanablePtr<AsyncConnectivityStateWatcherInterface>(watcher_));
  }
}

void RlsLb::RlsChannel::Orphan() {
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO, "[rlslb %p] RlsChannel=%p, channel=%p: shutdown",
            lb_policy_.get(), this, channel_);
  }
  is_shutdown_ = true;
  if (channel_ != nullptr) {
    // Remove channelz linkage.
    if (parent_channelz_node_ != nullptr) {
      channelz::ChannelNode* child_channelz_node =
          grpc_channel_get_channelz_node(channel_);
      GPR_ASSERT(child_channelz_node != nullptr);
      parent_channelz_node_->RemoveChildChannel(child_channelz_node->uuid());
    }
    // Stop connectivity watch.
    if (watcher_ != nullptr) {
      ClientChannel* client_channel =
          ClientChannel::GetFromChannel(Channel::FromC(channel_));
      GPR_ASSERT(client_channel != nullptr);
      client_channel->RemoveConnectivityWatcher(watcher_);
      watcher_ = nullptr;
    }
    grpc_channel_destroy(channel_);
  }
  Unref(DEBUG_LOCATION, "Orphan");
}

void RlsLb::RlsChannel::StartRlsCall(const RequestKey& key,
                                     Cache::Entry* stale_entry) {
  std::unique_ptr<BackOff> backoff_state;
  grpc_lookup_v1_RouteLookupRequest_Reason reason =
      grpc_lookup_v1_RouteLookupRequest_REASON_MISS;
  std::string stale_header_data;
  if (stale_entry != nullptr) {
    backoff_state = stale_entry->TakeBackoffState();
    reason = grpc_lookup_v1_RouteLookupRequest_REASON_STALE;
    stale_header_data = stale_entry->header_data();
  }
  lb_policy_->request_map_.emplace(
      key, MakeOrphanable<RlsRequest>(
               lb_policy_->Ref(DEBUG_LOCATION, "RlsRequest"), key,
               lb_policy_->rls_channel_->Ref(DEBUG_LOCATION, "RlsRequest"),
               std::move(backoff_state), reason, std::move(stale_header_data)));
}

void RlsLb::RlsChannel::ReportResponseLocked(bool response_succeeded) {
  throttle_.RegisterResponse(response_succeeded);
}

void RlsLb::RlsChannel::ResetBackoff() {
  GPR_DEBUG_ASSERT(channel_ != nullptr);
  grpc_channel_reset_connect_backoff(channel_);
}

//
// RlsLb::RlsRequest
//

RlsLb::RlsRequest::RlsRequest(RefCountedPtr<RlsLb> lb_policy, RequestKey key,
                              RefCountedPtr<RlsChannel> rls_channel,
                              std::unique_ptr<BackOff> backoff_state,
                              grpc_lookup_v1_RouteLookupRequest_Reason reason,
                              std::string stale_header_data)
    : InternallyRefCounted<RlsRequest>(
          GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace) ? "RlsRequest" : nullptr),
      lb_policy_(std::move(lb_policy)),
      key_(std::move(key)),
      rls_channel_(std::move(rls_channel)),
      backoff_state_(std::move(backoff_state)),
      reason_(reason),
      stale_header_data_(std::move(stale_header_data)) {
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO,
            "[rlslb %p] rls_request=%p: RLS request created for key %s",
            lb_policy_.get(), this, key_.ToString().c_str());
  }
  GRPC_CLOSURE_INIT(&call_complete_cb_, OnRlsCallComplete, this, nullptr);
  ExecCtx::Run(
      DEBUG_LOCATION,
      GRPC_CLOSURE_INIT(&call_start_cb_, StartCall,
                        Ref(DEBUG_LOCATION, "StartCall").release(), nullptr),
      GRPC_ERROR_NONE);
}

RlsLb::RlsRequest::~RlsRequest() { GPR_ASSERT(call_ == nullptr); }

void RlsLb::RlsRequest::Orphan() {
  if (call_ != nullptr) {
    if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
      gpr_log(GPR_INFO, "[rlslb %p] rls_request=%p %s: cancelling RLS call",
              lb_policy_.get(), this, key_.ToString().c_str());
    }
    grpc_call_cancel_internal(call_);
  }
  Unref(DEBUG_LOCATION, "Orphan");
}

void RlsLb::RlsRequest::StartCall(void* arg, absl::Status /*error*/) {
  auto* request = static_cast<RlsRequest*>(arg);
  request->lb_policy_->work_serializer()->Run(
      [request]() {
        request->StartCallLocked();
        request->Unref(DEBUG_LOCATION, "StartCall");
      },
      DEBUG_LOCATION);
}

void RlsLb::RlsRequest::StartCallLocked() {
  {
    MutexLock lock(&lb_policy_->mu_);
    if (lb_policy_->is_shutdown_) return;
  }
  Timestamp now = ExecCtx::Get()->Now();
  deadline_ = now + lb_policy_->config_->lookup_service_timeout();
  grpc_metadata_array_init(&recv_initial_metadata_);
  grpc_metadata_array_init(&recv_trailing_metadata_);
  call_ = grpc_channel_create_pollset_set_call(
      rls_channel_->channel(), nullptr, GRPC_PROPAGATE_DEFAULTS,
      lb_policy_->interested_parties(),
      grpc_slice_from_static_string(kRlsRequestPath), nullptr, deadline_,
      nullptr);
  grpc_op ops[6];
  memset(ops, 0, sizeof(ops));
  grpc_op* op = ops;
  op->op = GRPC_OP_SEND_INITIAL_METADATA;
  ++op;
  op->op = GRPC_OP_SEND_MESSAGE;
  send_message_ = MakeRequestProto();
  op->data.send_message.send_message = send_message_;
  ++op;
  op->op = GRPC_OP_SEND_CLOSE_FROM_CLIENT;
  ++op;
  op->op = GRPC_OP_RECV_INITIAL_METADATA;
  op->data.recv_initial_metadata.recv_initial_metadata =
      &recv_initial_metadata_;
  ++op;
  op->op = GRPC_OP_RECV_MESSAGE;
  op->data.recv_message.recv_message = &recv_message_;
  ++op;
  op->op = GRPC_OP_RECV_STATUS_ON_CLIENT;
  op->data.recv_status_on_client.trailing_metadata = &recv_trailing_metadata_;
  op->data.recv_status_on_client.status = &status_recv_;
  op->data.recv_status_on_client.status_details = &status_details_recv_;
  ++op;
  Ref(DEBUG_LOCATION, "OnRlsCallComplete").release();
  auto call_error = grpc_call_start_batch_and_execute(
      call_, ops, static_cast<size_t>(op - ops), &call_complete_cb_);
  GPR_ASSERT(call_error == GRPC_CALL_OK);
}

void RlsLb::RlsRequest::OnRlsCallComplete(void* arg, absl::Status error) {
  auto* request = static_cast<RlsRequest*>(arg);
  request->lb_policy_->work_serializer()->Run(
      [request, error]() {
        request->OnRlsCallCompleteLocked(error);
        request->Unref(DEBUG_LOCATION, "OnRlsCallComplete");
      },
      DEBUG_LOCATION);
}

void RlsLb::RlsRequest::OnRlsCallCompleteLocked(absl::Status error) {
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    std::string status_message(StringViewFromSlice(status_details_recv_));
    gpr_log(GPR_INFO,
            "[rlslb %p] rls_request=%p %s, error=%s, status={%d, %s} RLS call "
            "response received",
            lb_policy_.get(), this, key_.ToString().c_str(),
            grpc_error_std_string(error).c_str(), status_recv_,
            status_message.c_str());
  }
  // Parse response.
  ResponseInfo response;
  if (!error.ok()) {
    grpc_status_code code;
    std::string message;
    grpc_error_get_status(error, deadline_, &code, &message,
                          /*http_error=*/nullptr, /*error_string=*/nullptr);
    response.status =
        absl::Status(static_cast<absl::StatusCode>(code), message);
  } else if (status_recv_ != GRPC_STATUS_OK) {
    response.status = absl::Status(static_cast<absl::StatusCode>(status_recv_),
                                   StringViewFromSlice(status_details_recv_));
  } else {
    response = ParseResponseProto();
  }
  // Clean up call state.
  grpc_byte_buffer_destroy(send_message_);
  grpc_byte_buffer_destroy(recv_message_);
  grpc_metadata_array_destroy(&recv_initial_metadata_);
  grpc_metadata_array_destroy(&recv_trailing_metadata_);
  grpc_slice_unref_internal(status_details_recv_);
  grpc_call_unref(call_);
  call_ = nullptr;
  // Return result to cache.
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO, "[rlslb %p] rls_request=%p %s: response info: %s",
            lb_policy_.get(), this, key_.ToString().c_str(),
            response.ToString().c_str());
  }
  std::vector<ChildPolicyWrapper*> child_policies_to_finish_update;
  {
    MutexLock lock(&lb_policy_->mu_);
    if (lb_policy_->is_shutdown_) return;
    rls_channel_->ReportResponseLocked(response.status.ok());
    Cache::Entry* cache_entry = lb_policy_->cache_.FindOrInsert(key_);
    child_policies_to_finish_update = cache_entry->OnRlsResponseLocked(
        std::move(response), std::move(backoff_state_));
    lb_policy_->request_map_.erase(key_);
  }
  // Now that we've released the lock, finish the update on any newly
  // created child policies.
  for (ChildPolicyWrapper* child : child_policies_to_finish_update) {
    child->MaybeFinishUpdate();
  }
}

grpc_byte_buffer* RlsLb::RlsRequest::MakeRequestProto() {
  upb::Arena arena;
  grpc_lookup_v1_RouteLookupRequest* req =
      grpc_lookup_v1_RouteLookupRequest_new(arena.ptr());
  grpc_lookup_v1_RouteLookupRequest_set_target_type(
      req, upb_StringView_FromDataAndSize(kGrpc, sizeof(kGrpc) - 1));
  for (const auto& kv : key_.key_map) {
    grpc_lookup_v1_RouteLookupRequest_key_map_set(
        req, upb_StringView_FromDataAndSize(kv.first.data(), kv.first.size()),
        upb_StringView_FromDataAndSize(kv.second.data(), kv.second.size()),
        arena.ptr());
  }
  grpc_lookup_v1_RouteLookupRequest_set_reason(req, reason_);
  if (!stale_header_data_.empty()) {
    grpc_lookup_v1_RouteLookupRequest_set_stale_header_data(
        req, upb_StringView_FromDataAndSize(stale_header_data_.data(),
                                            stale_header_data_.size()));
  }
  size_t len;
  char* buf =
      grpc_lookup_v1_RouteLookupRequest_serialize(req, arena.ptr(), &len);
  grpc_slice send_slice = grpc_slice_from_copied_buffer(buf, len);
  grpc_byte_buffer* byte_buffer = grpc_raw_byte_buffer_create(&send_slice, 1);
  grpc_slice_unref_internal(send_slice);
  return byte_buffer;
}

RlsLb::ResponseInfo RlsLb::RlsRequest::ParseResponseProto() {
  ResponseInfo response_info;
  upb::Arena arena;
  grpc_byte_buffer_reader bbr;
  grpc_byte_buffer_reader_init(&bbr, recv_message_);
  grpc_slice recv_slice = grpc_byte_buffer_reader_readall(&bbr);
  grpc_byte_buffer_reader_destroy(&bbr);
  grpc_lookup_v1_RouteLookupResponse* response =
      grpc_lookup_v1_RouteLookupResponse_parse(
          reinterpret_cast<const char*>(GRPC_SLICE_START_PTR(recv_slice)),
          GRPC_SLICE_LENGTH(recv_slice), arena.ptr());
  grpc_slice_unref_internal(recv_slice);
  if (response == nullptr) {
    response_info.status = absl::InternalError("cannot parse RLS response");
    return response_info;
  }
  size_t num_targets;
  const upb_StringView* targets_strview =
      grpc_lookup_v1_RouteLookupResponse_targets(response, &num_targets);
  if (num_targets == 0) {
    response_info.status =
        absl::InvalidArgumentError("RLS response has no target entry");
    return response_info;
  }
  response_info.targets.reserve(num_targets);
  for (size_t i = 0; i < num_targets; ++i) {
    response_info.targets.emplace_back(targets_strview[i].data,
                                       targets_strview[i].size);
  }
  upb_StringView header_data_strview =
      grpc_lookup_v1_RouteLookupResponse_header_data(response);
  response_info.header_data =
      std::string(header_data_strview.data, header_data_strview.size);
  return response_info;
}

//
// RlsLb
//

std::string GetServerUri(const ChannelArgs& args) {
  auto server_uri_str = args.GetString(GRPC_ARG_SERVER_URI);
  GPR_ASSERT(server_uri_str.has_value());
  absl::StatusOr<URI> uri = URI::Parse(*server_uri_str);
  GPR_ASSERT(uri.ok());
  return std::string(absl::StripPrefix(uri->path(), "/"));
}

RlsLb::RlsLb(Args args)
    : LoadBalancingPolicy(std::move(args)),
      server_name_(GetServerUri(channel_args())),
      cache_(this) {
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO, "[rlslb %p] policy created", this);
  }
}

void RlsLb::UpdateLocked(UpdateArgs args) {
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO, "[rlslb %p] policy updated", this);
  }
  update_in_progress_ = true;
  // Swap out config.
  RefCountedPtr<RlsLbConfig> old_config = std::move(config_);
  config_ = std::move(args.config);
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace) &&
      (old_config == nullptr ||
       old_config->child_policy_config() != config_->child_policy_config())) {
    gpr_log(GPR_INFO, "[rlslb %p] updated child policy config: %s", this,
            config_->child_policy_config().Dump().c_str());
  }
  // Swap out addresses.
  // If the new address list is an error and we have an existing address list,
  // stick with the existing addresses.
  absl::StatusOr<ServerAddressList> old_addresses;
  if (args.addresses.ok()) {
    old_addresses = std::move(addresses_);
    addresses_ = std::move(args.addresses);
  } else {
    old_addresses = addresses_;
  }
  // Swap out channel args.
  channel_args_ = std::move(args.args);
  // Determine whether we need to update all child policies.
  bool update_child_policies =
      old_config == nullptr ||
      old_config->child_policy_config() != config_->child_policy_config() ||
      old_addresses != addresses_ || args.args != channel_args_;
  // If default target changes, swap out child policy.
  bool created_default_child = false;
  if (old_config == nullptr ||
      config_->default_target() != old_config->default_target()) {
    if (config_->default_target().empty()) {
      if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
        gpr_log(GPR_INFO, "[rlslb %p] unsetting default target", this);
      }
      default_child_policy_.reset();
    } else {
      auto it = child_policy_map_.find(config_->default_target());
      if (it == child_policy_map_.end()) {
        if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
          gpr_log(GPR_INFO, "[rlslb %p] creating new default target", this);
        }
        default_child_policy_ = MakeRefCounted<ChildPolicyWrapper>(
            Ref(DEBUG_LOCATION, "ChildPolicyWrapper"),
            config_->default_target());
        created_default_child = true;
      } else {
        if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
          gpr_log(GPR_INFO,
                  "[rlslb %p] using existing child for default target", this);
        }
        default_child_policy_ =
            it->second->Ref(DEBUG_LOCATION, "DefaultChildPolicy");
      }
    }
  }
  // Now grab the lock to swap out the state it guards.
  {
    MutexLock lock(&mu_);
    // Swap out RLS channel if needed.
    if (old_config == nullptr ||
        config_->lookup_service() != old_config->lookup_service()) {
      rls_channel_ =
          MakeOrphanable<RlsChannel>(Ref(DEBUG_LOCATION, "RlsChannel"));
    }
    // Resize cache if needed.
    if (old_config == nullptr ||
        config_->cache_size_bytes() != old_config->cache_size_bytes()) {
      cache_.Resize(static_cast<size_t>(config_->cache_size_bytes()));
    }
    // Start update of child policies if needed.
    if (update_child_policies) {
      if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
        gpr_log(GPR_INFO, "[rlslb %p] starting child policy updates", this);
      }
      for (auto& p : child_policy_map_) {
        p.second->StartUpdate();
      }
    } else if (created_default_child) {
      if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
        gpr_log(GPR_INFO, "[rlslb %p] starting default child policy update",
                this);
      }
      default_child_policy_->StartUpdate();
    }
  }
  // Now that we've released the lock, finish update of child policies.
  if (update_child_policies) {
    if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
      gpr_log(GPR_INFO, "[rlslb %p] finishing child policy updates", this);
    }
    for (auto& p : child_policy_map_) {
      p.second->MaybeFinishUpdate();
    }
  } else if (created_default_child) {
    if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
      gpr_log(GPR_INFO, "[rlslb %p] finishing default child policy update",
              this);
    }
    default_child_policy_->MaybeFinishUpdate();
  }
  update_in_progress_ = false;
  // In principle, we need to update the picker here only if the config
  // fields used by the picker have changed.  However, it seems fragile
  // to check individual fields, since the picker logic could change in
  // the future to use additional config fields, and we might not
  // remember to update the code here.  So for now, we just unconditionally
  // update the picker here, even though it's probably redundant.
  UpdatePickerLocked();
}

void RlsLb::ExitIdleLocked() {
  MutexLock lock(&mu_);
  for (auto& child_entry : child_policy_map_) {
    child_entry.second->ExitIdleLocked();
  }
}

void RlsLb::ResetBackoffLocked() {
  {
    MutexLock lock(&mu_);
    rls_channel_->ResetBackoff();
    cache_.ResetAllBackoff();
  }
  for (auto& child : child_policy_map_) {
    child.second->ResetBackoffLocked();
  }
}

void RlsLb::ShutdownLocked() {
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO, "[rlslb %p] policy shutdown", this);
  }
  MutexLock lock(&mu_);
  is_shutdown_ = true;
  config_.reset(DEBUG_LOCATION, "ShutdownLocked");
  channel_args_ = ChannelArgs();
  cache_.Shutdown();
  request_map_.clear();
  rls_channel_.reset();
  default_child_policy_.reset();
}

void RlsLb::UpdatePickerAsync() {
  // Run via the ExecCtx, since the caller may be holding the lock, and
  // we don't want to be doing that when we hop into the WorkSerializer,
  // in case the WorkSerializer callback happens to run inline.
  ExecCtx::Run(
      DEBUG_LOCATION,
      GRPC_CLOSURE_CREATE(UpdatePickerCallback,
                          Ref(DEBUG_LOCATION, "UpdatePickerCallback").release(),
                          grpc_schedule_on_exec_ctx),
      GRPC_ERROR_NONE);
}

void RlsLb::UpdatePickerCallback(void* arg, absl::Status /*error*/) {
  auto* rls_lb = static_cast<RlsLb*>(arg);
  rls_lb->work_serializer()->Run(
      [rls_lb]() {
        RefCountedPtr<RlsLb> lb_policy(rls_lb);
        lb_policy->UpdatePickerLocked();
        lb_policy.reset(DEBUG_LOCATION, "UpdatePickerCallback");
      },
      DEBUG_LOCATION);
}

void RlsLb::UpdatePickerLocked() {
  // If we're in the process of propagating an update from our parent to
  // our children, ignore any updates that come from the children.  We
  // will instead return a new picker once the update has been seen by
  // all children.  This avoids unnecessary picker churn while an update
  // is being propagated to our children.
  if (update_in_progress_) return;
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO, "[rlslb %p] updating picker", this);
  }
  grpc_connectivity_state state = GRPC_CHANNEL_IDLE;
  if (!child_policy_map_.empty()) {
    state = GRPC_CHANNEL_TRANSIENT_FAILURE;
    int num_idle = 0;
    int num_connecting = 0;
    {
      MutexLock lock(&mu_);
      if (is_shutdown_) return;
      for (auto& p : child_policy_map_) {
        grpc_connectivity_state child_state = p.second->connectivity_state();
        if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
          gpr_log(GPR_INFO, "[rlslb %p] target %s in state %s", this,
                  p.second->target().c_str(),
                  ConnectivityStateName(child_state));
        }
        if (child_state == GRPC_CHANNEL_READY) {
          state = GRPC_CHANNEL_READY;
          break;
        } else if (child_state == GRPC_CHANNEL_CONNECTING) {
          ++num_connecting;
        } else if (child_state == GRPC_CHANNEL_IDLE) {
          ++num_idle;
        }
      }
      if (state != GRPC_CHANNEL_READY) {
        if (num_connecting > 0) {
          state = GRPC_CHANNEL_CONNECTING;
        } else if (num_idle > 0) {
          state = GRPC_CHANNEL_IDLE;
        }
      }
    }
  }
  if (GRPC_TRACE_FLAG_ENABLED(grpc_lb_rls_trace)) {
    gpr_log(GPR_INFO, "[rlslb %p] reporting state %s", this,
            ConnectivityStateName(state));
  }
  absl::Status status;
  if (state == GRPC_CHANNEL_TRANSIENT_FAILURE) {
    status = absl::UnavailableError("no children available");
  }
  channel_control_helper()->UpdateState(
      state, status, absl::make_unique<Picker>(Ref(DEBUG_LOCATION, "Picker")));
}

//
// RlsLbFactory
//

absl::Status ParseJsonHeaders(size_t idx, const Json& json,
                                   std::string* key,
                                   std::vector<std::string>* headers) {
  if (json.type() != Json::Type::OBJECT) {
    return GRPC_ERROR_CREATE_FROM_CPP_STRING(absl::StrCat(
        "field:headers index:", idx, " error:type should be OBJECT"));
  }
  std::vector<absl::Status> error_list;
  // requiredMatch must not be present.
  if (json.object_value().find("requiredMatch") != json.object_value().end()) {
    error_list.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
        "field:requiredMatch error:must not be present"));
  }
  // Find key.
  if (ParseJsonObjectField(json.object_value(), "key", key, &error_list) &&
      key->empty()) {
    error_list.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
        "field:key error:must be non-empty"));
  }
  // Find headers.
  const Json::Array* headers_json = nullptr;
  ParseJsonObjectField(json.object_value(), "names", &headers_json,
                       &error_list);
  if (headers_json != nullptr) {
    if (headers_json->empty()) {
      error_list.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
          "field:names error:list is empty"));
    } else {
      size_t name_idx = 0;
      for (const Json& name_json : *headers_json) {
        if (name_json.type() != Json::Type::STRING) {
          error_list.push_back(GRPC_ERROR_CREATE_FROM_CPP_STRING(absl::StrCat(
              "field:names index:", name_idx, " error:type should be STRING")));
        } else if (name_json.string_value().empty()) {
          error_list.push_back(GRPC_ERROR_CREATE_FROM_CPP_STRING(
              absl::StrCat("field:names index:", name_idx,
                           " error:header name must be non-empty")));
        } else {
          headers->push_back(name_json.string_value());
        }
        ++name_idx;
      }
    }
  }
  return GRPC_ERROR_CREATE_FROM_VECTOR_AND_CPP_STRING(
      absl::StrCat("field:headers index:", idx), &error_list);
}

std::string ParseJsonMethodName(size_t idx, const Json& json,
                                absl::Status* error) {
  if (json.type() != Json::Type::OBJECT) {
    *error = GRPC_ERROR_CREATE_FROM_CPP_STRING(absl::StrCat(
        "field:names index:", idx, " error:type should be OBJECT"));
    return "";
  }
  std::vector<absl::Status> error_list;
  // Find service name.
  absl::string_view service_name;
  ParseJsonObjectField(json.object_value(), "service", &service_name,
                       &error_list);
  // Find method name.
  absl::string_view method_name;
  ParseJsonObjectField(json.object_value(), "method", &method_name, &error_list,
                       /*required=*/false);
  // Return error, if any.
  *error = GRPC_ERROR_CREATE_FROM_VECTOR_AND_CPP_STRING(
      absl::StrCat("field:names index:", idx), &error_list);
  // Construct path.
  return absl::StrCat("/", service_name, "/", method_name);
}

absl::Status ParseGrpcKeybuilder(
    size_t idx, const Json& json, RlsLbConfig::KeyBuilderMap* key_builder_map) {
  if (json.type() != Json::Type::OBJECT) {
    return GRPC_ERROR_CREATE_FROM_CPP_STRING(absl::StrCat(
        "field:grpc_keybuilders index:", idx, " error:type should be OBJECT"));
  }
  std::vector<absl::Status> error_list;
  // Parse names.
  std::set<std::string> names;
  const Json::Array* names_array = nullptr;
  if (ParseJsonObjectField(json.object_value(), "names", &names_array,
                           &error_list)) {
    if (names_array->empty()) {
      error_list.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
          "field:names error:list is empty"));
    } else {
      size_t name_idx = 0;
      for (const Json& name_json : *names_array) {
        absl::Status child_error = GRPC_ERROR_NONE;
        std::string name =
            ParseJsonMethodName(name_idx++, name_json, &child_error);
        if (!child_error.ok()) {
          error_list.push_back(child_error);
        } else {
          bool inserted = names.insert(name).second;
          if (!inserted) {
            error_list.push_back(GRPC_ERROR_CREATE_FROM_CPP_STRING(
                absl::StrCat("field:names error:duplicate entry for ", name)));
          }
        }
      }
    }
  }
  // Helper function to check for duplicate keys.
  std::set<std::string> all_keys;
  auto duplicate_key_check_func = [&all_keys,
                                   &error_list](const std::string& key) {
    auto it = all_keys.find(key);
    if (it != all_keys.end()) {
      error_list.push_back(GRPC_ERROR_CREATE_FROM_CPP_STRING(
          absl::StrCat("key \"", key, "\" listed multiple times")));
    } else {
      all_keys.insert(key);
    }
  };
  // Parse headers.
  RlsLbConfig::KeyBuilder key_builder;
  const Json::Array* headers_array = nullptr;
  ParseJsonObjectField(json.object_value(), "headers", &headers_array,
                       &error_list, /*required=*/false);
  if (headers_array != nullptr) {
    size_t header_idx = 0;
    for (const Json& header_json : *headers_array) {
      std::string key;
      std::vector<std::string> headers;
      absl::Status child_error =
          ParseJsonHeaders(header_idx++, header_json, &key, &headers);
      if (!child_error.ok()) {
        error_list.push_back(child_error);
      } else {
        duplicate_key_check_func(key);
        key_builder.header_keys.emplace(key, std::move(headers));
      }
    }
  }
  // Parse extraKeys.
  const Json::Object* extra_keys = nullptr;
  ParseJsonObjectField(json.object_value(), "extraKeys", &extra_keys,
                       &error_list, /*required=*/false);
  if (extra_keys != nullptr) {
    std::vector<absl::Status> extra_keys_errors;
    if (ParseJsonObjectField(*extra_keys, "host", &key_builder.host_key,
                             &extra_keys_errors, /*required=*/false) &&
        key_builder.host_key.empty()) {
      extra_keys_errors.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
          "field:host error:must be non-empty"));
    }
    if (!key_builder.host_key.empty()) {
      duplicate_key_check_func(key_builder.host_key);
    }
    if (ParseJsonObjectField(*extra_keys, "service", &key_builder.service_key,
                             &extra_keys_errors, /*required=*/false) &&
        key_builder.service_key.empty()) {
      extra_keys_errors.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
          "field:service error:must be non-empty"));
    }
    if (!key_builder.service_key.empty()) {
      duplicate_key_check_func(key_builder.service_key);
    }
    if (ParseJsonObjectField(*extra_keys, "method", &key_builder.method_key,
                             &extra_keys_errors, /*required=*/false) &&
        key_builder.method_key.empty()) {
      extra_keys_errors.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
          "field:method error:must be non-empty"));
    }
    if (!key_builder.method_key.empty()) {
      duplicate_key_check_func(key_builder.method_key);
    }
    if (!extra_keys_errors.empty()) {
      error_list.push_back(
          GRPC_ERROR_CREATE_FROM_VECTOR("field:extraKeys", &extra_keys_errors));
    }
  }
  // Parse constantKeys.
  const Json::Object* constant_keys = nullptr;
  ParseJsonObjectField(json.object_value(), "constantKeys", &constant_keys,
                       &error_list, /*required=*/false);
  if (constant_keys != nullptr) {
    std::vector<absl::Status> constant_keys_errors;
    for (const auto& p : *constant_keys) {
      const std::string& key = p.first;
      const Json& value = p.second;
      if (key.empty()) {
        constant_keys_errors.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
            "error:keys must be non-empty"));
      }
      duplicate_key_check_func(key);
      ExtractJsonString(value, key, &key_builder.constant_keys[key],
                        &constant_keys_errors);
    }
    if (!constant_keys_errors.empty()) {
      error_list.push_back(GRPC_ERROR_CREATE_FROM_VECTOR(
          "field:constantKeys", &constant_keys_errors));
    }
  }
  // Insert key_builder into key_builder_map.
  for (const std::string& name : names) {
    bool inserted = key_builder_map->emplace(name, key_builder).second;
    if (!inserted) {
      error_list.push_back(GRPC_ERROR_CREATE_FROM_CPP_STRING(
          absl::StrCat("field:names error:duplicate entry for ", name)));
    }
  }
  return GRPC_ERROR_CREATE_FROM_VECTOR_AND_CPP_STRING(
      absl::StrCat("index:", idx), &error_list);
}

RlsLbConfig::KeyBuilderMap ParseGrpcKeybuilders(
    const Json::Array& key_builder_list, absl::Status* error) {
  RlsLbConfig::KeyBuilderMap key_builder_map;
  if (key_builder_list.empty()) {
    *error = GRPC_ERROR_CREATE_FROM_STATIC_STRING(
        "field:grpcKeybuilders error:list is empty");
    return key_builder_map;
  }
  std::vector<absl::Status> error_list;
  size_t idx = 0;
  for (const Json& key_builder : key_builder_list) {
    absl::Status child_error =
        ParseGrpcKeybuilder(idx++, key_builder, &key_builder_map);
    if (!child_error.ok()) error_list.push_back(child_error);
  }
  *error = GRPC_ERROR_CREATE_FROM_VECTOR("field:grpcKeybuilders", &error_list);
  return key_builder_map;
}

RlsLbConfig::RouteLookupConfig ParseRouteLookupConfig(
    const Json::Object& json, absl::Status* error) {
  std::vector<absl::Status> error_list;
  RlsLbConfig::RouteLookupConfig route_lookup_config;
  // Parse grpcKeybuilders.
  const Json::Array* keybuilder_list = nullptr;
  ParseJsonObjectField(json, "grpcKeybuilders", &keybuilder_list, &error_list);
  if (keybuilder_list != nullptr) {
    absl::Status child_error = GRPC_ERROR_NONE;
    route_lookup_config.key_builder_map =
        ParseGrpcKeybuilders(*keybuilder_list, &child_error);
    if (!child_error.ok()) error_list.push_back(child_error);
  }
  // Parse lookupService.
  if (ParseJsonObjectField(json, "lookupService",
                           &route_lookup_config.lookup_service, &error_list)) {
    if (!CoreConfiguration::Get().resolver_registry().IsValidTarget(
            route_lookup_config.lookup_service)) {
      error_list.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
          "field:lookupService error:must be valid gRPC target URI"));
    }
  }
  // Parse lookupServiceTimeout.
  route_lookup_config.lookup_service_timeout = kDefaultLookupServiceTimeout;
  ParseJsonObjectFieldAsDuration(json, "lookupServiceTimeout",
                                 &route_lookup_config.lookup_service_timeout,
                                 &error_list, /*required=*/false);
  // Parse maxAge.
  route_lookup_config.max_age = kMaxMaxAge;
  bool max_age_set = ParseJsonObjectFieldAsDuration(
      json, "maxAge", &route_lookup_config.max_age, &error_list,
      /*required=*/false);
  // Clamp maxAge to the max allowed value.
  if (route_lookup_config.max_age > kMaxMaxAge) {
    route_lookup_config.max_age = kMaxMaxAge;
  }
  // Parse staleAge.
  route_lookup_config.stale_age = kMaxMaxAge;
  bool stale_age_set = ParseJsonObjectFieldAsDuration(
      json, "staleAge", &route_lookup_config.stale_age, &error_list,
      /*required=*/false);
  // If staleAge is set, then maxAge must also be set.
  if (stale_age_set && !max_age_set) {
    error_list.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
        "field:maxAge error:must be set if staleAge is set"));
  }
  // Ignore staleAge if greater than or equal to maxAge.
  if (route_lookup_config.stale_age >= route_lookup_config.max_age) {
    route_lookup_config.stale_age = route_lookup_config.max_age;
  }
  // Parse cacheSizeBytes.
  ParseJsonObjectField(json, "cacheSizeBytes",
                       &route_lookup_config.cache_size_bytes, &error_list);
  if (route_lookup_config.cache_size_bytes <= 0) {
    error_list.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
        "field:cacheSizeBytes error:must be greater than 0"));
  }
  // Clamp cacheSizeBytes to the max allowed value.
  if (route_lookup_config.cache_size_bytes > kMaxCacheSizeBytes) {
    route_lookup_config.cache_size_bytes = kMaxCacheSizeBytes;
  }
  // Parse defaultTarget.
  if (ParseJsonObjectField(json, "defaultTarget",
                           &route_lookup_config.default_target, &error_list,
                           /*required=*/false)) {
    if (route_lookup_config.default_target.empty()) {
      error_list.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
          "field:defaultTarget error:must be non-empty if set"));
    }
  }
  *error =
      GRPC_ERROR_CREATE_FROM_VECTOR("field:routeLookupConfig", &error_list);
  return route_lookup_config;
}

absl::Status ValidateChildPolicyList(
    const Json& child_policy_list,
    const std::string& child_policy_config_target_field_name,
    const std::string& default_target, Json* child_policy_config,
    RefCountedPtr<LoadBalancingPolicy::Config>*
        default_child_policy_parsed_config) {
  // Add target to each entry in the config proto.
  *child_policy_config = child_policy_list;
  std::string target =
      default_target.empty() ? kFakeTargetFieldValue : default_target;
  absl::Status error = InsertOrUpdateChildPolicyField(
      child_policy_config_target_field_name, target, child_policy_config);
  if (!error.ok()) return error;
  // Parse the config.
  RefCountedPtr<LoadBalancingPolicy::Config> parsed_config =
      LoadBalancingPolicyRegistry::ParseLoadBalancingConfig(
          *child_policy_config, &error);
  if (!error.ok()) return error;
  // Find the chosen config and return it in JSON form.
  // We remove all non-selected configs, and in the selected config, we leave
  // the target field in place, set to the default value.  This slightly
  // optimizes what we need to do later when we update a child policy for a
  // given target.
  if (parsed_config != nullptr) {
    for (Json& config : *(child_policy_config->mutable_array())) {
      if (config.object_value().begin()->first == parsed_config->name()) {
        Json save_config = std::move(config);
        child_policy_config->mutable_array()->clear();
        child_policy_config->mutable_array()->push_back(std::move(save_config));
        break;
      }
    }
  }
  // If default target is set, return the parsed config.
  if (!default_target.empty()) {
    *default_child_policy_parsed_config = std::move(parsed_config);
  }
  return GRPC_ERROR_NONE;
}

class RlsLbFactory : public LoadBalancingPolicyFactory {
 public:
  const char* name() const override { return kRls; }

  OrphanablePtr<LoadBalancingPolicy> CreateLoadBalancingPolicy(
      LoadBalancingPolicy::Args args) const override {
    return MakeOrphanable<RlsLb>(std::move(args));
  }

  RefCountedPtr<LoadBalancingPolicy::Config> ParseLoadBalancingConfig(
      const Json& config, absl::Status* error) const override {
    std::vector<absl::Status> error_list;
    // Parse routeLookupConfig.
    RlsLbConfig::RouteLookupConfig route_lookup_config;
    const Json::Object* route_lookup_config_json = nullptr;
    if (ParseJsonObjectField(config.object_value(), "routeLookupConfig",
                             &route_lookup_config_json, &error_list)) {
      absl::Status child_error = GRPC_ERROR_NONE;
      route_lookup_config =
          ParseRouteLookupConfig(*route_lookup_config_json, &child_error);
      if (!child_error.ok()) error_list.push_back(child_error);
    }
    // Parse routeLookupChannelServiceConfig.
    std::string rls_channel_service_config;
    const Json::Object* rls_channel_service_config_json_obj = nullptr;
    if (ParseJsonObjectField(config.object_value(),
                             "routeLookupChannelServiceConfig",
                             &rls_channel_service_config_json_obj, &error_list,
                             /*required=*/false)) {
      absl::Status child_error = GRPC_ERROR_NONE;
      Json rls_channel_service_config_json(
          *rls_channel_service_config_json_obj);
      rls_channel_service_config = rls_channel_service_config_json.Dump();
      auto service_config = MakeRefCounted<ServiceConfigImpl>(
          ChannelArgs(), rls_channel_service_config,
          std::move(rls_channel_service_config_json), &child_error);
      if (!child_error.ok()) {
        error_list.push_back(GRPC_ERROR_CREATE_REFERENCING_FROM_STATIC_STRING(
            "field:routeLookupChannelServiceConfig", &child_error, 1));
      }
    }
    // Parse childPolicyConfigTargetFieldName.
    std::string child_policy_config_target_field_name;
    if (ParseJsonObjectField(
            config.object_value(), "childPolicyConfigTargetFieldName",
            &child_policy_config_target_field_name, &error_list)) {
      if (child_policy_config_target_field_name.empty()) {
        error_list.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
            "field:childPolicyConfigTargetFieldName error:must be non-empty"));
      }
    }
    // Parse childPolicy.
    Json child_policy_config;
    RefCountedPtr<LoadBalancingPolicy::Config>
        default_child_policy_parsed_config;
    auto it = config.object_value().find("childPolicy");
    if (it == config.object_value().end()) {
      error_list.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
          "field:childPolicy error:does not exist."));
    } else if (it->second.type() != Json::Type::ARRAY) {
      error_list.push_back(GRPC_ERROR_CREATE_FROM_STATIC_STRING(
          "field:childPolicy error:type should be ARRAY"));
    } else {
      absl::Status child_error = ValidateChildPolicyList(
          it->second, child_policy_config_target_field_name,
          route_lookup_config.default_target, &child_policy_config,
          &default_child_policy_parsed_config);
      if (!child_error.ok()) {
        error_list.push_back(GRPC_ERROR_CREATE_REFERENCING_FROM_STATIC_STRING(
            "field:childPolicy", &child_error, 1));
      }
    }
    // Return result.
    *error = GRPC_ERROR_CREATE_FROM_VECTOR(
        "errors parsing RLS LB policy config", &error_list);
    return MakeRefCounted<RlsLbConfig>(
        std::move(route_lookup_config), std::move(rls_channel_service_config),
        std::move(child_policy_config),
        std::move(child_policy_config_target_field_name),
        std::move(default_child_policy_parsed_config));
  }
};

}  //  namespace

void RlsLbPluginInit() {
  LoadBalancingPolicyRegistry::Builder::RegisterLoadBalancingPolicyFactory(
      absl::make_unique<RlsLbFactory>());
}

void RlsLbPluginShutdown() {}

}  // namespace grpc_core
