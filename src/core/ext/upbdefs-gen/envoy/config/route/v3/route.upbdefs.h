/* This file was generated by upb_generator from the input file:
 *
 *     envoy/config/route/v3/route.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated.
 * NO CHECKED-IN PROTOBUF GENCODE */

#ifndef ENVOY_CONFIG_ROUTE_V3_ROUTE_PROTO_UPBDEFS_H_
#define ENVOY_CONFIG_ROUTE_V3_ROUTE_PROTO_UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc" // Must be last.
#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_config_route_v3_route_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_route_v3_RouteConfiguration_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_route_v3_route_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.route.v3.RouteConfiguration");
}

UPB_INLINE const upb_MessageDef *envoy_config_route_v3_RouteConfiguration_TypedPerFilterConfigEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_route_v3_route_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.route.v3.RouteConfiguration.TypedPerFilterConfigEntry");
}

UPB_INLINE const upb_MessageDef *envoy_config_route_v3_Vhds_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_route_v3_route_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.route.v3.Vhds");
}

#ifdef __cplusplus
}  /* extern "C" */
#endif

#include "upb/port/undef.inc"

#endif  /* ENVOY_CONFIG_ROUTE_V3_ROUTE_PROTO_UPBDEFS_H_ */
