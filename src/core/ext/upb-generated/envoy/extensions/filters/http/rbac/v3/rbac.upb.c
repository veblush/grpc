/* This file was generated by upbc (the upb compiler) from the input
 * file:
 *
 *     envoy/extensions/filters/http/rbac/v3/rbac.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated. */

#include <stddef.h>
#include "upb/msg_internal.h"
#include "envoy/extensions/filters/http/rbac/v3/rbac.upb.h"
#include "envoy/config/rbac/v3/rbac.upb.h"
#include "udpa/annotations/status.upb.h"
#include "udpa/annotations/versioning.upb.h"

#include "upb/port_def.inc"

static const upb_MiniTable_Sub envoy_extensions_filters_http_rbac_v3_RBAC_submsgs[1] = {
  {.submsg = &envoy_config_rbac_v3_RBAC_msginit},
};

static const upb_MiniTable_Field envoy_extensions_filters_http_rbac_v3_RBAC__fields[3] = {
  {1, UPB_SIZE(12, 24), 1, 0, 11, kUpb_FieldMode_Scalar | (upb_FieldRep_Pointer << upb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 32), 2, 0, 11, kUpb_FieldMode_Scalar | (upb_FieldRep_Pointer << upb_FieldRep_Shift)},
  {3, UPB_SIZE(4, 8), 0, 0, 9, kUpb_FieldMode_Scalar | (upb_FieldRep_StringView << upb_FieldRep_Shift)},
};

const upb_MiniTable envoy_extensions_filters_http_rbac_v3_RBAC_msginit = {
  &envoy_extensions_filters_http_rbac_v3_RBAC_submsgs[0],
  &envoy_extensions_filters_http_rbac_v3_RBAC__fields[0],
  UPB_SIZE(24, 48), 3, upb_ExtMode_NonExtendable, 3, 255, 0,
};

static const upb_MiniTable_Sub envoy_extensions_filters_http_rbac_v3_RBACPerRoute_submsgs[1] = {
  {.submsg = &envoy_extensions_filters_http_rbac_v3_RBAC_msginit},
};

static const upb_MiniTable_Field envoy_extensions_filters_http_rbac_v3_RBACPerRoute__fields[1] = {
  {2, UPB_SIZE(4, 8), 1, 0, 11, kUpb_FieldMode_Scalar | (upb_FieldRep_Pointer << upb_FieldRep_Shift)},
};

const upb_MiniTable envoy_extensions_filters_http_rbac_v3_RBACPerRoute_msginit = {
  &envoy_extensions_filters_http_rbac_v3_RBACPerRoute_submsgs[0],
  &envoy_extensions_filters_http_rbac_v3_RBACPerRoute__fields[0],
  UPB_SIZE(8, 16), 1, upb_ExtMode_NonExtendable, 0, 255, 0,
};

static const upb_MiniTable *messages_layout[2] = {
  &envoy_extensions_filters_http_rbac_v3_RBAC_msginit,
  &envoy_extensions_filters_http_rbac_v3_RBACPerRoute_msginit,
};

const upb_MiniTable_File envoy_extensions_filters_http_rbac_v3_rbac_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port_undef.inc"

