/* This file was generated by upb_generator from the input file:
 *
 *     envoy/config/route/v3/scoped_route.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated.
 * NO CHECKED-IN PROTOBUF GENCODE */

#ifndef ENVOY_CONFIG_ROUTE_V3_SCOPED_ROUTE_PROTO_UPB_H_
#define ENVOY_CONFIG_ROUTE_V3_SCOPED_ROUTE_PROTO_UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/route/v3/scoped_route.upb_minitable.h"

#include "envoy/config/route/v3/route.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

// Must be last.
#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_route_v3_ScopedRouteConfiguration { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_ScopedRouteConfiguration;
typedef struct envoy_config_route_v3_ScopedRouteConfiguration_Key { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_ScopedRouteConfiguration_Key;
typedef struct envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment;
struct envoy_config_route_v3_RouteConfiguration;



/* envoy.config.route.v3.ScopedRouteConfiguration */

UPB_INLINE envoy_config_route_v3_ScopedRouteConfiguration* envoy_config_route_v3_ScopedRouteConfiguration_new(upb_Arena* arena) {
  return (envoy_config_route_v3_ScopedRouteConfiguration*)_upb_Message_New(&envoy__config__route__v3__ScopedRouteConfiguration_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_ScopedRouteConfiguration* envoy_config_route_v3_ScopedRouteConfiguration_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_ScopedRouteConfiguration* ret = envoy_config_route_v3_ScopedRouteConfiguration_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__ScopedRouteConfiguration_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_ScopedRouteConfiguration* envoy_config_route_v3_ScopedRouteConfiguration_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_ScopedRouteConfiguration* ret = envoy_config_route_v3_ScopedRouteConfiguration_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__ScopedRouteConfiguration_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_ScopedRouteConfiguration_serialize(const envoy_config_route_v3_ScopedRouteConfiguration* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__ScopedRouteConfiguration_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_ScopedRouteConfiguration_serialize_ex(const envoy_config_route_v3_ScopedRouteConfiguration* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__ScopedRouteConfiguration_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_ScopedRouteConfiguration_clear_name(envoy_config_route_v3_ScopedRouteConfiguration* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_ScopedRouteConfiguration_name(const envoy_config_route_v3_ScopedRouteConfiguration* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_ScopedRouteConfiguration_clear_route_configuration_name(envoy_config_route_v3_ScopedRouteConfiguration* msg) {
  const upb_MiniTableField field = {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_ScopedRouteConfiguration_route_configuration_name(const envoy_config_route_v3_ScopedRouteConfiguration* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_ScopedRouteConfiguration_clear_key(envoy_config_route_v3_ScopedRouteConfiguration* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_ScopedRouteConfiguration_Key* envoy_config_route_v3_ScopedRouteConfiguration_key(const envoy_config_route_v3_ScopedRouteConfiguration* msg) {
  const envoy_config_route_v3_ScopedRouteConfiguration_Key* default_val = NULL;
  const envoy_config_route_v3_ScopedRouteConfiguration_Key* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_ScopedRouteConfiguration_has_key(const envoy_config_route_v3_ScopedRouteConfiguration* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_ScopedRouteConfiguration_clear_on_demand(envoy_config_route_v3_ScopedRouteConfiguration* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 9), 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_ScopedRouteConfiguration_on_demand(const envoy_config_route_v3_ScopedRouteConfiguration* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 9), 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_ScopedRouteConfiguration_clear_route_configuration(envoy_config_route_v3_ScopedRouteConfiguration* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_route_v3_RouteConfiguration* envoy_config_route_v3_ScopedRouteConfiguration_route_configuration(const envoy_config_route_v3_ScopedRouteConfiguration* msg) {
  const struct envoy_config_route_v3_RouteConfiguration* default_val = NULL;
  const struct envoy_config_route_v3_RouteConfiguration* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(20, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_ScopedRouteConfiguration_has_route_configuration(const envoy_config_route_v3_ScopedRouteConfiguration* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_ScopedRouteConfiguration_set_name(envoy_config_route_v3_ScopedRouteConfiguration *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_ScopedRouteConfiguration_set_route_configuration_name(envoy_config_route_v3_ScopedRouteConfiguration *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_ScopedRouteConfiguration_set_key(envoy_config_route_v3_ScopedRouteConfiguration *msg, envoy_config_route_v3_ScopedRouteConfiguration_Key* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_ScopedRouteConfiguration_Key* envoy_config_route_v3_ScopedRouteConfiguration_mutable_key(envoy_config_route_v3_ScopedRouteConfiguration* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_ScopedRouteConfiguration_Key* sub = (struct envoy_config_route_v3_ScopedRouteConfiguration_Key*)envoy_config_route_v3_ScopedRouteConfiguration_key(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_ScopedRouteConfiguration_Key*)_upb_Message_New(&envoy__config__route__v3__ScopedRouteConfiguration__Key_msg_init, arena);
    if (sub) envoy_config_route_v3_ScopedRouteConfiguration_set_key(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_ScopedRouteConfiguration_set_on_demand(envoy_config_route_v3_ScopedRouteConfiguration *msg, bool value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 9), 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_ScopedRouteConfiguration_set_route_configuration(envoy_config_route_v3_ScopedRouteConfiguration *msg, struct envoy_config_route_v3_RouteConfiguration* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RouteConfiguration* envoy_config_route_v3_ScopedRouteConfiguration_mutable_route_configuration(envoy_config_route_v3_ScopedRouteConfiguration* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RouteConfiguration* sub = (struct envoy_config_route_v3_RouteConfiguration*)envoy_config_route_v3_ScopedRouteConfiguration_route_configuration(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RouteConfiguration*)_upb_Message_New(&envoy__config__route__v3__RouteConfiguration_msg_init, arena);
    if (sub) envoy_config_route_v3_ScopedRouteConfiguration_set_route_configuration(msg, sub);
  }
  return sub;
}

/* envoy.config.route.v3.ScopedRouteConfiguration.Key */

UPB_INLINE envoy_config_route_v3_ScopedRouteConfiguration_Key* envoy_config_route_v3_ScopedRouteConfiguration_Key_new(upb_Arena* arena) {
  return (envoy_config_route_v3_ScopedRouteConfiguration_Key*)_upb_Message_New(&envoy__config__route__v3__ScopedRouteConfiguration__Key_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_ScopedRouteConfiguration_Key* envoy_config_route_v3_ScopedRouteConfiguration_Key_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_ScopedRouteConfiguration_Key* ret = envoy_config_route_v3_ScopedRouteConfiguration_Key_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__ScopedRouteConfiguration__Key_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_ScopedRouteConfiguration_Key* envoy_config_route_v3_ScopedRouteConfiguration_Key_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_ScopedRouteConfiguration_Key* ret = envoy_config_route_v3_ScopedRouteConfiguration_Key_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__ScopedRouteConfiguration__Key_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_ScopedRouteConfiguration_Key_serialize(const envoy_config_route_v3_ScopedRouteConfiguration_Key* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__ScopedRouteConfiguration__Key_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_ScopedRouteConfiguration_Key_serialize_ex(const envoy_config_route_v3_ScopedRouteConfiguration_Key* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__ScopedRouteConfiguration__Key_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_ScopedRouteConfiguration_Key_clear_fragments(envoy_config_route_v3_ScopedRouteConfiguration_Key* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment* const* envoy_config_route_v3_ScopedRouteConfiguration_Key_fragments(const envoy_config_route_v3_ScopedRouteConfiguration_Key* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_ScopedRouteConfiguration_Key_fragments_upb_array(const envoy_config_route_v3_ScopedRouteConfiguration_Key* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_ScopedRouteConfiguration_Key_fragments_mutable_upb_array(envoy_config_route_v3_ScopedRouteConfiguration_Key* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment** envoy_config_route_v3_ScopedRouteConfiguration_Key_mutable_fragments(envoy_config_route_v3_ScopedRouteConfiguration_Key* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment** envoy_config_route_v3_ScopedRouteConfiguration_Key_resize_fragments(envoy_config_route_v3_ScopedRouteConfiguration_Key* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment* envoy_config_route_v3_ScopedRouteConfiguration_Key_add_fragments(envoy_config_route_v3_ScopedRouteConfiguration_Key* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment* sub = (struct envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment*)_upb_Message_New(&envoy__config__route__v3__ScopedRouteConfiguration__Key__Fragment_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

/* envoy.config.route.v3.ScopedRouteConfiguration.Key.Fragment */

UPB_INLINE envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment* envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_new(upb_Arena* arena) {
  return (envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment*)_upb_Message_New(&envoy__config__route__v3__ScopedRouteConfiguration__Key__Fragment_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment* envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment* ret = envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__ScopedRouteConfiguration__Key__Fragment_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment* envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment* ret = envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__ScopedRouteConfiguration__Key__Fragment_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_serialize(const envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__ScopedRouteConfiguration__Key__Fragment_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_serialize_ex(const envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__ScopedRouteConfiguration__Key__Fragment_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_type_string_key = 1,
  envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_type_NOT_SET = 0
} envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_type_oneofcases;
UPB_INLINE envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_type_oneofcases envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_type_case(const envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_clear_string_key(envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_string_key(const envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_has_string_key(const envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_set_string_key(envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}  /* extern "C" */
#endif

#include "upb/port/undef.inc"

#endif  /* ENVOY_CONFIG_ROUTE_V3_SCOPED_ROUTE_PROTO_UPB_H_ */
