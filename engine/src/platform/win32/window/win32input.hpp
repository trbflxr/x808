//
// Created by FLXR on 7/14/2018.
//

#ifndef X808_WIN32INPUT_HPP
#define X808_WIN32INPUT_HPP


#include "window/keyboard.hpp"
#include "window/mouse.hpp"

namespace xe { namespace internal {

	struct PlatformInput {

		///keyboard
		static bool isKeyPressed(Keyboard::Key key);

		///mouse
		static bool isMouseButtonPressed(Mouse::Button button);

		static vec2i getMousePosition();
		static vec2i getMousePosition(const Window& relativeTo);

		static void setMousePosition(const vec2i& position);
		static void setMousePosition(const vec2i& position, const Window& relativeTo);
	};

}}


#endif //X808_WIN32INPUT_HPP
