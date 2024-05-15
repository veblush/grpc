/* This file was generated by upb_generator from the input file:
 *
 *     envoy/config/core/v3/socket_option.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated.
 * NO CHECKED-IN PROTOBUF GENCODE */

#ifndef ENVOY_CONFIG_CORE_V3_SOCKET_OPTION_PROTO_UPB_H_
#define ENVOY_CONFIG_CORE_V3_SOCKET_OPTION_PROTO_UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/core/v3/socket_option.upb_minitable.h"

#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

// Must be last.
#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_core_v3_SocketOption { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_SocketOption;
typedef struct envoy_config_core_v3_SocketOptionsOverride { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_SocketOptionsOverride;

typedef enum {
  envoy_config_core_v3_SocketOption_STATE_PREBIND = 0,
  envoy_config_core_v3_SocketOption_STATE_BOUND = 1,
  envoy_config_core_v3_SocketOption_STATE_LISTENING = 2
} envoy_config_core_v3_SocketOption_SocketState;



/* envoy.config.core.v3.SocketOption */

UPB_INLINE envoy_config_core_v3_SocketOption* envoy_config_core_v3_SocketOption_new(upb_Arena* arena) {
  return (envoy_config_core_v3_SocketOption*)_upb_Message_New(&envoy__config__core__v3__SocketOption_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_SocketOption* envoy_config_core_v3_SocketOption_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_SocketOption* ret = envoy_config_core_v3_SocketOption_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__SocketOption_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_SocketOption* envoy_config_core_v3_SocketOption_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_SocketOption* ret = envoy_config_core_v3_SocketOption_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__SocketOption_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_SocketOption_serialize(const envoy_config_core_v3_SocketOption* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__SocketOption_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_SocketOption_serialize_ex(const envoy_config_core_v3_SocketOption* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__SocketOption_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_SocketOption_value_int_value = 4,
  envoy_config_core_v3_SocketOption_value_buf_value = 5,
  envoy_config_core_v3_SocketOption_value_NOT_SET = 0
} envoy_config_core_v3_SocketOption_value_oneofcases;
UPB_INLINE envoy_config_core_v3_SocketOption_value_oneofcases envoy_config_core_v3_SocketOption_value_case(const envoy_config_core_v3_SocketOption* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 16), -9, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_SocketOption_value_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_SocketOption_clear_description(envoy_config_core_v3_SocketOption* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(16, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_SocketOption_description(const envoy_config_core_v3_SocketOption* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(16, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_SocketOption_clear_level(envoy_config_core_v3_SocketOption* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 48), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t envoy_config_core_v3_SocketOption_level(const envoy_config_core_v3_SocketOption* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(24, 48), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_SocketOption_clear_name(envoy_config_core_v3_SocketOption* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(32, 56), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t envoy_config_core_v3_SocketOption_name(const envoy_config_core_v3_SocketOption* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(32, 56), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_SocketOption_clear_int_value(envoy_config_core_v3_SocketOption* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 16), -9, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t envoy_config_core_v3_SocketOption_int_value(const envoy_config_core_v3_SocketOption* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {4, UPB_SIZE(40, 16), -9, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_SocketOption_has_int_value(const envoy_config_core_v3_SocketOption* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 16), -9, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_SocketOption_clear_buf_value(envoy_config_core_v3_SocketOption* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 16), -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_SocketOption_buf_value(const envoy_config_core_v3_SocketOption* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {5, UPB_SIZE(40, 16), -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_SocketOption_has_buf_value(const envoy_config_core_v3_SocketOption* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 16), -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_SocketOption_clear_state(envoy_config_core_v3_SocketOption* msg) {
  const upb_MiniTableField field = {6, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_core_v3_SocketOption_state(const envoy_config_core_v3_SocketOption* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {6, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_SocketOption_set_description(envoy_config_core_v3_SocketOption *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(16, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_SocketOption_set_level(envoy_config_core_v3_SocketOption *msg, int64_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 48), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_SocketOption_set_name(envoy_config_core_v3_SocketOption *msg, int64_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(32, 56), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_SocketOption_set_int_value(envoy_config_core_v3_SocketOption *msg, int64_t value) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 16), -9, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_SocketOption_set_buf_value(envoy_config_core_v3_SocketOption *msg, upb_StringView value) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 16), -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_SocketOption_set_state(envoy_config_core_v3_SocketOption *msg, int32_t value) {
  const upb_MiniTableField field = {6, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

/* envoy.config.core.v3.SocketOptionsOverride */

UPB_INLINE envoy_config_core_v3_SocketOptionsOverride* envoy_config_core_v3_SocketOptionsOverride_new(upb_Arena* arena) {
  return (envoy_config_core_v3_SocketOptionsOverride*)_upb_Message_New(&envoy__config__core__v3__SocketOptionsOverride_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_SocketOptionsOverride* envoy_config_core_v3_SocketOptionsOverride_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_SocketOptionsOverride* ret = envoy_config_core_v3_SocketOptionsOverride_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__SocketOptionsOverride_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_SocketOptionsOverride* envoy_config_core_v3_SocketOptionsOverride_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_SocketOptionsOverride* ret = envoy_config_core_v3_SocketOptionsOverride_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__SocketOptionsOverride_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_SocketOptionsOverride_serialize(const envoy_config_core_v3_SocketOptionsOverride* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__SocketOptionsOverride_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_SocketOptionsOverride_serialize_ex(const envoy_config_core_v3_SocketOptionsOverride* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__SocketOptionsOverride_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_SocketOptionsOverride_clear_socket_options(envoy_config_core_v3_SocketOptionsOverride* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_SocketOption* const* envoy_config_core_v3_SocketOptionsOverride_socket_options(const envoy_config_core_v3_SocketOptionsOverride* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_core_v3_SocketOption* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_SocketOptionsOverride_socket_options_upb_array(const envoy_config_core_v3_SocketOptionsOverride* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_SocketOptionsOverride_socket_options_mutable_upb_array(envoy_config_core_v3_SocketOptionsOverride* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_core_v3_SocketOption** envoy_config_core_v3_SocketOptionsOverride_mutable_socket_options(envoy_config_core_v3_SocketOptionsOverride* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_core_v3_SocketOption**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_core_v3_SocketOption** envoy_config_core_v3_SocketOptionsOverride_resize_socket_options(envoy_config_core_v3_SocketOptionsOverride* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_SocketOption**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_SocketOption* envoy_config_core_v3_SocketOptionsOverride_add_socket_options(envoy_config_core_v3_SocketOptionsOverride* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_SocketOption* sub = (struct envoy_config_core_v3_SocketOption*)_upb_Message_New(&envoy__config__core__v3__SocketOption_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

#ifdef __cplusplus
}  /* extern "C" */
#endif

#include "upb/port/undef.inc"

#endif  /* ENVOY_CONFIG_CORE_V3_SOCKET_OPTION_PROTO_UPB_H_ */
