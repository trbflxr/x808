//
// Created by FLXR on 2/22/2019.
//

#ifndef X808_MATHFUNC_HPP
#define X808_MATHFUNC_HPP


#include <cmath>


#define XE_PI 3.14159265359f

#define to_rad(deg) ((deg) * XE_PI / 180.0f)
#define to_deg(rad) ((rad) * 180.0f / XE_PI)

#define __max(a, b) (((a) > (b)) ? (a) : (b))
#define __min(a, b) (((a) < (b)) ? (a) : (b))


namespace xe::math {

  static float clampf(float n, float min, float max) {
    return __max(__min(n, max), min);
  }

  static float logf(float a, float newBase) {
    if (std::isnan(a)) return a;
    if (std::isnan(newBase)) return newBase;
    if (newBase == 1.0f || (a != 1.0f && (newBase == 0.0f || std::isinf(newBase)))) return NAN;

    return std::log(a) / std::log(newBase);
  }

  template<class T>
  static T lerp(const T &start, const T &end, float t) {
    return (1.0f - t) * start + t * end;
  }

  static float slerp(float src0, float src1, float t) {
    src0 = __max(src0, 0.000001f);
    return powf(src1 / src0, t) * src0;
  }

  static float signum(float val) {
    return (val == 0.0f || std::isnan(val)) ? val : copysignf(1.0f, val);
  }

}


#endif //X808_MATHFUNC_HPP
