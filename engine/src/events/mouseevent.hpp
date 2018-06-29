//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_MOUSEEVENT_HPP
#define X808_MOUSEEVENT_HPP


#include "event.hpp"
#include "math/vec2.hpp"

namespace xe {

	class MouseButtonEvent : public Event {
	public:
		inline int32 getButton() const { return button; }

		inline float getX() const { return position.x; }
		inline float getY() const { return position.y; }
		inline const vec2 &getPosition() const { return position; }

		inline static int32 getStaticType() {
			return (int32) Event::Type::MOUSE_PRESS | (int32) Type::MOUSE_RELEASE;
		}

	protected:
		explicit MouseButtonEvent(Type type, int32 button, float x, float y) :
				Event(type), button(button), position(x, y) { }

	protected:
		int32 button;
		vec2 position;
	};


	class MousePressEvent : public MouseButtonEvent {
	public:
		explicit MousePressEvent(int32 button, float x, float y) :
				MouseButtonEvent(getStaticType(), button, x, y) { }

		inline static Type getStaticType() { return Type::MOUSE_PRESS; }
	};


	class MouseReleaseEvent : public MouseButtonEvent {
	public:
		explicit MouseReleaseEvent(int32 button, float x, float y) :
				MouseButtonEvent(getStaticType(), button, x, y) { }

		inline static Type getStaticType() { return Type::MOUSE_RELEASE; }
	};


	class MouseMoveEvent : public Event {
	public:
		explicit MouseMoveEvent(float x, float y, bool dragged) :
				Event(getStaticType()), position(x, y), dragged(dragged) { }

		inline const float getX() const { return position.x; }
		inline const float getY() const { return position.y; }
		inline const vec2 &getPosition() const { return position; }

		inline const bool isDragged() const { return dragged; }

		inline static Type getStaticType() { return Type::MOUSE_MOVE; }

	protected:
		vec2 position;
		bool dragged;
	};


	class MouseWheelEvent : public Event {
	public:
		explicit MouseWheelEvent(int32 x, int32 y) :
				Event(getStaticType()), x(x), y(y) { }

		inline const int32 getX() const { return x; }
		inline const int32 getY() const { return y; }

		inline static Type getStaticType() { return Type::SCROLL; }

	protected:
		int32 x;
		int32 y;
	};
}


#endif //X808_MOUSEEVENT_HPP
