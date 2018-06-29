//
// Created by FLXR on 6/29/2018.
//

#include <windows.h>

#include "input.hpp"
#include "utils/log.hpp"

extern HWND hWnd;

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

void xe::InputManager::platformUpdate() {
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(hWnd, &mouse);

	vec2 mousePos = {(float) mouse.x, (float) mouse.y};
	if (mousePos != mousePosition) {
		//todo: mouse drag handle
		auto e = MouseMoveEvent(mousePos.x, mousePos.y, mouseButtons[XE_MOUSE_LEFT]);

		XE_ASSERT(eventCallback);

		eventCallback(e);
		mousePosition = mousePos;
	}
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

void xe::InputManager::setMousePosition(const xe::vec2 &position) {
	POINT pt = {(LONG) position.x, (LONG) position.y};
	ClientToScreen(hWnd, &pt);
	SetCursorPos(pt.x, pt.y);
}

void xe::InputManager::setMouseCursor(int32 cursor) {
	if (cursor == XE_NO_CURSOR) {
		SetCursor(XE_NO_CURSOR);
		while (ShowCursor(false) >= 0);
	} else {
		SetCursor(LoadCursor(nullptr, IDC_ARROW));
		ShowCursor(true);
	}
}

void xe::keyCallback(xe::InputManager *inputManager, int32 flags, int32 key, uint message) {
	bool pressed = message == WM_KEYDOWN || message == WM_SYSKEYDOWN;
	inputManager->keyState[key] = pressed;

	bool repeat = static_cast<bool>((flags >> 30) & 1);

	int32 modifier = 0;
	switch (key) {
		case XE_KEY_CONTROL: modifier = XE_MODIFIER_LEFT_CONTROL;
			break;
		case XE_KEY_ALT: modifier = XE_MODIFIER_LEFT_ALT;
			break;
		case XE_KEY_SHIFT: modifier = XE_MODIFIER_LEFT_SHIFT;
			break;
		default:break;
	}

	if (pressed) {
		inputManager->keyModifiers |= modifier;
	} else {
		inputManager->keyModifiers &= ~(modifier);
	}

	XE_ASSERT(inputManager->eventCallback);

	if (pressed) {
		auto e = KeyPressEvent(key, inputManager->keyModifiers, repeat);
		inputManager->eventCallback(e);
	} else {
		auto e = KeyReleaseEvent(key);
		inputManager->eventCallback(e);
	}
}

void xe::mouseButtonCallback(xe::InputManager *inputManager, int32 button, int32 x, int32 y) {
	bool down = false;

	switch (button) {
		case WM_LBUTTONDOWN: SetCapture(hWnd);
			button = XE_MOUSE_LEFT;
			down = true;
			break;
		case WM_LBUTTONUP: ReleaseCapture();
			button = XE_MOUSE_LEFT;
			down = false;
			break;
		case WM_RBUTTONDOWN: SetCapture(hWnd);
			button = XE_MOUSE_RIGHT;
			down = true;
			break;
		case WM_RBUTTONUP: ReleaseCapture();
			button = XE_MOUSE_RIGHT;
			down = false;
			break;
		case WM_MBUTTONDOWN: SetCapture(hWnd);
			button = XE_MOUSE_MIDDLE;
			down = true;
			break;
		case WM_MBUTTONUP: ReleaseCapture();
			button = XE_MOUSE_MIDDLE;
			down = false;
			break;
		default:break;
	}

	inputManager->mouseButtons[button] = down;
	inputManager->mousePosition.x = (float) x;
	inputManager->mousePosition.y = (float) y;

	XE_ASSERT(inputManager->eventCallback);

	if (down) {
		auto e = MousePressEvent(button, x, y);
		inputManager->eventCallback(e);
	} else {
		auto e = MouseReleaseEvent(button, x, y);
		inputManager->eventCallback(e);
	}
}
