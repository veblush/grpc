/* This file was generated by upb_generator from the input file:
 *
 *     envoy/config/endpoint/v3/load_report.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated. */

#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/endpoint/v3/load_report.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

// Must be last.
#include "upb/port/def.inc"

static const upb_MiniTableSub envoy_config_endpoint_v3_UpstreamLocalityStats_submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Locality_msg_init},
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init},
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__UpstreamEndpointStats_msg_init},
};

static const upb_MiniTableField envoy_config_endpoint_v3_UpstreamLocalityStats__fields[11] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(32, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(40, 32), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(48, 40), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(20, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(24, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(56, 64), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(64, 72), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(72, 80), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(80, 88), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__endpoint__v3__UpstreamLocalityStats_msg_init = {
  &envoy_config_endpoint_v3_UpstreamLocalityStats_submsgs[0],
  &envoy_config_endpoint_v3_UpstreamLocalityStats__fields[0],
  UPB_SIZE(88, 96), 11, kUpb_ExtMode_NonExtendable, 11, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.endpoint.v3.UpstreamLocalityStats",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f000010, &upb_psv8_1bt},
    {0x002000003f000018, &upb_psv8_1bt},
    {0x002800003f000020, &upb_psv8_1bt},
    {0x003000003f01002a, &upb_prm_1bt_max64b},
    {0x000c00003f000030, &upb_psv4_1bt},
    {0x003800003f02003a, &upb_prm_1bt_max128b},
    {0x004000003f000040, &upb_psv8_1bt},
    {0x004800003f000048, &upb_psv8_1bt},
    {0x005000003f000050, &upb_psv8_1bt},
    {0x005800003f000058, &upb_psv8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTableSub envoy_config_endpoint_v3_UpstreamEndpointStats_submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init},
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Struct_msg_init},
};

static const upb_MiniTableField envoy_config_endpoint_v3_UpstreamEndpointStats__fields[7] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 24, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, 32, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {4, 40, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(20, 56), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(48, 64), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__endpoint__v3__UpstreamEndpointStats_msg_init = {
  &envoy_config_endpoint_v3_UpstreamEndpointStats_submsgs[0],
  &envoy_config_endpoint_v3_UpstreamEndpointStats__fields[0],
  UPB_SIZE(56, 72), 7, kUpb_ExtMode_NonExtendable, 7, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.endpoint.v3.UpstreamEndpointStats",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f000010, &upb_psv8_1bt},
    {0x002000003f000018, &upb_psv8_1bt},
    {0x002800003f000020, &upb_psv8_1bt},
    {0x003000003f01002a, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x004000003f000038, &upb_psv8_1bt},
  })
};

static const upb_MiniTableField envoy_config_endpoint_v3_EndpointLoadMetricStats__fields[3] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(24, 32), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init = {
  NULL,
  &envoy_config_endpoint_v3_EndpointLoadMetricStats__fields[0],
  UPB_SIZE(32, 40), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.endpoint.v3.EndpointLoadMetricStats",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000010, &upb_psv8_1bt},
    {0x002000003f000019, &upb_psf8_1bt},
  })
};

static const upb_MiniTableSub envoy_config_endpoint_v3_ClusterStats_submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__UpstreamLocalityStats_msg_init},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init},
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__ClusterStats__DroppedRequests_msg_init},
};

static const upb_MiniTableField envoy_config_endpoint_v3_ClusterStats__fields[6] = {
  {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(32, 40), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 48), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(40, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__endpoint__v3__ClusterStats_msg_init = {
  &envoy_config_endpoint_v3_ClusterStats_submsgs[0],
  &envoy_config_endpoint_v3_ClusterStats__fields[0],
  UPB_SIZE(48, 80), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.endpoint.v3.ClusterStats",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_prm_1bt_max128b},
    {0x002800003f000018, &upb_psv8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003800003f02002a, &upb_prm_1bt_max64b},
    {0x004000003f000032, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTableField envoy_config_endpoint_v3_ClusterStats_DroppedRequests__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__endpoint__v3__ClusterStats__DroppedRequests_msg_init = {
  NULL,
  &envoy_config_endpoint_v3_ClusterStats_DroppedRequests__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.endpoint.v3.ClusterStats.DroppedRequests",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000010, &upb_psv8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTable *messages_layout[5] = {
  &envoy__config__endpoint__v3__UpstreamLocalityStats_msg_init,
  &envoy__config__endpoint__v3__UpstreamEndpointStats_msg_init,
  &envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init,
  &envoy__config__endpoint__v3__ClusterStats_msg_init,
  &envoy__config__endpoint__v3__ClusterStats__DroppedRequests_msg_init,
};

const upb_MiniTableFile envoy_config_endpoint_v3_load_report_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  5,
  0,
  0,
};

#include "upb/port/undef.inc"

