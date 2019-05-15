//
// Created by FLXR on 9/12/2018.
//

#include <Box2D/Box2D.h>
#include <xe/physics/2d/physicsworld2d.hpp>
#include <xe/physics/2d/boxcollider2d.hpp>

namespace xe {

  BoxCollider2D::BoxCollider2D(PhysicsWorld2D *world, ColliderType type, RectangleShape *rect, bool fixedRotation) :
      Collider2D(world, type, rect, fixedRotation) {

    shape = new b2PolygonShape();
  }

  BoxCollider2D::~BoxCollider2D() {
    delete shape;
  }

  void BoxCollider2D::update() {
    RectangleShape *rect = (RectangleShape *) transformable;

    if (rect->isSizeChanged()) {
      rect->setSizeChanged(false);

      recreate();
    }

    transformable->setPosition(getPosition());
    transformable->setRotation(getRotation());
  }

  void BoxCollider2D::recreate() {
    const RectangleShape *rect = (RectangleShape *) transformable;

    world->destroyBody(body);
    create(world);

    b2Vec2 s(rect->getSize() / 2.0f);
    shape->SetAsBox(s.x, s.y);

    fixtureDef->shape = shape;

    body->CreateFixture(fixtureDef);
  }

}