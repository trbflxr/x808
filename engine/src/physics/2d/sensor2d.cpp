//
// Created by FLXR on 5/14/2019.
//

#include <Box2D/Box2D.h>
#include <xe/utils/assert.hpp>
#include <xe/physics/2d/sensor2d.hpp>

namespace xe {

	Sensor2D::Sensor2D(PhysicsWorld2D *world, RectangleShape *rect, const vec2 &center, float rotation) :
			world(world),
			center(center),
			rect(rect),
			fixture(nullptr) {

		shape = new b2PolygonShape();
		fixtureDef = new b2FixtureDef();

		const b2Vec2 s(rect->getSize() / 2.0f);
		shape->SetAsBox(s.x, s.y, center, to_rad(rotation));

		fixtureDef->shape = shape;
		fixtureDef->isSensor = true;
	}

	Sensor2D::~Sensor2D() {
		delete shape;
		delete fixtureDef;
	}

	void Sensor2D::update() {
		if (fixture) {
//			rect->setPosition(vec2(fixture->GetBody()->GetPosition()) + center);
			rect->setPosition(vec2(fixture->GetBody()->GetPosition()) );
			rect->setRotation(to_deg(fixture->GetBody()->GetAngle()));
		}
	}

	uint16 Sensor2D::getCategoryBits() const {
		return filter.categoryBits;
	}

	void Sensor2D::setCategoryBits(uint16 bits) {
		XE_ASSERT(fixture, "You have to attach sensor first");

		filter.categoryBits = bits;
		fixture->SetFilterData(filter);
	}

	uint16 Sensor2D::getMask() const {
		return filter.maskBits;
	}

	void Sensor2D::setMask(uint16 bits) {
		XE_ASSERT(fixture, "You have to attach sensor first");

		filter.maskBits = bits;
		fixture->SetFilterData(filter);
	}

	void Sensor2D::setUserData(void *data) {
		XE_ASSERT(fixture, "You have to attach sensor first");

		fixture->SetUserData(data);
	}

	void *Sensor2D::getUserData() const {
		XE_ASSERT(fixture, "You have to attach sensor first");

		return fixture->GetUserData();
	}

}

