//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_EVENTDISPATCHER_HPP
#define X808_EVENTDISPATCHER_HPP


#include <functional>
#include "event.hpp"

namespace xe{

	class EventDispatcher {
	public:
		explicit EventDispatcher(Event &event) : event(event) { }

		template<typename T>
		void dispatch(std::function<bool(T &)> func) {
			if ((int32) event.getType() & (int32) T::getStaticType()) event.handled = func(*(T *) &event);
		}

	private:
		Event &event;
	};

}


#endif //X808_EVENTDISPATCHER_HPP
