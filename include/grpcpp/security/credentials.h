/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef GRPCPP_SECURITY_CREDENTIALS_H
#define GRPCPP_SECURITY_CREDENTIALS_H

#include <grpcpp/security/credentials_impl.h>

namespace grpc_impl {

class Channel;
}  // namespace grpc_impl
namespace grpc {

class CallCredentials;
class ChannelArguments;
class ChannelCredentials;
class SecureCallCredentials;
class SecureChannelCredentials;
}  // namespace grpc
namespace grpc_impl {
std::shared_ptr<Channel> CreateCustomChannel(
    const grpc::string& target,
    const std::shared_ptr<grpc::ChannelCredentials>& creds,
    const grpc::ChannelArguments& args);

namespace experimental {
std::shared_ptr<Channel> CreateCustomChannelWithInterceptors(
    const grpc::string& target,
    const std::shared_ptr<grpc::ChannelCredentials>& creds,
    const grpc::ChannelArguments& args,
    std::vector<
        std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators);
}  // namespace experimental
}  // namespace grpc_impl
namespace grpc {
class SecureChannelCredentials;
class SecureCallCredentials;

/// A channel credentials object encapsulates all the state needed by a client
/// to authenticate with a server for a given channel.
/// It can make various assertions, e.g., about the client’s identity, role
/// for all the calls on that channel.
///
/// \see https://grpc.io/docs/guides/auth.html
class ChannelCredentials : private GrpcLibraryCodegen {
 public:
  ChannelCredentials();
  ~ChannelCredentials();

 protected:
  friend std::shared_ptr<ChannelCredentials> CompositeChannelCredentials(
      const std::shared_ptr<ChannelCredentials>& channel_creds,
      const std::shared_ptr<CallCredentials>& call_creds);

  virtual SecureChannelCredentials* AsSecureCredentials() = 0;

 private:
  friend std::shared_ptr<::grpc_impl::Channel> grpc_impl::CreateCustomChannel(
      const grpc::string& target,
      const std::shared_ptr<ChannelCredentials>& creds,
      const grpc::ChannelArguments& args);

  friend std::shared_ptr<::grpc_impl::Channel>
  grpc_impl::experimental::CreateCustomChannelWithInterceptors(
      const grpc::string& target,
      const std::shared_ptr<ChannelCredentials>& creds,
      const grpc::ChannelArguments& args,
      std::vector<std::unique_ptr<
          grpc::experimental::ClientInterceptorFactoryInterface>>
          interceptor_creators);

  virtual std::shared_ptr<::grpc_impl::Channel> CreateChannel(
      const grpc::string& target, const ChannelArguments& args) = 0;

  // This function should have been a pure virtual function, but it is
  // implemented as a virtual function so that it does not break API.
  virtual std::shared_ptr<::grpc_impl::Channel> CreateChannelWithInterceptors(
      const grpc::string& target, const ChannelArguments& args,
      std::vector<
          std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
          interceptor_creators) {
    return nullptr;
  }
};

/// A call credentials object encapsulates the state needed by a client to
/// authenticate with a server for a given call on a channel.
///
/// \see https://grpc.io/docs/guides/auth.html
class CallCredentials : private GrpcLibraryCodegen {
 public:
  CallCredentials();
  ~CallCredentials();

  /// Apply this instance's credentials to \a call.
  virtual bool ApplyToCall(grpc_call* call) = 0;

 protected:
  friend std::shared_ptr<ChannelCredentials> CompositeChannelCredentials(
      const std::shared_ptr<ChannelCredentials>& channel_creds,
      const std::shared_ptr<CallCredentials>& call_creds);

  friend std::shared_ptr<CallCredentials> CompositeCallCredentials(
      const std::shared_ptr<CallCredentials>& creds1,
      const std::shared_ptr<CallCredentials>& creds2);

  virtual SecureCallCredentials* AsSecureCredentials() = 0;
};

/// Options used to build SslCredentials.
struct SslCredentialsOptions {
  /// The buffer containing the PEM encoding of the server root certificates. If
  /// this parameter is empty, the default roots will be used.  The default
  /// roots can be overridden using the \a GRPC_DEFAULT_SSL_ROOTS_FILE_PATH
  /// environment variable pointing to a file on the file system containing the
  /// roots.
  grpc::string pem_root_certs;
>>>>>>> master

typedef ::grpc_impl::ChannelCredentials ChannelCredentials;
typedef ::grpc_impl::CallCredentials CallCredentials;
typedef ::grpc_impl::SslCredentialsOptions SslCredentialsOptions;
typedef ::grpc_impl::SecureCallCredentials SecureCallCredentials;
typedef ::grpc_impl::SecureChannelCredentials SecureChannelCredentials;

static inline std::shared_ptr<grpc_impl::ChannelCredentials>
GoogleDefaultCredentials() {
  return ::grpc_impl::GoogleDefaultCredentials();
}

static inline std::shared_ptr<ChannelCredentials> SslCredentials(
    const SslCredentialsOptions& options) {
  return ::grpc_impl::SslCredentials(options);
}

static inline std::shared_ptr<grpc_impl::CallCredentials>
GoogleComputeEngineCredentials() {
  return ::grpc_impl::GoogleComputeEngineCredentials();
}

static inline std::shared_ptr<grpc_impl::CallCredentials>
ServiceAccountJWTAccessCredentials(
    const grpc::string& json_key,
    long token_lifetime_seconds = ::grpc_impl::kMaxAuthTokenLifetimeSecs) {
  return ::grpc_impl::ServiceAccountJWTAccessCredentials(
      json_key, token_lifetime_seconds);
}

static inline std::shared_ptr<grpc_impl::CallCredentials>
GoogleRefreshTokenCredentials(const grpc::string& json_refresh_token) {
  return ::grpc_impl::GoogleRefreshTokenCredentials(json_refresh_token);
}

static inline std::shared_ptr<grpc_impl::CallCredentials>
AccessTokenCredentials(const grpc::string& access_token) {
  return ::grpc_impl::AccessTokenCredentials(access_token);
}

static inline std::shared_ptr<grpc_impl::CallCredentials> GoogleIAMCredentials(
    const grpc::string& authorization_token,
    const grpc::string& authority_selector) {
  return ::grpc_impl::GoogleIAMCredentials(authorization_token,
                                           authority_selector);
}

static inline std::shared_ptr<ChannelCredentials> CompositeChannelCredentials(
    const std::shared_ptr<ChannelCredentials>& channel_creds,
    const std::shared_ptr<CallCredentials>& call_creds) {
  return ::grpc_impl::CompositeChannelCredentials(channel_creds, call_creds);
}

static inline std::shared_ptr<grpc_impl::CallCredentials>
CompositeCallCredentials(const std::shared_ptr<CallCredentials>& creds1,
                         const std::shared_ptr<CallCredentials>& creds2) {
  return ::grpc_impl::CompositeCallCredentials(creds1, creds2);
}

static inline std::shared_ptr<grpc_impl::ChannelCredentials>
InsecureChannelCredentials() {
  return ::grpc_impl::InsecureChannelCredentials();
}

static inline std::shared_ptr<grpc_impl::ChannelCredentials>
CronetChannelCredentials(void* engine) {
  return ::grpc_impl::CronetChannelCredentials(engine);
}

typedef ::grpc_impl::MetadataCredentialsPlugin MetadataCredentialsPlugin;

static inline std::shared_ptr<grpc_impl::CallCredentials>
MetadataCredentialsFromPlugin(
    std::unique_ptr<MetadataCredentialsPlugin> plugin) {
  return ::grpc_impl::MetadataCredentialsFromPlugin(std::move(plugin));
}

namespace experimental {

typedef ::grpc_impl::experimental::AltsCredentialsOptions
    AltsCredentialsOptions;

static inline std::shared_ptr<grpc_impl::ChannelCredentials> AltsCredentials(
    const AltsCredentialsOptions& options) {
  return ::grpc_impl::experimental::AltsCredentials(options);
}

static inline std::shared_ptr<grpc_impl::ChannelCredentials> LocalCredentials(
    grpc_local_connect_type type) {
  return ::grpc_impl::experimental::LocalCredentials(type);
}

}  // namespace experimental
}  // namespace grpc

#endif  // GRPCPP_SECURITY_CREDENTIALS_H
