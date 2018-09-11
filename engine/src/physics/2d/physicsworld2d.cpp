//
// Created by FLXR on 9/11/2018.
//

#include <Box2D/Box2D.h>
#include <xe/utils/log.hpp>
#include <xe/physics/2d/physicsworld2d.hpp>

namespace xe {

	PhysicsWorld2D::PhysicsWorld2D(const vec2 &gravity) {
		world = new b2World(b2Vec2(gravity, false));
	}

	PhysicsWorld2D::~PhysicsWorld2D() {
		delete world;
	}

	void PhysicsWorld2D::test(const vec2 &pos, const vec2 &size, bool f) {
		if (!f) {
			b2BodyDef bodyDef;
			bodyDef.position = pos;
			bodyDef.angle = to_rad(45.0f);
			bodyDef.type = b2_dynamicBody;
			body = world->CreateBody(&bodyDef);

			b2PolygonShape shape;
			b2Vec2 s(size / 2.0f);
			shape.SetAsBox(s.x, s.y);

			b2FixtureDef fixtureDef;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.07f;
			fixtureDef.shape = &shape;
			body->CreateFixture(&fixtureDef);
		} else {
			b2BodyDef bodyDef;
			bodyDef.position = pos;
			bodyDef.angle = to_rad(15.0f);
			bodyDef.type = b2_staticBody;
			floor = world->CreateBody(&bodyDef);

			b2PolygonShape shape;
			b2Vec2 s(size / 2.0f);
			shape.SetAsBox(s.x, s.y);

			b2FixtureDef fixtureDef;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.07f;
			fixtureDef.shape = &shape;
			floor->CreateFixture(&fixtureDef);
		}
	}

	void PhysicsWorld2D::update(float timeStep, uint velocityIterations, uint positionIterations) {
		world->Step(timeStep, velocityIterations, positionIterations);

		for (b2Body *b = world->GetBodyList(); b != nullptr; b = b->GetNext()) {
//			XE_INFO("angle: ", to_deg(b->GetAngle()));
		}
	}

	vec2 PhysicsWorld2D::getPos(bool f) {
		return f ? floor->GetPosition() : body->GetPosition();
	}

	float PhysicsWorld2D::getRot(bool f) {
		return f ? to_deg(floor->GetAngle()) : to_deg(body->GetAngle());
	}

}