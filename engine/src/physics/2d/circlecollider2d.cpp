//
// Created by FLXR on 9/18/2018.
//

#include <Box2D/Box2D.h>
#include <xe/physics/2d/physicsworld2d.hpp>
#include <xe/physics/2d/circlecollider2d.hpp>

namespace xe {

	CircleCollider2D::CircleCollider2D(PhysicsWorld2D *world, ColliderType type, CircleShape *circle) :
			Collider2D(world, type, circle) {

		shape = new b2CircleShape();
	}

	CircleCollider2D::~CircleCollider2D() {
		delete shape;
	}

	void CircleCollider2D::update() {
		CircleShape *circle = (CircleShape *) transformable;

		if (circle->isRadiusChanged()) {
			circle->setRadiusChanged(false);

			recreate();
		}

		transformable->setPosition(getPosition());
		transformable->setRotation(getRotation());
	}

	void CircleCollider2D::recreate() {
		const CircleShape *circle = (CircleShape *) transformable;

		world->destroyBody(body);
		create(world);

		shape->m_radius = xeb2(circle->getRadius());

		fixtureDef->shape = shape;

		body->CreateFixture(fixtureDef);
	}

}