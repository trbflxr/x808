//
// Created by FLXR on 5/14/2019.
//

#ifndef X808_ICONTACTLISTENERIMPL_HPP
#define X808_ICONTACTLISTENERIMPL_HPP


#include <xe/physics/2d/icontactlistener.hpp>
#include <Box2D/Dynamics/b2WorldCallbacks.h>

namespace xe::internal {

  class IContactListenerImpl : public b2ContactListener {
  public:
    explicit IContactListenerImpl(IContactListener *listener) : listener(listener) { }

    void BeginContact(b2Contact *contact) override { listener->beginContact(contact); }
    void EndContact(b2Contact *contact) override { listener->endContact(contact); }

    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override {
      listener->preSolve(contact, oldManifold);
    }

    void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) override {
      listener->postSolve(contact, impulse);
    }

  private:
    IContactListener *listener;
  };

}


#endif //X808_ICONTACTLISTENERIMPL_HPP
