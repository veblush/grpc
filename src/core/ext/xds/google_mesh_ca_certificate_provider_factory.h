//
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
//

#ifndef GRPC_CORE_EXT_XDS_GOOGLE_MESH_CA_CERTIFICATE_PROVIDER_FACTORY_H
#define GRPC_CORE_EXT_XDS_GOOGLE_MESH_CA_CERTIFICATE_PROVIDER_FACTORY_H

#include <grpc/support/port_platform.h>

#include <stdint.h>

#include <string>
#include <vector>

#include <grpc/grpc_security.h>

#include "src/core/ext/xds/certificate_provider_factory.h"
#include "src/core/lib/gprpp/ref_counted_ptr.h"
#include "src/core/lib/gprpp/time.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/json/json.h"
#include "src/core/lib/security/credentials/tls/grpc_tls_certificate_provider.h"

namespace grpc_core {

class GoogleMeshCaCertificateProviderFactory
    : public CertificateProviderFactory {
 public:
  class Config : public CertificateProviderFactory::Config {
   public:
    struct StsConfig {
      std::string token_exchange_service_uri;
      std::string resource;
      std::string audience;
      std::string scope;
      std::string requested_token_type;
      std::string subject_token_path;
      std::string subject_token_type;
      std::string actor_token_path;
      std::string actor_token_type;
    };

    const char* name() const override;

    std::string ToString() const override;

    const std::string& endpoint() const { return endpoint_; }

    const StsConfig& sts_config() const { return sts_config_; }

    Duration timeout() const { return timeout_; }

    Duration certificate_lifetime() const { return certificate_lifetime_; }

    Duration renewal_grace_period() const { return renewal_grace_period_; }

    uint32_t key_size() const { return key_size_; }

    const std::string& location() const { return location_; }

    static RefCountedPtr<Config> Parse(const Json& config_json,
                                       absl::Status* error);

   private:
    // Helpers for parsing the config
    std::vector<absl::Status> ParseJsonObjectStsService(
        const Json::Object& sts_service);
    std::vector<absl::Status> ParseJsonObjectCallCredentials(
        const Json::Object& call_credentials);
    std::vector<absl::Status> ParseJsonObjectGoogleGrpc(
        const Json::Object& google_grpc);
    std::vector<absl::Status> ParseJsonObjectGrpcServices(
        const Json::Object& grpc_service);
    std::vector<absl::Status> ParseJsonObjectServer(const Json::Object& server);

    std::string endpoint_;
    StsConfig sts_config_;
    Duration timeout_;
    Duration certificate_lifetime_;
    Duration renewal_grace_period_;
    uint32_t key_size_;
    std::string location_;
  };

  const char* name() const override;

  RefCountedPtr<CertificateProviderFactory::Config>
  CreateCertificateProviderConfig(const Json& config_json,
                                  absl::Status* error) override;

  RefCountedPtr<grpc_tls_certificate_provider> CreateCertificateProvider(
      RefCountedPtr<CertificateProviderFactory::Config> /*config*/) override {
    // TODO(yashykt) : To be implemented
    return nullptr;
  }
};

}  // namespace grpc_core

#endif  // GRPC_CORE_EXT_XDS_GOOGLE_MESH_CA_CERTIFICATE_PROVIDER_FACTORY_H
