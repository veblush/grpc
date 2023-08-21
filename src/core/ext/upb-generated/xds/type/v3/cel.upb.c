/* This file was generated by upbc (the upb compiler) from the input
 * file:
 *
 *     xds/type/v3/cel.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated. */

#include <stddef.h>
#include "upb/generated_code_support.h"
#include "xds/type/v3/cel.upb.h"
#include "google/api/expr/v1alpha1/checked.upb.h"
#include "google/api/expr/v1alpha1/syntax.upb.h"
#include "google/protobuf/wrappers.upb.h"
#include "xds/annotations/v3/status.upb.h"
#include "validate/validate.upb.h"

// Must be last.
#include "upb/port/def.inc"

static const upb_MiniTableSub xds_type_v3_CelExpression_submsgs[2] = {
  {.submsg = &google_api_expr_v1alpha1_ParsedExpr_msg_init},
  {.submsg = &google_api_expr_v1alpha1_CheckedExpr_msg_init},
};

static const upb_MiniTableField xds_type_v3_CelExpression__fields[2] = {
  {1, UPB_SIZE(4, 8), -1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(4, 8), -1, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds_type_v3_CelExpression_msg_init = {
  &xds_type_v3_CelExpression_submsgs[0],
  &xds_type_v3_CelExpression__fields[0],
  UPB_SIZE(8, 16), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800000100000a, &upb_pom_1bt_maxmaxb},
    {0x0008000002010012, &upb_pom_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTableSub xds_type_v3_CelExtractString_submsgs[2] = {
  {.submsg = &xds_type_v3_CelExpression_msg_init},
  {.submsg = &google_protobuf_StringValue_msg_init},
};

static const upb_MiniTableField xds_type_v3_CelExtractString__fields[2] = {
  {1, UPB_SIZE(4, 8), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 16), 2, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds_type_v3_CelExtractString_msg_init = {
  &xds_type_v3_CelExtractString_submsgs[0],
  &xds_type_v3_CelExtractString__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800000100000a, &upb_psm_1bt_max64b},
    {0x0010000002010012, &upb_psm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTable *messages_layout[2] = {
  &xds_type_v3_CelExpression_msg_init,
  &xds_type_v3_CelExtractString_msg_init,
};

const upb_MiniTableFile xds_type_v3_cel_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"

