//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_INPUT_HPP
#define X808_INPUT_HPP

#include <functional>
#include "math/vec2.hpp"
#include "common.hpp"
#include "events/events.hpp"
#include "gfx/camera/camera.hpp"

namespace xe {

#define MAX_KEYS    1024
#define MAX_BUTTONS 32

	typedef std::function<void(xe::Event &event)> WindowEventCallback;

	class Window;

	class XE_API InputManager {
	private:
		friend class Window;

	public:
		explicit InputManager();

		inline void setEventCallback(const WindowEventCallback &callback) { eventCallback = callback; }

		void update();
		void platformUpdate();

		bool isKeyPressed(uint keyCode) const;
		bool isMouseButtonPressed(uint button) const;
		bool isMouseButtonClicked(uint button) const;

		inline const vec2 &getMousePosition() const { return mousePosition; };
		void setMousePosition(const vec2 &position);

		inline bool isMouseGrabbed() const { return mouseDragged; }
		inline void setMouseGrabbed(bool grabbed) { mouseDragged = grabbed; }

		void setMouseCursor(int32 cursor);

		void clearKeys();
		void clearMouseButtons();

	private:
		friend void keyCallback(InputManager *inputManager, int32 flags, int32 key, uint message);
		friend void mouseButtonCallback(InputManager *inputManager, int32 button, int32 x, int32 y);
		friend void mouseWheelCallback(InputManager *inputManager, int32 x, int32 y, int32 delta);

	private:
		bool keyState[MAX_KEYS];
		bool lastKeyState[MAX_KEYS];

		bool mouseButtons[MAX_BUTTONS];
		bool mouseState[MAX_BUTTONS];
		bool mouseClicked[MAX_BUTTONS];
		bool mouseDragged;
		int32 keyModifiers;

		vec2 mousePosition;
		WindowEventCallback eventCallback;
	};

	void keyCallback(InputManager *inputManager, int32 flags, int32 key, uint message);
	void mouseButtonCallback(InputManager *inputManager, int32 button, int32 x, int32 y);
	void mouseWheelCallback(InputManager *inputManager, int32 x, int32 y, int32 delta);


	class XE_API Input {
	private:
		friend class InputManager;

	public:
		inline static bool isKeyPressed(uint keyCode) { return inputManager->isKeyPressed(keyCode); }
		inline static bool isMouseButtonPressed(uint btn) { return inputManager->isMouseButtonPressed(btn); }
		inline static bool isMouseButtonClicked(uint btn) { return inputManager->isMouseButtonClicked(btn); }
		inline static const vec2 &getMousePosition() { return inputManager->getMousePosition(); }
		inline static void setMousePosition(const vec2 &pos) { return inputManager->setMousePosition(pos); }

		static vec2 getMouseWorldPosition();

		inline static void setCamera(gfx::Camera *camera) { Input::camera = camera; }

		inline static void setMouseCursor(int32 cursor) { inputManager->setMouseCursor(cursor); }
		inline static bool isMouseGrabbed() { return inputManager->isMouseGrabbed(); }
		inline static void setMouseGrabbed(bool grabbed) { inputManager->setMouseGrabbed(grabbed); }

	protected:
		static gfx::Camera *camera;
		static InputManager *inputManager;
	};
}


#define XE_MOUSE_LEFT     0x00
#define XE_MOUSE_MIDDLE   0x01
#define XE_MOUSE_RIGHT    0x02

#define XE_NO_CURSOR      0

#define XE_MODIFIER_LEFT_CONTROL    BIT(0)
#define XE_MODIFIER_LEFT_ALT        BIT(1)
#define XE_MODIFIER_LEFT_SHIFT      BIT(2)
#define XE_MODIFIER_RIGHT_CONTROL   BIT(3)
#define XE_MODIFIER_RIGHT_ALT       BIT(4)
#define XE_MODIFIER_RIGHT_SHIFT     BIT(5)

#define XE_KEY_BACK           0x08
#define XE_KEY_TAB            0x09

#define XE_KEY_0              0x30
#define XE_KEY_1              0x31
#define XE_KEY_2              0x32
#define XE_KEY_3              0x33
#define XE_KEY_4              0x34
#define XE_KEY_5              0x35
#define XE_KEY_6              0x36
#define XE_KEY_7              0x37
#define XE_KEY_8              0x38
#define XE_KEY_9              0x39

#define XE_KEY_A              0x41
#define XE_KEY_B              0x42
#define XE_KEY_C              0x43
#define XE_KEY_D              0x44
#define XE_KEY_E              0x45
#define XE_KEY_F              0x46
#define XE_KEY_G              0x47
#define XE_KEY_H              0x48
#define XE_KEY_I              0x49
#define XE_KEY_J              0x4A
#define XE_KEY_K              0x4B
#define XE_KEY_L              0x4C
#define XE_KEY_M              0x4D
#define XE_KEY_N              0x4E
#define XE_KEY_O              0x4F
#define XE_KEY_P              0x50
#define XE_KEY_Q              0x51
#define XE_KEY_R              0x52
#define XE_KEY_S              0x53
#define XE_KEY_T              0x54
#define XE_KEY_U              0x55
#define XE_KEY_V              0x56
#define XE_KEY_W              0x57
#define XE_KEY_X              0x58
#define XE_KEY_Y              0x59
#define XE_KEY_Z              0x5A

#define XE_KEY_LBUTTON        0x01
#define XE_KEY_RBUTTON        0x02
#define XE_KEY_CANCEL         0x03
#define XE_KEY_MBUTTON        0x04

#define XE_KEY_ESCAPE         0x1B
#define XE_KEY_SHIFT          0x10
#define XE_KEY_CONTROL        0x11
#define XE_KEY_MENU           0x12
#define XE_KEY_ALT            XE_KEY_MENU
#define XE_KEY_RETURN         0x13
#define XE_KEY_CAPITAL        0x14

#define XE_KEY_SPACE          0x20
#define XE_KEY_PRIOR          0x21
#define XE_KEY_NEXT           0x22
#define XE_KEY_END            0x23
#define XE_KEY_HOME           0x24
#define XE_KEY_LEFT           0x25
#define XE_KEY_UP             0x26
#define XE_KEY_RIGHT          0x27
#define XE_KEY_DOWN           0x28
#define XE_KEY_SELECT         0x29
#define XE_KEY_PRINT          0x2A
#define XE_KEY_EXECUTE        0x2B
#define XE_KEY_SNAPSHOT       0x2C
#define XE_KEY_INSERT         0x2D
#define XE_KEY_DELETE         0x2E
#define XE_KEY_HELP           0x2F

#define XE_KEY_NUMPAD0        0x60
#define XE_KEY_NUMPAD1        0x61
#define XE_KEY_NUMPAD2        0x62
#define XE_KEY_NUMPAD3        0x63
#define XE_KEY_NUMPAD4        0x64
#define XE_KEY_NUMPAD5        0x65
#define XE_KEY_NUMPAD6        0x66
#define XE_KEY_NUMPAD7        0x67
#define XE_KEY_NUMPAD8        0x68
#define XE_KEY_NUMPAD9        0x69
#define XE_KEY_MULTIPLY       0x6A
#define XE_KEY_ADD            0x6B
#define XE_KEY_SEPARATOR      0x6C
#define XE_KEY_SUBTRACT       0x6D
#define XE_KEY_DECIMAL        0x6E
#define XE_KEY_DIVIDE         0x6F
#define XE_KEY_F1             0x70
#define XE_KEY_F2             0x71
#define XE_KEY_F3             0x72
#define XE_KEY_F4             0x73
#define XE_KEY_F5             0x74
#define XE_KEY_F6             0x75
#define XE_KEY_F7             0x76
#define XE_KEY_F8             0x77
#define XE_KEY_F9             0x78
#define XE_KEY_F10            0x79
#define XE_KEY_F11            0x7A
#define XE_KEY_F12            0x7B
#define XE_KEY_F13            0x7C
#define XE_KEY_F14            0x7D
#define XE_KEY_F15            0x7E
#define XE_KEY_F16            0x7F
#define XE_KEY_F17            0x80
#define XE_KEY_F18            0x81
#define XE_KEY_F19            0x82
#define XE_KEY_F20            0x83
#define XE_KEY_F21            0x84
#define XE_KEY_F22            0x85
#define XE_KEY_F23            0x86
#define XE_KEY_F24            0x87

#define XE_KEY_NUMLOCK        0x90
#define XE_KEY_SCROLL         0x91

#define XE_KEY_LSHIFT         0xA0
#define XE_KEY_RSHIFT         0xA1
#define XE_KEY_LCONTROL       0xA2
#define XE_KEY_RCONTROL       0xA3
#define XE_KEY_LMENU          0xA4
#define XE_KEY_RMENU          0xA5


#endif //X808_INPUT_HPP
