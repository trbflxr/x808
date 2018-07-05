//
// Created by FLXR on 6/29/2018.
//


#include "input.hpp"
#include "utils/log.hpp"

xe::InputManager *xe::Input::inputManager = nullptr;

xe::InputManager::InputManager() {
	clearKeys();
	clearMouseButtons();

	mouseDragged = false;

	Input::inputManager = this;
}

void xe::InputManager::update() {
	for (int32 i = 0; i < MAX_BUTTONS; i++) {
		mouseClicked[i] = mouseButtons[i] && !mouseState[i];
	}

	memcpy(lastKeyState, keyState, MAX_KEYS);
	memcpy(mouseState, mouseButtons, MAX_BUTTONS);
}

void xe::InputManager::clearKeys() {
	for (int32 i = 0; i < MAX_KEYS; i++) {
		keyState[i] = false;
		lastKeyState[i] = false;
	}
	keyModifiers = 0;
}


void xe::InputManager::clearMouseButtons() {
	for (int32 i = 0; i < MAX_BUTTONS; i++) {
		mouseButtons[i] = false;
		mouseState[i] = false;
		mouseClicked[i] = false;
	}
}

bool xe::InputManager::isKeyPressed(uint keyCode) const {
	if (keyCode >= MAX_KEYS) return false;
	return keyState[keyCode];
}

bool xe::InputManager::isMouseButtonPressed(uint button) const {
	if (button >= MAX_BUTTONS) return false;
	return mouseButtons[button];
}

bool xe::InputManager::isMouseButtonClicked(uint button) const {
	if (button >= MAX_BUTTONS) return false;
	return mouseClicked[button];
}

void xe::mouseWheelCallback(InputManager *inputManager, int32 x, int32 y, int32 delta) {
	auto e = MouseWheelEvent(x, y, delta);
	inputManager->eventCallback(e);
}