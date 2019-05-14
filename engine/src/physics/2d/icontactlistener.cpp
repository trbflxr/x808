//
// Created by FLXR on 5/14/2019.
//

#include "icontactlistenerimpl.hpp"
#include <xe/physics/2d/icontactlistener.hpp>

namespace xe {

	IContactListener::IContactListener() {
		listener = new internal::IContactListenerImpl(this);
	}

	IContactListener::~IContactListener() {
		delete listener;
	}

}