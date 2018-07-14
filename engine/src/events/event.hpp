//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_EVENT1_HPP
#define X808_EVENT1_HPP


#include "common.hpp"
#include "xeint.hpp"

namespace xe {

#undef WINDOW_RESIZE
#undef KEY_PRESS
#undef KEY_RELEASE
#undef SCROLL
#undef MOUSE_PRESS
#undef MOUSE_RELEASE
#undef MOUSE_MOVE

	class Event {
	private:
		friend class EventDispatcher;

	public:
		enum class Type {
			WINDOW_RESIZE = BIT(0),
			KEY_PRESS = BIT(1),
			KEY_RELEASE = BIT(2),
			SCROLL = BIT(3),
			MOUSE_PRESS = BIT(4),
			MOUSE_RELEASE = BIT(5),
			MOUSE_MOVE = BIT(6)
		};

	public:
		inline Type getType() const { return type; }
		inline bool isHandled() const { return handled; }

	protected:
		explicit Event(Type type) : type(type), handled(false) { }

	protected:
		bool handled;
		Type type;
	};

}


#endif //X808_EVENT1_HPP
