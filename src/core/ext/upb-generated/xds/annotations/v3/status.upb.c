/* This file was generated by upbc (the upb compiler) from the input
 * file:
 *
 *     xds/annotations/v3/status.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated. */

#include <stddef.h>
#include "upb/generated_code_support.h"
#include "xds/annotations/v3/status.upb.h"
#include "google/protobuf/descriptor.upb.h"

// Must be last.
#include "upb/port/def.inc"

static const upb_MiniTableField xds_annotations_v3_FileStatusAnnotation__fields[1] = {
  {1, 0, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds_annotations_v3_FileStatusAnnotation_msg_init = {
  NULL,
  &xds_annotations_v3_FileStatusAnnotation__fields[0],
  8, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000000003f000008, &upb_psb1_1bt},
  })
};

static const upb_MiniTableField xds_annotations_v3_MessageStatusAnnotation__fields[1] = {
  {1, 0, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds_annotations_v3_MessageStatusAnnotation_msg_init = {
  NULL,
  &xds_annotations_v3_MessageStatusAnnotation__fields[0],
  8, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000000003f000008, &upb_psb1_1bt},
  })
};

static const upb_MiniTableField xds_annotations_v3_FieldStatusAnnotation__fields[1] = {
  {1, 0, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds_annotations_v3_FieldStatusAnnotation_msg_init = {
  NULL,
  &xds_annotations_v3_FieldStatusAnnotation__fields[0],
  8, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000000003f000008, &upb_psb1_1bt},
  })
};

static const upb_MiniTableField xds_annotations_v3_StatusAnnotation__fields[2] = {
  {1, 0, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {2, 4, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds_annotations_v3_StatusAnnotation_msg_init = {
  NULL,
  &xds_annotations_v3_StatusAnnotation__fields[0],
  8, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000000003f000008, &upb_psb1_1bt},
    {0x000400003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTable *messages_layout[4] = {
  &xds_annotations_v3_FileStatusAnnotation_msg_init,
  &xds_annotations_v3_MessageStatusAnnotation_msg_init,
  &xds_annotations_v3_FieldStatusAnnotation_msg_init,
  &xds_annotations_v3_StatusAnnotation_msg_init,
};

extern const upb_MiniTable google_protobuf_FieldOptions_msg_init;
extern const upb_MiniTable google_protobuf_FileOptions_msg_init;
extern const upb_MiniTable google_protobuf_MessageOptions_msg_init;
extern const upb_MiniTable xds_annotations_v3_FieldStatusAnnotation_msg_init;
extern const upb_MiniTable xds_annotations_v3_FileStatusAnnotation_msg_init;
extern const upb_MiniTable xds_annotations_v3_MessageStatusAnnotation_msg_init;
const upb_MiniTableExtension xds_annotations_v3_file_status_ext = {
  {226829418, 0, 0, 0, 11, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  &google_protobuf_FileOptions_msg_init,
  {.submsg = &xds_annotations_v3_FileStatusAnnotation_msg_init},

};
const upb_MiniTableExtension xds_annotations_v3_message_status_ext = {
  {226829418, 0, 0, 0, 11, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  &google_protobuf_MessageOptions_msg_init,
  {.submsg = &xds_annotations_v3_MessageStatusAnnotation_msg_init},

};
const upb_MiniTableExtension xds_annotations_v3_field_status_ext = {
  {226829418, 0, 0, 0, 11, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  &google_protobuf_FieldOptions_msg_init,
  {.submsg = &xds_annotations_v3_FieldStatusAnnotation_msg_init},

};

static const upb_MiniTableExtension *extensions_layout[3] = {
  &xds_annotations_v3_file_status_ext,
  &xds_annotations_v3_message_status_ext,
  &xds_annotations_v3_field_status_ext,
};

const upb_MiniTableFile xds_annotations_v3_status_proto_upb_file_layout = {
  messages_layout,
  NULL,
  extensions_layout,
  4,
  0,
  3,
};

#include "upb/port/undef.inc"
