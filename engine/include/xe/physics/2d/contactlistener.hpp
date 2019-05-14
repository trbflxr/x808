//
// Created by FLXR on 5/14/2019.
//

#ifndef X808_CONTACTLISTENER_HPP
#define X808_CONTACTLISTENER_HPP


#include <Box2D/Dynamics/b2WorldCallbacks.h>

class ContactListener : public b2ContactListener {
public:
	virtual ~ContactListener() = default;

	virtual void beginContact(b2Contact *contact) { }
	virtual void endContact(b2Contact *contact) { }

	virtual void preSolve(b2Contact *contact, const b2Manifold *oldManifold) { }
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) { }
};


#endif //X808_CONTACTLISTENER_HPP
