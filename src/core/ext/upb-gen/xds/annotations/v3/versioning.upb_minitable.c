/* This file was generated by upb_generator from the input file:
 *
 *     xds/annotations/v3/versioning.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated.
 * NO CHECKED-IN PROTOBUF GENCODE */

#include <stddef.h>
#include "upb/generated_code_support.h"
#include "xds/annotations/v3/versioning.upb_minitable.h"
#include "google/protobuf/descriptor.upb_minitable.h"

// Must be last.
#include "upb/port/def.inc"

static const upb_MiniTableField xds_annotations_v3_VersioningAnnotation__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__annotations__v3__VersioningAnnotation_msg_init = {
  NULL,
  &xds_annotations_v3_VersioningAnnotation__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.annotations.v3.VersioningAnnotation",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

static const upb_MiniTable *messages_layout[1] = {
  &xds__annotations__v3__VersioningAnnotation_msg_init,
};

const upb_MiniTableExtension xds_annotations_v3_versioning_ext = {
  {92389011, 0, 0, 0, 11, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  &google__protobuf__MessageOptions_msg_init,
  {.UPB_PRIVATE(submsg) = &xds__annotations__v3__VersioningAnnotation_msg_init},

};

static const upb_MiniTableExtension *extensions_layout[1] = {
  &xds_annotations_v3_versioning_ext,
};

const upb_MiniTableFile xds_annotations_v3_versioning_proto_upb_file_layout = {
  messages_layout,
  NULL,
  extensions_layout,
  1,
  0,
  1,
};

#include "upb/port/undef.inc"

