//
// Created by FLXR on 7/14/2018.
//

#include "keyboard.hpp"
#include "platforminput.hpp"

namespace xe {

	bool Keyboard::isKeyPressed(Keyboard::Key key) {
		return internal::PlatformInput::isKeyPressed(key);
	}

}