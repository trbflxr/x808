//
// Created by FLXR on 7/14/2018.
//

#include "mouse.hpp"
#include "platforminput.hpp"
#include "application/window.hpp"

namespace xe {

	bool Mouse::isButtonPressed(Mouse::Button button) {
		return internal::PlatformInput::isMouseButtonPressed(button);
	}

	vec2i Mouse::getPosition() {
		return internal::PlatformInput::getMousePosition();
	}

	vec2i Mouse::getPosition(const Window &relativeTo) {
		return internal::PlatformInput::getMousePosition(relativeTo);
	}

	void Mouse::setPosition(const vec2i &position) {
		internal::PlatformInput::setMousePosition(position);
	}

	void Mouse::setPosition(const vec2i &position, const Window &relativeTo) {
		internal::PlatformInput::setMousePosition(position, relativeTo);
	}

}