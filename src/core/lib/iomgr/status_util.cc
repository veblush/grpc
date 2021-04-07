//
//
// Copyright 2021 the gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//

#include <grpc/support/port_platform.h>

#include "src/core/lib/gprpp/time_util.h"
#include "src/core/lib/iomgr/status_util.h"

#include "absl/strings/cord.h"
#include "absl/strings/escaping.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"

#include "google/protobuf/any.upb.h"
#include "google/rpc/status.upb.h"
#include "upb/upb.hpp"

#ifdef GPR_WINDOWS
#include <grpc/support/log_windows.h>
#endif

extern const char* error_int_name(grpc_error_ints key);
extern const char* error_str_name(grpc_error_strs key);

namespace grpc_core {

absl::Status StatusCreate(absl::StatusCode code, absl::string_view msg,
                          const char* file, int line,
                          std::initializer_list<absl::Status> children) {
  absl::Status s(code, msg);
  StatusSetStr(&s, GRPC_ERROR_STR_FILE, file);
  StatusSetInt(&s, GRPC_ERROR_INT_FILE_LINE, line);
  absl::Time now = grpc_core::ToAbslTime(gpr_now(GPR_CLOCK_REALTIME));
  s.SetPayload("created", absl::Cord(absl::FormatTime(now)));
  for (const absl::Status& child : children) {
    if (!child.ok()) {
      StatusAddChild(&s, child);
    }
  }
  return s;
}

void StatusSetInt(absl::Status* status, grpc_error_ints which, intptr_t value) {
  status->SetPayload(error_int_name(which), absl::Cord(std::to_string(value)));
}

absl::optional<intptr_t> StatusGetInt(const absl::Status& status,
                                      grpc_error_ints which) {
  absl::optional<absl::Cord> p = status.GetPayload(error_int_name(which));
  if (p.has_value()) {
    absl::optional<absl::string_view> sv = p->TryFlat();
    intptr_t value;
    if (sv.has_value()) {
      if (absl::SimpleAtoi(*sv, &value)) {
        return value;
      }
    } else {
      if (absl::SimpleAtoi(std::string(*p), &value)) {
        return value;
      }
    }
  }
  return {};
}

void StatusSetStr(absl::Status* status, grpc_error_strs which,
                  std::string value) {
  status->SetPayload(error_str_name(which), absl::Cord(value));
}

absl::optional<std::string> StatusGetStr(const absl::Status& status,
                                         grpc_error_strs which) {
  absl::optional<absl::Cord> p = status.GetPayload(error_str_name(which));
  if (p.has_value()) {
    return std::string(*p);
  }
  return {};
}

static void EncodeUInt32ToBytes(uint32_t v, char* buf) {
  buf[0] = v & 0xFF;
  buf[1] = (v >> 8) & 0xFF;
  buf[2] = (v >> 16) & 0xFF;
  buf[3] = (v >> 24) & 0xFF;
}

static uint32_t DecodeUInt32FromBytes(const char* buf) {
  return buf[0] | (uint32_t(buf[1]) << 8) | (uint32_t(buf[2]) << 16) |
         (uint32_t(buf[3]) << 24);
}

void StatusAddChild(absl::Status* status, absl::Status child) {
  upb::Arena arena;
  // Serialize msg to buf
  google_rpc_Status* msg = StatusToProto(child, arena.ptr());
  size_t buf_len = 0;
  char* buf = google_rpc_Status_serialize(msg, arena.ptr(), &buf_len);
  // Append (msg-length and msg) to children payload
  absl::optional<absl::Cord> old_children = status->GetPayload("children");
  absl::Cord children;
  if (old_children.has_value()) {
    children = *old_children;
  }
  char head_buf[sizeof(uint32_t)];
  EncodeUInt32ToBytes(buf_len, head_buf);
  children.Append(absl::string_view(head_buf, sizeof(uint32_t)));
  children.Append(absl::string_view(buf, buf_len));
  status->SetPayload("children", std::move(children));
}

static std::vector<absl::Status> ParseChildren(absl::Cord children) {
  std::vector<absl::Status> result;
  upb::Arena arena;
  // Cord is flattened to iterate the buffer easily at the cost of memory copy.
  // TODO(veblush): Optimize this once CordReader is introduced.
  absl::string_view buf = children.Flatten();
  size_t cur = 0;
  while (buf.size() - cur >= sizeof(uint32_t)) {
    size_t msg_size = DecodeUInt32FromBytes(buf.data() + cur);
    cur += sizeof(uint32_t);
    GPR_ASSERT(buf.size() - cur >= msg_size);
    google_rpc_Status* msg =
        google_rpc_Status_parse(buf.data() + cur, msg_size, arena.ptr());
    cur += msg_size;
    result.push_back(StatusFromProto(msg));
  }
  return result;
}

std::vector<absl::Status> StatusGetChildren(absl::Status status) {
  absl::optional<absl::Cord> children = status.GetPayload("children");
  return children.has_value() ? ParseChildren(*children)
                              : std::vector<absl::Status>();
}

google_rpc_Status* StatusToProto(absl::Status status, upb_arena* arena) {
  google_rpc_Status* msg = google_rpc_Status_new(arena);
  google_rpc_Status_set_code(msg, int32_t(status.code()));
  google_rpc_Status_set_message(
      msg, upb_strview_make(status.message().data(), status.message().size()));
  status.ForEachPayload([&](absl::string_view type_url,
                            const absl::Cord& payload) {
    google_protobuf_Any* any = google_rpc_Status_add_details(msg, arena);
    char* type_url_buf =
        reinterpret_cast<char*>(upb_arena_malloc(arena, type_url.size()));
    memcpy(type_url_buf, type_url.data(), type_url.size());
    google_protobuf_Any_set_type_url(
        any, upb_strview_make(type_url_buf, type_url.size()));
    absl::optional<absl::string_view> v_view = payload.TryFlat();
    if (v_view.has_value()) {
      google_protobuf_Any_set_value(
          any, upb_strview_make(v_view->data(), v_view->size()));
    } else {
      char* buf =
          reinterpret_cast<char*>(upb_arena_malloc(arena, payload.size()));
      char* cur = buf;
      for (absl::string_view chunk : payload.Chunks()) {
        memcpy(cur, chunk.data(), chunk.size());
        cur += chunk.size();
      }
      google_protobuf_Any_set_value(any, upb_strview_make(buf, payload.size()));
    }
  });
  return msg;
}

absl::Status StatusFromProto(google_rpc_Status* msg) {
  int32_t code = google_rpc_Status_code(msg);
  upb_strview message = google_rpc_Status_message(msg);
  absl::Status status(static_cast<absl::StatusCode>(code),
                      absl::string_view(message.data, message.size));
  size_t detail_len;
  const google_protobuf_Any* const* details =
      google_rpc_Status_details(msg, &detail_len);
  for (size_t i = 0; i < detail_len; i++) {
    upb_strview type_url = google_protobuf_Any_type_url(details[i]);
    upb_strview value = google_protobuf_Any_value(details[i]);
    status.SetPayload(absl::string_view(type_url.data, type_url.size),
                      absl::Cord(absl::string_view(value.data, value.size)));
  }
  return status;
}

std::string StatusToString(const absl::Status& status) {
  if (status.ok()) {
    return "OK";
  }
  std::string head;
  absl::StrAppend(&head, absl::StatusCodeToString(status.code()));
  if (!status.message().empty()) {
    absl::StrAppend(&head, ":", status.message());
  }
  std::vector<std::string> kvs;
  absl::optional<absl::Cord> children;
  status.ForEachPayload([&](absl::string_view type_url,
                            const absl::Cord& payload) {
    if (type_url == "children") {
      children = payload;
    } else {
      absl::optional<absl::string_view> payload_view = payload.TryFlat();
      std::string payload_str = absl::CHexEscape(
          payload_view.has_value() ? *payload_view : std::string(payload));
      kvs.push_back(absl::StrCat(type_url, ":'", std::move(payload_str), "'"));
    }
  });
  if (children.has_value()) {
    std::vector<absl::Status> children_status = ParseChildren(*children);
    std::vector<std::string> children_text;
    children_text.reserve(children_status.size());
    for (auto child_status : children_status) {
      children_text.push_back(StatusToString(child_status));
    }
    kvs.push_back(
        absl::StrCat("children:[", absl::StrJoin(children_text, ", "), "]"));
  }
  return kvs.empty() ? head
                     : absl::StrCat(head, " {", absl::StrJoin(kvs, ", "), "}");
}

absl::Status StatusCreateOS(const char* file, int line, int err,
                            const char* call_name) {
  absl::Status s =
      StatusCreate(absl::StatusCode::kInternal, strerror(err), file, line, {});
  StatusSetInt(&s, GRPC_ERROR_INT_ERRNO, err);
  StatusSetStr(&s, GRPC_ERROR_STR_OS_ERROR, strerror(err));
  StatusSetStr(&s, GRPC_ERROR_STR_SYSCALL, call_name);
  return s;
}

#ifdef GPR_WINDOWS
absl::Status StatusCreateWSA(const char* file, int line, int err,
                             const char* call_name) {
  absl::Status s =
      StatusCreate(absl::StatusCode::kInternal, "WSA Error", file, line, {});
  char* utf8_message = gpr_format_message(err);
  StatusSetInt(&s, GRPC_ERROR_INT_WSA_ERROR, err);
  StatusSetStr(&s, GRPC_ERROR_STR_OS_ERROR, utf8_message);
  StatusSetStr(&s, GRPC_ERROR_STR_SYSCALL, call_name);
  return s;
}
#endif  // GPR_WINDOWS

}  // namespace grpc_core
