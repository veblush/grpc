/* This file was generated by upbc (the upb compiler) from the input
 * file:
 *
 *     envoy/extensions/load_balancing_policies/common/v3/common.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated. */

#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/extensions/load_balancing_policies/common/v3/common.upb.h"
#include "envoy/config/core/v3/base.upb.h"
#include "envoy/type/v3/percent.upb.h"
#include "google/protobuf/duration.upb.h"
#include "google/protobuf/wrappers.upb.h"
#include "udpa/annotations/status.upb.h"
#include "validate/validate.upb.h"

// Must be last.
#include "upb/port/def.inc"

static const upb_MiniTableSub envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_submsgs[2] = {
  {.submsg = &envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_msg_init},
  {.submsg = &envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig_msg_init},
};

static const upb_MiniTableField envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig__fields[2] = {
  {1, UPB_SIZE(4, 8), -1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(4, 8), -1, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_msg_init = {
  &envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_submsgs[0],
  &envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig__fields[0],
  UPB_SIZE(8, 16), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800000100000a, &upb_pom_1bt_max64b},
    {0x0008000002010012, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTableSub envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_submsgs[2] = {
  {.submsg = &envoy_type_v3_Percent_msg_init},
  {.submsg = &google_protobuf_UInt64Value_msg_init},
};

static const upb_MiniTableField envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig__fields[3] = {
  {1, UPB_SIZE(4, 8), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 16), 2, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 1), 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_msg_init = {
  &envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_submsgs[0],
  &envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig__fields[0],
  UPB_SIZE(16, 24), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800000100000a, &upb_psm_1bt_maxmaxb},
    {0x0010000002010012, &upb_psm_1bt_maxmaxb},
    {0x000100003f000018, &upb_psb1_1bt},
  })
};

const upb_MiniTable envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig_msg_init = {
  NULL,
  NULL,
  0, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
};

static const upb_MiniTableSub envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_submsgs[3] = {
  {.submsg = &google_protobuf_Duration_msg_init},
  {.submsg = &envoy_config_core_v3_RuntimeDouble_msg_init},
  {.submsg = &envoy_type_v3_Percent_msg_init},
};

static const upb_MiniTableField envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig__fields[3] = {
  {1, UPB_SIZE(4, 8), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 16), 2, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 24), 3, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_msg_init = {
  &envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_submsgs[0],
  &envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig__fields[0],
  UPB_SIZE(16, 32), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800000100000a, &upb_psm_1bt_maxmaxb},
    {0x0010000002010012, &upb_psm_1bt_maxmaxb},
    {0x001800000302001a, &upb_psm_1bt_maxmaxb},
  })
};

static const upb_MiniTableSub envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_submsgs[1] = {
  {.submsg = &google_protobuf_UInt32Value_msg_init},
};

static const upb_MiniTableField envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig__fields[2] = {
  {1, 1, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(4, 8), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_msg_init = {
  &envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_submsgs[0],
  &envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig__fields[0],
  UPB_SIZE(8, 16), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000100003f000008, &upb_psb1_1bt},
    {0x0008000001000012, &upb_psm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTable *messages_layout[5] = {
  &envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_msg_init,
  &envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_msg_init,
  &envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig_msg_init,
  &envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_msg_init,
  &envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_msg_init,
};

const upb_MiniTableFile envoy_extensions_load_balancing_policies_common_v3_common_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  5,
  0,
  0,
};

#include "upb/port/undef.inc"

