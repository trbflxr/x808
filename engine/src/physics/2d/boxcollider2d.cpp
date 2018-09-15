//
// Created by FLXR on 9/12/2018.
//

#include <Box2D/Box2D.h>
#include <xe/physics/2d/boxcollider2d.hpp>

namespace xe {

	BoxCollider2D::BoxCollider2D(PhysicsWorld2D *world, ColliderType type, ITransformable2D *transformable) :
			Collider2D(world, type, transformable) {

		b2PolygonShape shape;
		b2Vec2 s(transformable->getSize() / 2.0f);
		shape.SetAsBox(s.x, s.y);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;

		body->CreateFixture(&fixtureDef);
	}

	void BoxCollider2D::update() {
		transformable->setPosition(getPosition() - transformable->getSize() / 2.0f);
		transformable->setRotation(getRotation());
	}

}