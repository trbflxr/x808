//
// Created by FLXR on 6/28/2018.
//

#include <xe/math/math.hpp>
#include <xe/math/vec3.hpp>

namespace xe {

  vec3::vec3() : x(0), y(0), z(0) { }
  vec3::vec3(float val) : x(val), y(val), z(val) { }
  vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) { }
  vec3::vec3(float x, float y) : x(x), y(y), z(0) { }
  vec3::vec3(const vec3 &vec) : x(vec.x), y(vec.y), z(vec.z) { }
  vec3::vec3(const vec2 &vec) : x(vec.x), y(vec.y), z(0.0f) { }
  vec3::vec3(const vec2 &xy, float z) : x(xy.x), y(xy.y), z(z) { }
  vec3::vec3(const vec4 &vec) : x(vec.x), y(vec.y), z(vec.z) { }

  vec3 vec3::rotate(const quat &rotation) const {
    quat cq = quat::conjugate(rotation);
    quat w = rotation * (*this) * cq;
    return vec3(w.x, w.y, w.z);
  }

  float vec3::length(const vec3 &v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
  }

  float vec3::max(const vec3 &v) {
    return __max(v.x, __max(v.y, v.z));
  }

  float vec3::dot(const vec3 &v1, const vec3 &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
  }

  vec3 vec3::cross(const vec3 &v1, const vec3 &v2) {
    const float x = v1.y * v2.z - v1.z * v2.y;
    const float y = v1.z * v2.x - v1.x * v2.z;
    const float z = v1.x * v2.y - v1.y * v2.x;

    return vec3(x, y, z);
  }

  vec3 vec3::normalize(const vec3 &v) {
    const float l = length(v);

    return vec3(v.x / l, v.y / l, v.z / l);
  }

  vec3 vec3::rotate(const vec3 &v, const vec3 &axis, float angle) {
    const float sin = sinf(-angle);
    const float cos = cosf(-angle);

    return cross(v, axis * sin) + v * cos + axis * dot(v, axis * (1.0f - cos));
  }

  vec3 vec3::lerp(const vec3 &v, const vec3 &dest, float lerpFactor) {
    return (dest - v) * lerpFactor + v;
  }

  vec3 vec3::transformPerspective(const vec3 &vec, const mat4 &mat) {
    vec3 res;

    vec4 r1(0.0f, 0.0f, 0.0f, 1.0f);
    r1 = vec4::transform(r1, mat);

    res.x = r1.x / r1.w;
    res.y = r1.y / r1.w;
    res.z = r1.z / r1.w;

    return res;
  }

  const vec3 &vec3::UnitX() {
    static const vec3 u = vec3(1.0f, 0.0f, 0.0f);
    return u;
  }

  const vec3 &vec3::UnitY() {
    static const vec3 u = vec3(0.0f, 1.0f, 0.0f);
    return u;
  }

  const vec3 &vec3::UnitZ() {
    static const vec3 u = vec3(0.0f, 0.0f, 1.0f);
    return u;
  }

  const vec3 &vec3::UnitXN() {
    static const vec3 u = vec3(-1.0f, 0.0f, 0.0f);
    return u;
  }

  const vec3 &vec3::UnitYN() {
    static const vec3 u = vec3(0.0f, -1.0f, 0.0f);
    return u;
  }

  const vec3 &vec3::UnitZN() {
    static const vec3 u = vec3(0.0f, 0.0f, -1.0f);
    return u;
  }

  const vec3 &vec3::Zero() {
    static const vec3 u = vec3(0.0f, 0.0f, 0.0f);
    return u;
  }


  ///----- operators -----///
  vec3 operator*(const vec3 &left, const mat4 &right) {
    return vec3(right.rows[0].x * left.x + right.rows[0].y * left.y + right.rows[0].z * left.z + right.rows[0].w,
                right.rows[1].x * left.x + right.rows[1].y * left.y + right.rows[1].z * left.z + right.rows[1].w,
                right.rows[2].x * left.x + right.rows[2].y * left.y + right.rows[2].z * left.z + right.rows[2].w);
  }

}