//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_KEYEVENT_HPP
#define X808_KEYEVENT_HPP


#include "event.hpp"

namespace xe {

	class KeyEvent : public Event {
	public:
		inline int32 getKey() const { return code; }

		inline static int32 getStaticType() {
			return (int32) Type::KEY_PRESS | (int32) Type::KEY_RELEASE;
		}

	protected:
		explicit KeyEvent(Type type, int32 code) :
				Event(type), code(code) { }

	protected:
		int32 code;
	};


	class  KeyPressEvent : public KeyEvent {
	public:
		explicit KeyPressEvent(int32 code, int32 modifiers, int32 repeat) :
				KeyEvent(getStaticType(), code), modifiers(modifiers), repeat(repeat) { }

		inline int32 getModifiers() const { return modifiers; }
		inline int32 getRepeat() const { return repeat; }
		inline bool isModifier(int modifier) const { return (bool) (modifiers & modifier); }

		inline static Type getStaticType() { return Event::Type::KEY_PRESS; }

	protected:
		int32 modifiers;
		int32 repeat;
	};

	class KeyReleaseEvent : public KeyEvent {
	public:
		explicit KeyReleaseEvent(int32 code) :
				KeyEvent(getStaticType(), code) { }

		inline static Type getStaticType() { return Event::Type::KEY_RELEASE; }
	};
}


#endif //X808_KEYEVENT_HPP
