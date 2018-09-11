//
// Created by FLXR on 9/11/2018.
//

#include <Box2D/Box2D.h>
#include <xe/math/math.hpp>
#include <xe/physics/2d/physicsworld2d.hpp>
#include <xe/physics/2d/collider2d.hpp>

namespace xe {

	Collider2D::Collider2D(PhysicsWorld2D *world, ColliderType type, Transform2D &transform) :
			type(type) {

//		b2BodyDef bodyDef;
//		bodyDef.position = transform.getPosition();
//		bodyDef.angle = to_rad();
//		bodyDef.type = b2_dynamicBody;
//		body = world->CreateBody(&bodyDef);
//
//		world->world->CreateBody()
	}

	vec2 Collider2D::getPosition() const {
		return body->GetPosition();
	}

	float Collider2D::getRotation() const {
		return to_deg(body->GetAngle());
	}

}