/* This file was generated by upbc (the upb compiler) from the input
 * file:
 *
 *     xds/core/v3/context_params.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated. */

#include <stddef.h>
#include "upb/collections/array_internal.h"
#include "upb/message/internal.h"
#include "upb/mini_table/enum_internal.h"
#include "xds/core/v3/context_params.upb.h"
#include "xds/annotations/v3/status.upb.h"

// Must be last.
#include "upb/port/def.inc"

static const upb_MiniTableSub xds_core_v3_ContextParams_submsgs[1] = {
  {.submsg = &xds_core_v3_ContextParams_ParamsEntry_msg_init},
};

static const upb_MiniTableField xds_core_v3_ContextParams__fields[1] = {
  {1, 0, 0, 0, 11, kUpb_FieldMode_Map | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds_core_v3_ContextParams_msg_init = {
  &xds_core_v3_ContextParams_submsgs[0],
  &xds_core_v3_ContextParams__fields[0],
  8, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
};

static const upb_MiniTableField xds_core_v3_ContextParams_ParamsEntry__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds_core_v3_ContextParams_ParamsEntry_msg_init = {
  NULL,
  &xds_core_v3_ContextParams_ParamsEntry__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTable *messages_layout[2] = {
  &xds_core_v3_ContextParams_msg_init,
  &xds_core_v3_ContextParams_ParamsEntry_msg_init,
};

const upb_MiniTableFile xds_core_v3_context_params_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"

