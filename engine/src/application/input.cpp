//
// Created by FLXR on 6/29/2018.
//


#include "input.hpp"
#include "utils/log.hpp"
#include "application/application.hpp"

namespace xe {

	InputManager::InputManager() {
		clearKeys();
		clearMouseButtons();

		mouseDragged = false;

		Input::inputManager = this;
	}

	void InputManager::update() {
		for (int32 i = 0; i < MAX_BUTTONS; i++) {
			mouseClicked[i] = mouseButtons[i] && !mouseState[i];
		}

		memcpy(lastKeyState, keyState, MAX_KEYS);
		memcpy(mouseState, mouseButtons, MAX_BUTTONS);
	}

	void InputManager::clearKeys() {
		for (int32 i = 0; i < MAX_KEYS; i++) {
			keyState[i] = false;
			lastKeyState[i] = false;
		}
		keyModifiers = 0;
	}


	void InputManager::clearMouseButtons() {
		for (int32 i = 0; i < MAX_BUTTONS; i++) {
			mouseButtons[i] = false;
			mouseState[i] = false;
			mouseClicked[i] = false;
		}
	}

	bool InputManager::isKeyPressed(uint keyCode) const {
		if (keyCode >= MAX_KEYS) return false;
		return keyState[keyCode];
	}

	bool InputManager::isMouseButtonPressed(uint button) const {
		if (button >= MAX_BUTTONS) return false;
		return mouseButtons[button];
	}

	bool InputManager::isMouseButtonClicked(uint button) const {
		if (button >= MAX_BUTTONS) return false;
		return mouseClicked[button];
	}

	void mouseWheelCallback(InputManager *inputManager, int32 x, int32 y, int32 delta) {
		auto e = MouseWheelEvent(x, y, delta);
		inputManager->eventCallback(e);
	}


	///------ InputManager ------///
	InputManager *Input::inputManager = nullptr;
	gfx::Camera *Input::camera = nullptr;

	vec2 Input::getMouseWorldPosition() {
		if (!camera) {
			static bool logged = false;
			if (!logged) {
				XE_WARN("[Input::getMouseWorldPosition]: You should call Input::setCamera first");
				logged = true;
			}

			return inputManager->getMousePosition();
		}

		const vec2 &mousePos = inputManager->getMousePosition();
		uint width = Application::get().getWindowWidth();
		uint height = Application::get().getWindowHeight();
		float scale = Application::get().getConfig().scale;

		return vec2((mousePos.x - width / 2.0f) / (scale / 2) + camera->getPosition().x,
		            (height / 2.0f - mousePos.y) / (scale / 2) + camera->getPosition().y);
	}

}