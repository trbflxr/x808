//
// Created by FLXR on 5/14/2019.
//

#ifndef X808_ICONTACTLISTENER_HPP
#define X808_ICONTACTLISTENER_HPP


#include <xe/common.hpp>

class b2Contact;
struct b2Manifold;
struct b2ContactImpulse;

namespace xe {

	namespace internal {
		class IContactListenerImpl;
	}

	class XE_API IContactListener {
	public:
		explicit IContactListener();
		virtual ~IContactListener();

		virtual void beginContact(b2Contact *contact) { }
		virtual void endContact(b2Contact *contact) { }

		virtual void preSolve(b2Contact *contact, const b2Manifold *oldManifold) { }
		virtual void postSolve(b2Contact *contact, const b2ContactImpulse *impulse) { }

	private:
		friend class PhysicsWorld2D;

		internal::IContactListenerImpl *listener;
	};

}


#endif //X808_ICONTACTLISTENER_HPP
