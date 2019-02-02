//
// Created by FLXR on 9/18/2018.
//

#include <Box2D/Box2D.h>
#include <xe/physics/2d/physicsworld2d.hpp>
#include <xe/physics/2d/polygoncollider2d.hpp>
#include <xe/utils/assert.hpp>

namespace xe {

	PolygonCollider2D::PolygonCollider2D(PhysicsWorld2D *world, ColliderType type, Polygon *polygon)
			: Collider2D(world, type, polygon) {

		XE_ASSERT(false, "Convex polygons is not implemented");

		shape = new b2PolygonShape();
	}

	PolygonCollider2D::~PolygonCollider2D() {
		delete shape;
	}

	void PolygonCollider2D::update() {
		Polygon *polygon = (Polygon *) transformable;

		if (polygon->isPointsChanged()) {
			polygon->setPointsChanged(false);

			world->destroyBody(body);
			create(world);

			const uint size = polygon->getPointCount();
			const vec2 *rp = polygon->getRawPoints();

			b2Vec2 points[size];

			for (uint i = 0; i < size; ++i) {
				points[i] = rp[i];
			}

			shape->Set(points, size);

			fixtureDef->shape = shape;

			body->CreateFixture(fixtureDef);
		}

		transformable->setPosition(getPosition());
		transformable->setRotation(getRotation());
	}

}