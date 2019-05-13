//
// Created by FLXR on 9/11/2018.
//

#include <Box2D/Box2D.h>
#include <xe/utils/logger.hpp>
#include <xe/physics/2d/collider2d.hpp>
#include <xe/physics/2d/physicsworld2d.hpp>

namespace xe {

	PhysicsWorld2D::PhysicsWorld2D(const vec2 &gravity) {
		world = new b2World(b2Vec2(gravity, false));
	}

	PhysicsWorld2D::~PhysicsWorld2D() {
		delete world;
	}

	void PhysicsWorld2D::update(float timeStep, uint velocityIterations, uint positionIterations) {
		world->Step(timeStep, velocityIterations, positionIterations);

		for (b2Body *b = world->GetBodyList(); b != nullptr; b = b->GetNext()) {
			if (b->IsAwake()) {
				Collider2D *c = static_cast<Collider2D *>( b->GetUserData());
				if (c) c->update();
			}
		}
	}

	b2Body *PhysicsWorld2D::createBody(b2BodyDef *bodyDef) {
		return world->CreateBody(bodyDef);
	}

	void PhysicsWorld2D::destroyBody(b2Body *body) {
		if (body) {
			world->DestroyBody(body);
			body = nullptr;
		}
	}

	void PhysicsWorld2D::destroyCollider(Collider2D *collider) {
		if (collider->body ) {
			world->DestroyBody(collider->body);
			collider->body = nullptr;
		}
	}

}