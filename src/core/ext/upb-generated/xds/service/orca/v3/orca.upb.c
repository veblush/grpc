/* This file was generated by upbc (the upb compiler) from the input
 * file:
 *
 *     xds/service/orca/v3/orca.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated. */

#include <stddef.h>
#include "upb/generated_code_support.h"
#include "xds/service/orca/v3/orca.upb.h"
#include "xds/data/orca/v3/orca_load_report.upb.h"
#include "google/protobuf/duration.upb.h"

// Must be last.
#include "upb/port/def.inc"

static const upb_MiniTableSub xds_service_orca_v3_OrcaLoadReportRequest_submsgs[1] = {
  {.submsg = &google_protobuf_Duration_msg_init},
};

static const upb_MiniTableField xds_service_orca_v3_OrcaLoadReportRequest__fields[2] = {
  {1, UPB_SIZE(4, 8), 1, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds_service_orca_v3_OrcaLoadReportRequest_msg_init = {
  &xds_service_orca_v3_OrcaLoadReportRequest_submsgs[0],
  &xds_service_orca_v3_OrcaLoadReportRequest__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800000100000a, &upb_psm_1bt_maxmaxb},
    {0x001000003f000012, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

static const upb_MiniTable *messages_layout[1] = {
  &xds_service_orca_v3_OrcaLoadReportRequest_msg_init,
};

const upb_MiniTableFile xds_service_orca_v3_orca_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"

