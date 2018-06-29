//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_IEVENTLISTENER_HPP
#define X808_IEVENTLISTENER_HPP


#include "event.hpp"

namespace xe {

	class IEventListener {
	public:
		virtual void onEvent(Event &event) = 0;
	};

}


#endif //X808_IEVENTLISTENER_HPP
