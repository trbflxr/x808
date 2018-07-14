//
// Created by FLXR on 7/14/2018.
//

#ifndef X808_MOUSE_HPP
#define X808_MOUSE_HPP


#include "common.hpp"
#include "math/tvec2.hpp"

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

		static vec2i getPosition();
		static vec2i getPosition(const Window &relativeTo);

		static void setPosition(const vec2i &position);
		static void setPosition(const vec2i &position, const Window &relativeTo);
	};

}


#endif //X808_MOUSE_HPP
