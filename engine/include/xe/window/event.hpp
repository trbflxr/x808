//
// Created by FLXR on 7/14/2018.
//

#ifndef X808_EVENT_HPP
#define X808_EVENT_HPP


#include <xe/xeint.hpp>
#include <xe/window/keyboard.hpp>
#include <xe/window/mouse.hpp>

namespace xe {

	struct Event {
		struct SizeEvent {
			uint width;
			uint height;
		};

		struct KeyEvent {
			Keyboard::Key code;
			bool alt;
			bool control;
			bool shift;
			bool system;
		};

		struct TextEvent {
			uint unicode;
		};

		struct MouseMoveEvent {
			int32 x;
			int32 y;
		};

		struct MouseButtonEvent {
			Mouse::Button button;
			int32 x;
			int32 y;
		};

		struct MouseWheelEvent {
			int32 delta;
			int32 x;
			int32 y;
		};


		enum EventType {
			Closed,
			Resized,
			LostFocus,
			GainedFocus,
			TextEntered,
			KeyPressed,
			KeyReleased,
			MouseWheelMoved,
			MouseButtonPressed,
			MouseButtonReleased,
			MouseMoved,
			MouseEntered,
			MouseLeft,

			Count
		};

		EventType type;

		union {
			SizeEvent size;
			KeyEvent key;
			TextEvent text;
			MouseMoveEvent mouseMove;
			MouseButtonEvent mouseButton;
			MouseWheelEvent mouseWheel;
		};

		bool handled = false;
	};

}

#endif //X808_EVENT_HPP
