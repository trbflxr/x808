//
// Created by FLXR on 6/30/2018.
//

#ifndef X808_COLOR_HPP
#define X808_COLOR_HPP


#include <xe/xeint.hpp>
#include <xe/math/vec4.hpp>

namespace xe {

  struct color {

    static constexpr uint Transparent = 0x00000000;

    static constexpr uint Black = 0xff000000;
    static constexpr uint White = 0xffffffff;
    static constexpr uint Red = 0xffff0000;
    static constexpr uint Green = 0xff00ff00;
    static constexpr uint Blue = 0xff0000ff;

    static constexpr uint Yellow = 0xffffff00;
    static constexpr uint Cyan = 0xff00ffff;
    static constexpr uint Pink = 0xffff00ff;

    static constexpr uint Gray = 0xff5a5a5a;
    static constexpr uint LightGray = 0xff9a9a9a;

    static constexpr uint rgba(float r, float g, float b, float a) {
      const uint r1 = static_cast<uint>(r * 255);
      const uint g1 = static_cast<uint>(g * 255);
      const uint b1 = static_cast<uint>(b * 255);
      const uint a1 = static_cast<uint>(a * 255);

      const uint color = a1 << 24 | r1 << 16 | g1 << 8 | b1;
      return color;
    }

    static constexpr uint encode(const vec4 &color) {
      const uint r1 = static_cast<uint>(color.x * 255);
      const uint g1 = static_cast<uint>(color.y * 255);
      const uint b1 = static_cast<uint>(color.z * 255);
      const uint a1 = static_cast<uint>(color.w * 255);

      const uint result = a1 << 24 | r1 << 16 | g1 << 8 | b1;
      return result;
    }

    static vec4 decode(uint color) {
      vec4 result;
      result.z = ((color >> 0) & 255) / 255.0f;
      result.y = ((color >> 8) & 255) / 255.0f;
      result.x = ((color >> 16) & 255) / 255.0f;
      result.w = ((color >> 24) & 255) / 255.0f;

      return result;
    }
  };

}

#endif //X808_COLOR_HPP
