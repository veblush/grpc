/* This file was generated by upbc (the upb compiler) from the input
 * file:
 *
 *     envoy/admin/v3/config_dump.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated. */

#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/admin/v3/config_dump.upb.h"
#include "envoy/admin/v3/config_dump_shared.upb.h"
#include "envoy/config/bootstrap/v3/bootstrap.upb.h"
#include "google/protobuf/any.upb.h"
#include "google/protobuf/timestamp.upb.h"
#include "udpa/annotations/status.upb.h"
#include "udpa/annotations/versioning.upb.h"

// Must be last.
#include "upb/port/def.inc"

static const upb_MiniTableSub envoy_admin_v3_ConfigDump_submsgs[1] = {
  {.submsg = &google_protobuf_Any_msg_init},
};

static const upb_MiniTableField envoy_admin_v3_ConfigDump__fields[1] = {
  {1, 0, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_admin_v3_ConfigDump_msg_init = {
  &envoy_admin_v3_ConfigDump_submsgs[0],
  &envoy_admin_v3_ConfigDump__fields[0],
  8, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000000003f00000a, &upb_prm_1bt_maxmaxb},
  })
};

static const upb_MiniTableSub envoy_admin_v3_BootstrapConfigDump_submsgs[2] = {
  {.submsg = &envoy_config_bootstrap_v3_Bootstrap_msg_init},
  {.submsg = &google_protobuf_Timestamp_msg_init},
};

static const upb_MiniTableField envoy_admin_v3_BootstrapConfigDump__fields[2] = {
  {1, UPB_SIZE(4, 8), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 16), 2, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_admin_v3_BootstrapConfigDump_msg_init = {
  &envoy_admin_v3_BootstrapConfigDump_submsgs[0],
  &envoy_admin_v3_BootstrapConfigDump__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800000100000a, &upb_psm_1bt_maxmaxb},
    {0x0010000002010012, &upb_psm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTableSub envoy_admin_v3_SecretsConfigDump_submsgs[3] = {
  {.submsg = &envoy_admin_v3_SecretsConfigDump_StaticSecret_msg_init},
  {.submsg = &envoy_admin_v3_SecretsConfigDump_DynamicSecret_msg_init},
  {.submsg = &envoy_admin_v3_SecretsConfigDump_DynamicSecret_msg_init},
};

static const upb_MiniTableField envoy_admin_v3_SecretsConfigDump__fields[3] = {
  {1, 0, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(4, 8), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(8, 16), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_admin_v3_SecretsConfigDump_msg_init = {
  &envoy_admin_v3_SecretsConfigDump_submsgs[0],
  &envoy_admin_v3_SecretsConfigDump__fields[0],
  UPB_SIZE(16, 24), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000000003f00000a, &upb_prm_1bt_max64b},
    {0x000800003f010012, &upb_prm_1bt_max128b},
    {0x001000003f02001a, &upb_prm_1bt_max128b},
  })
};

static const upb_MiniTableSub envoy_admin_v3_SecretsConfigDump_DynamicSecret_submsgs[3] = {
  {.submsg = &google_protobuf_Timestamp_msg_init},
  {.submsg = &google_protobuf_Any_msg_init},
  {.submsg = &envoy_admin_v3_UpdateFailureState_msg_init},
};

static const upb_MiniTableField envoy_admin_v3_SecretsConfigDump_DynamicSecret__fields[6] = {
  {1, UPB_SIZE(20, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(28, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(4, 40), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(8, 48), 2, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 56), 3, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(16, 4), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_admin_v3_SecretsConfigDump_DynamicSecret_msg_init = {
  &envoy_admin_v3_SecretsConfigDump_DynamicSecret_submsgs[0],
  &envoy_admin_v3_SecretsConfigDump_DynamicSecret__fields[0],
  UPB_SIZE(40, 64), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_pss_1bt},
    {0x002800000100001a, &upb_psm_1bt_maxmaxb},
    {0x0030000002010022, &upb_psm_1bt_maxmaxb},
    {0x003800000302002a, &upb_psm_1bt_maxmaxb},
    {0x000400003f000030, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTableSub envoy_admin_v3_SecretsConfigDump_StaticSecret_submsgs[2] = {
  {.submsg = &google_protobuf_Timestamp_msg_init},
  {.submsg = &google_protobuf_Any_msg_init},
};

static const upb_MiniTableField envoy_admin_v3_SecretsConfigDump_StaticSecret__fields[3] = {
  {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(4, 24), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(8, 32), 2, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy_admin_v3_SecretsConfigDump_StaticSecret_msg_init = {
  &envoy_admin_v3_SecretsConfigDump_StaticSecret_submsgs[0],
  &envoy_admin_v3_SecretsConfigDump_StaticSecret__fields[0],
  UPB_SIZE(24, 40), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x0018000001000012, &upb_psm_1bt_maxmaxb},
    {0x002000000201001a, &upb_psm_1bt_maxmaxb},
  })
};

static const upb_MiniTable *messages_layout[5] = {
  &envoy_admin_v3_ConfigDump_msg_init,
  &envoy_admin_v3_BootstrapConfigDump_msg_init,
  &envoy_admin_v3_SecretsConfigDump_msg_init,
  &envoy_admin_v3_SecretsConfigDump_DynamicSecret_msg_init,
  &envoy_admin_v3_SecretsConfigDump_StaticSecret_msg_init,
};

const upb_MiniTableFile envoy_admin_v3_config_dump_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  5,
  0,
  0,
};

#include "upb/port/undef.inc"

