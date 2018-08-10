//
// Created by FLXR on 8/10/2018.
//

#include "worldobject.hpp"

namespace xe {

	WorldObject::WorldObject(const SpatialData &data) : spatialData(data) { }

	void WorldObject::rotate(const vec3 &angles) {
		spatialData.setRotationAngles(angles);

		quat r;

		if (angles.x) r *= quat(vec3::XAXIS, angles.x);
		if (angles.y) r *= quat(vec3::YAXIS, angles.y);
		if (angles.z) r *= quat(vec3::ZAXIS, angles.z);
		r = quat::normalize(r);

		spatialData.setRotationMatrix(r.toRotationMatrix());
	}

	void WorldObject::rotate(float x, float y, float z) {
		rotate({x, y, z});
	}

	void WorldObject::moveForward(float speed) {
		spatialData.move(spatialData.getLook() * speed);
	}

	void WorldObject::moveBackward(float speed) {
		spatialData.move(-spatialData.getLook() * speed);
	}

	void WorldObject::moveUp(float speed) {
		spatialData.move(spatialData.getUp() * speed);
	}

	void WorldObject::moveDown(float speed) {
		spatialData.move(-spatialData.getUp() * speed);
	}

	void WorldObject::moveRight(float speed) {
		spatialData.move(-spatialData.getStrafe() * speed);
	}

	void WorldObject::moveLeft(float speed) {
		spatialData.move(spatialData.getStrafe() * speed);
	}

}
