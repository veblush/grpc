/* This file was generated by upb_generator from the input file:
 *
 *     envoy/extensions/transport_sockets/http_11_proxy/v3/upstream_http_11_connect.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated.
 * NO CHECKED-IN PROTOBUF GENCODE */

#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/extensions/transport_sockets/http_11_proxy/v3/upstream_http_11_connect.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

// Must be last.
#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TransportSocket_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__http_011_0proxy__v3__Http11ProxyUpstreamTransport_msg_init = {
  &envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport__submsgs[0],
  &envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.http_11_proxy.v3.Http11ProxyUpstreamTransport",
#endif
};

const upb_MiniTable* envoy__extensions__transport_0sockets__http_011_0proxy__v3__Http11ProxyUpstreamTransport_msg_init_ptr = &envoy__extensions__transport_0sockets__http_011_0proxy__v3__Http11ProxyUpstreamTransport_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &envoy__extensions__transport_0sockets__http_011_0proxy__v3__Http11ProxyUpstreamTransport_msg_init,
};

const upb_MiniTableFile envoy_extensions_transport_sockets_http_11_proxy_v3_upstream_http_11_connect_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
