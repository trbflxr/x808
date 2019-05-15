//
// Created by FLXR on 7/14/2018.
//

#ifndef X808_MOUSE_HPP
#define X808_MOUSE_HPP


#include <xe/common.hpp>
#include <xe/math/vec2.hpp>

namespace xe {

  class Window;

  struct XE_API Mouse {
    enum Button {
      Left,
      Right,
      Middle,
      XButton1,
      XButton2,

      ButtonCount
    };

    static bool isButtonPressed(Button button);

    static vec2 getPosition();
    static vec2 getPosition(const Window &relativeTo);

    static void setPosition(const vec2 &position);
    static void setPosition(const vec2 &position, const Window &relativeTo);
  };

}


#endif //X808_MOUSE_HPP
