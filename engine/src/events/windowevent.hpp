//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_WINDOWEVENT_HPP
#define X808_WINDOWEVENT_HPP


#include "event.hpp"

namespace xe{

	class WindowResizeEvent : public Event {
	public:
		explicit WindowResizeEvent(uint width, uint height)
				: Event(getStaticType()), x(width), y(height) { }

		inline const uint getWidth() const { return x; }
		inline const uint getHeight() const { return y; }

		inline static Type getStaticType() { return Type::WINDOW_RESIZE; }

	protected:
		uint x;
		uint y;
	};

}


#endif //X808_WINDOWEVENT_HPP
