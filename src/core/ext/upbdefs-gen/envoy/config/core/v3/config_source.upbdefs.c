/* This file was generated by upb_generator from the input file:
 *
 *     envoy/config/core/v3/config_source.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated.
 * NO CHECKED-IN PROTOBUF GENCODE */

#include "upb/reflection/def.h"
#include "envoy/config/core/v3/config_source.upbdefs.h"
#include "envoy/config/core/v3/config_source.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_core_v3_base_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_core_v3_extension_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_core_v3_grpc_service_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_any_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_duration_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_wrappers_proto_upbdefinit;
extern _upb_DefPool_Init xds_core_v3_authority_proto_upbdefinit;
extern _upb_DefPool_Init envoy_annotations_deprecation_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;
static const char descriptor[3037] = {'\n', '(', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'c', 'o', 
'n', 'f', 'i', 'g', '_', 's', 'o', 'u', 'r', 'c', 'e', '.', 'p', 'r', 'o', 't', 'o', '\022', '\024', 'e', 'n', 'v', 'o', 'y', '.', 
'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '\032', '\037', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 
'f', 'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'b', 'a', 's', 'e', '.', 'p', 'r', 'o', 't', 'o', '\032', '$', 'e', 
'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'e', 'x', 't', 'e', 'n', 
's', 'i', 'o', 'n', '.', 'p', 'r', 'o', 't', 'o', '\032', '\'', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 
'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'g', 'r', 'p', 'c', '_', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'p', 'r', 'o', 't', 
'o', '\032', '\031', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 'a', 'n', 'y', '.', 'p', 'r', 
'o', 't', 'o', '\032', '\036', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 'd', 'u', 'r', 'a', 
't', 'i', 'o', 'n', '.', 'p', 'r', 'o', 't', 'o', '\032', '\036', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r', 'o', 't', 'o', 'b', 
'u', 'f', '/', 'w', 'r', 'a', 'p', 'p', 'e', 'r', 's', '.', 'p', 'r', 'o', 't', 'o', '\032', '\033', 'x', 'd', 's', '/', 'c', 'o', 
'r', 'e', '/', 'v', '3', '/', 'a', 'u', 't', 'h', 'o', 'r', 'i', 't', 'y', '.', 'p', 'r', 'o', 't', 'o', '\032', '#', 'e', 'n', 
'v', 'o', 'y', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 'd', 'e', 'p', 'r', 'e', 'c', 'a', 't', 'i', 
'o', 'n', '.', 'p', 'r', 'o', 't', 'o', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 
's', '/', 's', 't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\032', '!', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 
't', 'a', 't', 'i', 'o', 'n', 's', '/', 'v', 'e', 'r', 's', 'i', 'o', 'n', 'i', 'n', 'g', '.', 'p', 'r', 'o', 't', 'o', '\032', 
'\027', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o', 't', 'o', '\"', 
'\364', '\006', '\n', '\017', 'A', 'p', 'i', 'C', 'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 'e', '\022', 'R', '\n', '\010', 'a', 'p', 
'i', '_', 't', 'y', 'p', 'e', '\030', '\001', ' ', '\001', '(', '\016', '2', '-', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 
'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'A', 'p', 'i', 'C', 'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 
'e', '.', 'A', 'p', 'i', 'T', 'y', 'p', 'e', 'B', '\010', '\372', 'B', '\005', '\202', '\001', '\002', '\020', '\001', 'R', '\007', 'a', 'p', 'i', 'T', 
'y', 'p', 'e', '\022', '^', '\n', '\025', 't', 'r', 'a', 'n', 's', 'p', 'o', 'r', 't', '_', 'a', 'p', 'i', '_', 'v', 'e', 'r', 's', 
'i', 'o', 'n', '\030', '\010', ' ', '\001', '(', '\016', '2', ' ', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 
'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'A', 'p', 'i', 'V', 'e', 'r', 's', 'i', 'o', 'n', 'B', '\010', '\372', 'B', '\005', '\202', '\001', 
'\002', '\020', '\001', 'R', '\023', 't', 'r', 'a', 'n', 's', 'p', 'o', 'r', 't', 'A', 'p', 'i', 'V', 'e', 'r', 's', 'i', 'o', 'n', '\022', 
'#', '\n', '\r', 'c', 'l', 'u', 's', 't', 'e', 'r', '_', 'n', 'a', 'm', 'e', 's', '\030', '\002', ' ', '\003', '(', '\t', 'R', '\014', 'c', 
'l', 'u', 's', 't', 'e', 'r', 'N', 'a', 'm', 'e', 's', '\022', 'F', '\n', '\r', 'g', 'r', 'p', 'c', '_', 's', 'e', 'r', 'v', 'i', 
'c', 'e', 's', '\030', '\004', ' ', '\003', '(', '\013', '2', '!', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 
'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'G', 'r', 'p', 'c', 'S', 'e', 'r', 'v', 'i', 'c', 'e', 'R', '\014', 'g', 'r', 'p', 'c', 
'S', 'e', 'r', 'v', 'i', 'c', 'e', 's', '\022', '>', '\n', '\r', 'r', 'e', 'f', 'r', 'e', 's', 'h', '_', 'd', 'e', 'l', 'a', 'y', 
'\030', '\003', ' ', '\001', '(', '\013', '2', '\031', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 
'D', 'u', 'r', 'a', 't', 'i', 'o', 'n', 'R', '\014', 'r', 'e', 'f', 'r', 'e', 's', 'h', 'D', 'e', 'l', 'a', 'y', '\022', 'L', '\n', 
'\017', 'r', 'e', 'q', 'u', 'e', 's', 't', '_', 't', 'i', 'm', 'e', 'o', 'u', 't', '\030', '\005', ' ', '\001', '(', '\013', '2', '\031', '.', 
'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'D', 'u', 'r', 'a', 't', 'i', 'o', 'n', 'B', 
'\010', '\372', 'B', '\005', '\252', '\001', '\002', '*', '\000', 'R', '\016', 'r', 'e', 'q', 'u', 'e', 's', 't', 'T', 'i', 'm', 'e', 'o', 'u', 't', 
'\022', 'W', '\n', '\023', 'r', 'a', 't', 'e', '_', 'l', 'i', 'm', 'i', 't', '_', 's', 'e', 't', 't', 'i', 'n', 'g', 's', '\030', '\006', 
' ', '\001', '(', '\013', '2', '\'', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 
'v', '3', '.', 'R', 'a', 't', 'e', 'L', 'i', 'm', 'i', 't', 'S', 'e', 't', 't', 'i', 'n', 'g', 's', 'R', '\021', 'r', 'a', 't', 
'e', 'L', 'i', 'm', 'i', 't', 'S', 'e', 't', 't', 'i', 'n', 'g', 's', '\022', 'A', '\n', '\036', 's', 'e', 't', '_', 'n', 'o', 'd', 
'e', '_', 'o', 'n', '_', 'f', 'i', 'r', 's', 't', '_', 'm', 'e', 's', 's', 'a', 'g', 'e', '_', 'o', 'n', 'l', 'y', '\030', '\007', 
' ', '\001', '(', '\010', 'R', '\031', 's', 'e', 't', 'N', 'o', 'd', 'e', 'O', 'n', 'F', 'i', 'r', 's', 't', 'M', 'e', 's', 's', 'a', 
'g', 'e', 'O', 'n', 'l', 'y', '\022', 'W', '\n', '\021', 'c', 'o', 'n', 'f', 'i', 'g', '_', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'o', 
'r', 's', '\030', '\t', ' ', '\003', '(', '\013', '2', '*', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 
'o', 'r', 'e', '.', 'v', '3', '.', 'T', 'y', 'p', 'e', 'd', 'E', 'x', 't', 'e', 'n', 's', 'i', 'o', 'n', 'C', 'o', 'n', 'f', 
'i', 'g', 'R', '\020', 'c', 'o', 'n', 'f', 'i', 'g', 'V', 'a', 'l', 'i', 'd', 'a', 't', 'o', 'r', 's', '\"', '\222', '\001', '\n', '\007', 
'A', 'p', 'i', 'T', 'y', 'p', 'e', '\022', '3', '\n', '%', 'D', 'E', 'P', 'R', 'E', 'C', 'A', 'T', 'E', 'D', '_', 'A', 'N', 'D', 
'_', 'U', 'N', 'A', 'V', 'A', 'I', 'L', 'A', 'B', 'L', 'E', '_', 'D', 'O', '_', 'N', 'O', 'T', '_', 'U', 'S', 'E', '\020', '\000', 
'\032', '\010', '\010', '\001', '\250', '\367', '\264', '\213', '\002', '\001', '\022', '\010', '\n', '\004', 'R', 'E', 'S', 'T', '\020', '\001', '\022', '\010', '\n', '\004', 'G', 
'R', 'P', 'C', '\020', '\002', '\022', '\016', '\n', '\n', 'D', 'E', 'L', 'T', 'A', '_', 'G', 'R', 'P', 'C', '\020', '\003', '\022', '\023', '\n', '\017', 
'A', 'G', 'G', 'R', 'E', 'G', 'A', 'T', 'E', 'D', '_', 'G', 'R', 'P', 'C', '\020', '\005', '\022', '\031', '\n', '\025', 'A', 'G', 'G', 'R', 
'E', 'G', 'A', 'T', 'E', 'D', '_', 'D', 'E', 'L', 'T', 'A', '_', 'G', 'R', 'P', 'C', '\020', '\006', ':', '(', '\232', '\305', '\210', '\036', 
'#', '\n', '!', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'p', 'i', '.', 'v', '2', '.', 'c', 'o', 'r', 'e', '.', 'A', 'p', 'i', 'C', 
'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 'e', '\"', 'I', '\n', '\026', 'A', 'g', 'g', 'r', 'e', 'g', 'a', 't', 'e', 'd', 
'C', 'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 'e', ':', '/', '\232', '\305', '\210', '\036', '*', '\n', '(', 'e', 'n', 'v', 'o', 
'y', '.', 'a', 'p', 'i', '.', 'v', '2', '.', 'c', 'o', 'r', 'e', '.', 'A', 'g', 'g', 'r', 'e', 'g', 'a', 't', 'e', 'd', 'C', 
'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 'e', '\"', '\235', '\001', '\n', '\020', 'S', 'e', 'l', 'f', 'C', 'o', 'n', 'f', 'i', 
'g', 'S', 'o', 'u', 'r', 'c', 'e', '\022', '^', '\n', '\025', 't', 'r', 'a', 'n', 's', 'p', 'o', 'r', 't', '_', 'a', 'p', 'i', '_', 
'v', 'e', 'r', 's', 'i', 'o', 'n', '\030', '\001', ' ', '\001', '(', '\016', '2', ' ', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 
'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'A', 'p', 'i', 'V', 'e', 'r', 's', 'i', 'o', 'n', 'B', '\010', '\372', 
'B', '\005', '\202', '\001', '\002', '\020', '\001', 'R', '\023', 't', 'r', 'a', 'n', 's', 'p', 'o', 'r', 't', 'A', 'p', 'i', 'V', 'e', 'r', 's', 
'i', 'o', 'n', ':', ')', '\232', '\305', '\210', '\036', '$', '\n', '\"', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'p', 'i', '.', 'v', '2', '.', 
'c', 'o', 'r', 'e', '.', 'S', 'e', 'l', 'f', 'C', 'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 'e', '\"', '\307', '\001', '\n', 
'\021', 'R', 'a', 't', 'e', 'L', 'i', 'm', 'i', 't', 'S', 'e', 't', 't', 'i', 'n', 'g', 's', '\022', ';', '\n', '\n', 'm', 'a', 'x', 
'_', 't', 'o', 'k', 'e', 'n', 's', '\030', '\001', ' ', '\001', '(', '\013', '2', '\034', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 
'o', 't', 'o', 'b', 'u', 'f', '.', 'U', 'I', 'n', 't', '3', '2', 'V', 'a', 'l', 'u', 'e', 'R', '\t', 'm', 'a', 'x', 'T', 'o', 
'k', 'e', 'n', 's', '\022', 'I', '\n', '\t', 'f', 'i', 'l', 'l', '_', 'r', 'a', 't', 'e', '\030', '\002', ' ', '\001', '(', '\013', '2', '\034', 
'.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'D', 'o', 'u', 'b', 'l', 'e', 'V', 'a', 
'l', 'u', 'e', 'B', '\016', '\372', 'B', '\013', '\022', '\t', '!', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', 'R', '\010', 'f', 'i', 'l', 'l', 
'R', 'a', 't', 'e', ':', '*', '\232', '\305', '\210', '\036', '%', '\n', '#', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'p', 'i', '.', 'v', '2', 
'.', 'c', 'o', 'r', 'e', '.', 'R', 'a', 't', 'e', 'L', 'i', 'm', 'i', 't', 'S', 'e', 't', 't', 'i', 'n', 'g', 's', '\"', '\204', 
'\001', '\n', '\020', 'P', 'a', 't', 'h', 'C', 'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 'e', '\022', '\033', '\n', '\004', 'p', 'a', 
't', 'h', '\030', '\001', ' ', '\001', '(', '\t', 'B', '\007', '\372', 'B', '\004', 'r', '\002', '\020', '\001', 'R', '\004', 'p', 'a', 't', 'h', '\022', 'S', 
'\n', '\021', 'w', 'a', 't', 'c', 'h', 'e', 'd', '_', 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', '\030', '\002', ' ', '\001', '(', '\013', 
'2', '&', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'W', 
'a', 't', 'c', 'h', 'e', 'd', 'D', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', 'R', '\020', 'w', 'a', 't', 'c', 'h', 'e', 'd', 'D', 
'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', '\"', '\214', '\005', '\n', '\014', 'C', 'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 'e', 
'\022', '8', '\n', '\013', 'a', 'u', 't', 'h', 'o', 'r', 'i', 't', 'i', 'e', 's', '\030', '\007', ' ', '\003', '(', '\013', '2', '\026', '.', 'x', 
'd', 's', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'A', 'u', 't', 'h', 'o', 'r', 'i', 't', 'y', 'R', '\013', 'a', 'u', 't', 
'h', 'o', 'r', 'i', 't', 'i', 'e', 's', '\022', '!', '\n', '\004', 'p', 'a', 't', 'h', '\030', '\001', ' ', '\001', '(', '\t', 'B', '\013', '\030', 
'\001', '\222', '\307', '\206', '\330', '\004', '\003', '3', '.', '0', 'H', '\000', 'R', '\004', 'p', 'a', 't', 'h', '\022', 'V', '\n', '\022', 'p', 'a', 't', 
'h', '_', 'c', 'o', 'n', 'f', 'i', 'g', '_', 's', 'o', 'u', 'r', 'c', 'e', '\030', '\010', ' ', '\001', '(', '\013', '2', '&', '.', 'e', 
'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'P', 'a', 't', 'h', 'C', 
'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 'e', 'H', '\000', 'R', '\020', 'p', 'a', 't', 'h', 'C', 'o', 'n', 'f', 'i', 'g', 
'S', 'o', 'u', 'r', 'c', 'e', '\022', 'S', '\n', '\021', 'a', 'p', 'i', '_', 'c', 'o', 'n', 'f', 'i', 'g', '_', 's', 'o', 'u', 'r', 
'c', 'e', '\030', '\002', ' ', '\001', '(', '\013', '2', '%', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 
'o', 'r', 'e', '.', 'v', '3', '.', 'A', 'p', 'i', 'C', 'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 'e', 'H', '\000', 'R', 
'\017', 'a', 'p', 'i', 'C', 'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 'e', '\022', '@', '\n', '\003', 'a', 'd', 's', '\030', '\003', 
' ', '\001', '(', '\013', '2', ',', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 
'v', '3', '.', 'A', 'g', 'g', 'r', 'e', 'g', 'a', 't', 'e', 'd', 'C', 'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 'e', 
'H', '\000', 'R', '\003', 'a', 'd', 's', '\022', '<', '\n', '\004', 's', 'e', 'l', 'f', '\030', '\005', ' ', '\001', '(', '\013', '2', '&', '.', 'e', 
'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'S', 'e', 'l', 'f', 'C', 
'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 'e', 'H', '\000', 'R', '\004', 's', 'e', 'l', 'f', '\022', 'M', '\n', '\025', 'i', 'n', 
'i', 't', 'i', 'a', 'l', '_', 'f', 'e', 't', 'c', 'h', '_', 't', 'i', 'm', 'e', 'o', 'u', 't', '\030', '\004', ' ', '\001', '(', '\013', 
'2', '\031', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'D', 'u', 'r', 'a', 't', 'i', 
'o', 'n', 'R', '\023', 'i', 'n', 'i', 't', 'i', 'a', 'l', 'F', 'e', 't', 'c', 'h', 'T', 'i', 'm', 'e', 'o', 'u', 't', '\022', '\\', 
'\n', '\024', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', '_', 'a', 'p', 'i', '_', 'v', 'e', 'r', 's', 'i', 'o', 'n', '\030', '\006', ' ', 
'\001', '(', '\016', '2', ' ', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', 
'3', '.', 'A', 'p', 'i', 'V', 'e', 'r', 's', 'i', 'o', 'n', 'B', '\010', '\372', 'B', '\005', '\202', '\001', '\002', '\020', '\001', 'R', '\022', 'r', 
'e', 's', 'o', 'u', 'r', 'c', 'e', 'A', 'p', 'i', 'V', 'e', 'r', 's', 'i', 'o', 'n', ':', '%', '\232', '\305', '\210', '\036', ' ', '\n', 
'\036', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'p', 'i', '.', 'v', '2', '.', 'c', 'o', 'r', 'e', '.', 'C', 'o', 'n', 'f', 'i', 'g', 
'S', 'o', 'u', 'r', 'c', 'e', 'B', '\036', '\n', '\027', 'c', 'o', 'n', 'f', 'i', 'g', '_', 's', 'o', 'u', 'r', 'c', 'e', '_', 's', 
'p', 'e', 'c', 'i', 'f', 'i', 'e', 'r', '\022', '\003', '\370', 'B', '\001', '\"', '\236', '\002', '\n', '\025', 'E', 'x', 't', 'e', 'n', 's', 'i', 
'o', 'n', 'C', 'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 'e', '\022', 'Q', '\n', '\r', 'c', 'o', 'n', 'f', 'i', 'g', '_', 
's', 'o', 'u', 'r', 'c', 'e', '\030', '\001', ' ', '\001', '(', '\013', '2', '\"', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 
'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'C', 'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 'e', 'B', '\010', 
'\372', 'B', '\005', '\242', '\001', '\002', '\010', '\001', 'R', '\014', 'c', 'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 'e', '\022', ';', '\n', 
'\016', 'd', 'e', 'f', 'a', 'u', 'l', 't', '_', 'c', 'o', 'n', 'f', 'i', 'g', '\030', '\002', ' ', '\001', '(', '\013', '2', '\024', '.', 'g', 
'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'A', 'n', 'y', 'R', '\r', 'd', 'e', 'f', 'a', 'u', 
'l', 't', 'C', 'o', 'n', 'f', 'i', 'g', '\022', 'N', '\n', '$', 'a', 'p', 'p', 'l', 'y', '_', 'd', 'e', 'f', 'a', 'u', 'l', 't', 
'_', 'c', 'o', 'n', 'f', 'i', 'g', '_', 'w', 'i', 't', 'h', 'o', 'u', 't', '_', 'w', 'a', 'r', 'm', 'i', 'n', 'g', '\030', '\003', 
' ', '\001', '(', '\010', 'R', ' ', 'a', 'p', 'p', 'l', 'y', 'D', 'e', 'f', 'a', 'u', 'l', 't', 'C', 'o', 'n', 'f', 'i', 'g', 'W', 
'i', 't', 'h', 'o', 'u', 't', 'W', 'a', 'r', 'm', 'i', 'n', 'g', '\022', '%', '\n', '\t', 't', 'y', 'p', 'e', '_', 'u', 'r', 'l', 
's', '\030', '\004', ' ', '\003', '(', '\t', 'B', '\010', '\372', 'B', '\005', '\222', '\001', '\002', '\010', '\001', 'R', '\010', 't', 'y', 'p', 'e', 'U', 'r', 
'l', 's', '*', '@', '\n', '\n', 'A', 'p', 'i', 'V', 'e', 'r', 's', 'i', 'o', 'n', '\022', '\025', '\n', '\004', 'A', 'U', 'T', 'O', '\020', 
'\000', '\032', '\013', '\010', '\001', '\212', '\364', '\233', '\263', '\005', '\003', '3', '.', '0', '\022', '\023', '\n', '\002', 'V', '2', '\020', '\001', '\032', '\013', '\010', 
'\001', '\212', '\364', '\233', '\263', '\005', '\003', '3', '.', '0', '\022', '\006', '\n', '\002', 'V', '3', '\020', '\002', 'B', '\205', '\001', '\n', '\"', 'i', 'o', 
'.', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 
'c', 'o', 'r', 'e', '.', 'v', '3', 'B', '\021', 'C', 'o', 'n', 'f', 'i', 'g', 'S', 'o', 'u', 'r', 'c', 'e', 'P', 'r', 'o', 't', 
'o', 'P', '\001', 'Z', 'B', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 
'y', '/', 'g', 'o', '-', 'c', 'o', 'n', 't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e', '/', 'e', 'n', 'v', 'o', 'y', '/', 
'c', 'o', 'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', ';', 'c', 'o', 'r', 'e', 'v', '3', '\272', '\200', '\310', '\321', 
'\006', '\002', '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3', 
};

static _upb_DefPool_Init *deps[12] = {
  &envoy_config_core_v3_base_proto_upbdefinit,
  &envoy_config_core_v3_extension_proto_upbdefinit,
  &envoy_config_core_v3_grpc_service_proto_upbdefinit,
  &google_protobuf_any_proto_upbdefinit,
  &google_protobuf_duration_proto_upbdefinit,
  &google_protobuf_wrappers_proto_upbdefinit,
  &xds_core_v3_authority_proto_upbdefinit,
  &envoy_annotations_deprecation_proto_upbdefinit,
  &udpa_annotations_status_proto_upbdefinit,
  &udpa_annotations_versioning_proto_upbdefinit,
  &validate_validate_proto_upbdefinit,
  NULL
};

_upb_DefPool_Init envoy_config_core_v3_config_source_proto_upbdefinit = {
  deps,
  &envoy_config_core_v3_config_source_proto_upb_file_layout,
  "envoy/config/core/v3/config_source.proto",
  UPB_STRINGVIEW_INIT(descriptor, 3037)
};
