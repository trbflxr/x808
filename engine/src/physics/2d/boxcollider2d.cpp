//
// Created by FLXR on 9/12/2018.
//

#include <Box2D/Box2D.h>
#include <xe/physics/2d/boxcollider2d.hpp>

namespace xe {

	BoxCollider2D::BoxCollider2D(PhysicsWorld2D *world, ColliderType type, Transform2D *transform) :
			Collider2D(world, type, transform) {

		b2PolygonShape shape;
		b2Vec2 s(transform->getSize() / 2.0f);
		shape.SetAsBox(s.x, s.y);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;

		body->CreateFixture(&fixtureDef);
	}

	void BoxCollider2D::update() {
		transform->setPosition(getPosition() - transform->getSize() / 2.0f);
		transform->setRotation(getRotation());
	}

}