//
// Created by FLXR on 2/2/2019.
//

#include <string>
#include <xe/math/vec2.hpp>
#include <xe/math/vec3.hpp>
#include <xe/math/vec4.hpp>
#include <xe/math/quat.hpp>
#include <xe/math/mat4.hpp>
#include <xe/math/rect.hpp>
#include <xe/utils/logger.hpp>

namespace xe {

  template<>
  XE_API const char *Logger::toString<char>(const char &t) { return &t; }

  template<>
  XE_API const char *Logger::toString<char *>(char *const &t) { return t; }

  template<>
  XE_API const char *Logger::toString<const char *>(const char *const &t) { return t; }

  template<>
  XE_API const char *Logger::toString<std::string>(const std::string &t) { return t.c_str(); }

  template<>
  XE_API const char *Logger::toString<std::string_view>(const std::string_view &t) { return t.data(); }

  template<>
  XE_API const char *Logger::toString<bool>(const bool &t) { return t ? "true" : "false"; }

  template<>
  XE_API const char *Logger::toString<int8>(const int8 &t) {
    sprintf(buffer, "%d", t);
    return buffer;
  }

  template<>
  XE_API const char *Logger::toString<uint8>(const uint8 &t) {
    sprintf(buffer, "%d", t);
    return buffer;
  }

  template<>
  XE_API const char *Logger::toString<int16>(const int16 &t) {
    sprintf(buffer, "%d", t);
    return buffer;
  }

  template<>
  XE_API const char *Logger::toString<uint16>(const uint16 &t) {
    sprintf(buffer, "%d", t);
    return buffer;
  }

  template<>
  XE_API const char *Logger::toString<int32>(const int32 &t) {
    sprintf(buffer, "%d", t);
    return buffer;
  }

  template<>
  XE_API const char *Logger::toString<uint32>(const uint32 &t) {
    sprintf(buffer, "%d", t);
    return buffer;
  }

  template<>
  XE_API const char *Logger::toString<int64>(const int64 &t) {
    sprintf(buffer, "%lli", t);
    return buffer;
  }

  template<>
  XE_API const char *Logger::toString<uint64>(const uint64 &t) {
    sprintf(buffer, "%llu", t);
    return buffer;
  }

  template<>
  XE_API const char *Logger::toString<float>(const float &t) {
    sprintf(buffer, "%f", t);
    return buffer;
  }

  template<>
  XE_API const char *Logger::toString<double>(const double &t) {
    sprintf(buffer, "%lf", t);
    return buffer;
  }

  template<>
  XE_API const char *Logger::toString<vec2>(const vec2 &t) {
    sprintf(buffer, "vec2(%f, %f)", t.x, t.y);
    return buffer;
  }

  template<>
  XE_API const char *Logger::toString<vec3>(const vec3 &t) {
    sprintf(buffer, "vec3(%f, %f, %f)", t.x, t.y, t.z);
    return buffer;
  }

  template<>
  XE_API const char *Logger::toString<vec4>(const vec4 &t) {
    sprintf(buffer, "vec4(%f, %f, %f, %f)", t.x, t.y, t.z, t.w);
    return buffer;
  }

  template<>
  XE_API const char *Logger::toString<quat>(const quat &t) {
    sprintf(buffer, "quat(%f, %f, %f, %f)", t.x, t.y, t.z, t.w);
    return buffer;
  }

  template<>
  XE_API const char *Logger::toString<mat4>(const mat4 &t) {
    sprintf(buffer, "mat4({%f, %f, %f, %f},\n"
                    "\t   {%f, %f, %f, %f},\n"
                    "\t   {%f, %f, %f, %f},\n"
                    "\t   {%f, %f, %f, %f})",
            t.elements[0], t.elements[1], t.elements[2], t.elements[3],
            t.elements[4], t.elements[5], t.elements[6], t.elements[7],
            t.elements[8], t.elements[9], t.elements[10], t.elements[11],
            t.elements[12], t.elements[13], t.elements[14], t.elements[15]);
    return buffer;
  }

  template<>
  XE_API const char *Logger::toString<rect>(const rect &t) {
    sprintf(buffer, "rect(%f, %f, %f, %f)", t.x, t.y, t.width, t.height);
    return buffer;
  }

};