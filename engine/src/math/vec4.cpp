//
// Created by FLXR on 6/28/2018.
//

#include <xe/math/vec4.hpp>
#include <xe/math/math.hpp>

namespace xe {

  vec4::vec4() : x(0), y(0), z(0), w(0) { }
  vec4::vec4(float scalar) : x(scalar), y(scalar), z(scalar), w(scalar) { }
  vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
  vec4::vec4(const vec3 &xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
  vec4::vec4(const vec4 &vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) { }

  float vec4::dot(const vec4 &v1, const vec4 &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
  }
  vec4 vec4::transform(const vec4 &vec, const mat4 &m) {
    return vec4((vec.x * m.rows[0].x + vec.y * m.rows[1].x + vec.z * m.rows[2].x + vec.w * m.rows[3].x),
                (vec.x * m.rows[0].y + vec.y * m.rows[1].y + vec.z * m.rows[2].y + vec.w * m.rows[3].y),
                (vec.x * m.rows[0].z + vec.y * m.rows[1].z + vec.z * m.rows[2].z + vec.w * m.rows[3].z),
                (vec.x * m.rows[0].w + vec.y * m.rows[1].w + vec.z * m.rows[2].w + vec.w * m.rows[3].w));
  }


  ///----- operators -----///
  vec4 operator*(const vec4 &left, const mat4 &right) {
    return {right.rows[0].x * left.x + right.rows[0].y * left.y + right.rows[0].z * left.z +
            right.rows[0].w * left.w,
            right.rows[1].x * left.x + right.rows[1].y * left.y + right.rows[1].z * left.z +
            right.rows[1].w * left.w,
            right.rows[2].x * left.x + right.rows[2].y * left.y + right.rows[2].z * left.z +
            right.rows[2].w * left.w,
            right.rows[3].x * left.x + right.rows[3].y * left.y + right.rows[3].z * left.z +
            right.rows[3].w * left.w};
  }

}