//
// Created by FLXR on 7/6/2018.
//

#include <windows.h>
#include "application/input.hpp"
#include "utils/log.hpp"

extern HWND hWnd;

void xe::InputManager::platformUpdate() {
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(hWnd, &mouse);

	vec2 mousePos = {(float) mouse.x, (float) mouse.y};
	if (mousePos != mousePosition) {
		auto e = MouseMoveEvent(mousePos.x, mousePos.y, mouseButtons[XE_MOUSE_LEFT]);

		XE_ASSERT(eventCallback);

		eventCallback(e);
		mousePosition = mousePos;
	}
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
	if (message == WM_SYSKEYDOWN && key == VK_F4) {
		PostQuitMessage(0);
	}

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