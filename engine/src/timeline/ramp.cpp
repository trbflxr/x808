//
// Created by FLXR on 2/23/2019.
//

#include <xe/timeline/ramp.hpp>
#include <xe/common.hpp>
#include <xe/math/mathfunc.hpp>
#include <xe/math/vec2.hpp>
#include <xe/math/vec3.hpp>
#include <xe/math/vec4.hpp>

namespace xe {

  template<>
  XE_API float Ramp<float>::lerp(const float &s, const float &e, float t) {
    return (1.0f - t) * s + t * e;
  }

  template<>
  XE_API vec2 Ramp<vec2>::lerp(const vec2 &s, const vec2 &e, float t) {
    const float mt = (1.0f - t);
    return vec2(mt * s.x + t * e.x, mt * s.y + t * e.y);
  }

  template<>
  XE_API vec3 Ramp<vec3>::lerp(const vec3 &s, const vec3 &e, float t) {
    const float mt = (1.0f - t);
    return vec3(mt * s.x + t * e.x,
                mt * s.y + t * e.y,
                mt * s.z + t * e.z);
  }

  template<>
  XE_API vec4 Ramp<vec4>::lerp(const vec4 &s, const vec4 &e, float t) {
    const float mt = (1.0f - t);
    return vec4(mt * s.x + t * e.x,
                mt * s.y + t * e.y,
                mt * s.z + t * e.z,
                mt * s.w + t * e.w);
  }

  template<>
  XE_API vec4 Ramp<vec4>::lerpc1(const vec4 &s, const vec4 &e, float t) {
    const float mt = (1.0f - t);
    return vec4(math::clampf(mt * s.x + t * e.x, 0.0f, 1.0f),
                math::clampf(mt * s.y + t * e.y, 0.0f, 1.0f),
                math::clampf(mt * s.z + t * e.z, 0.0f, 1.0f),
                math::clampf(mt * s.w + t * e.w, 0.0f, 1.0f));
  }

}