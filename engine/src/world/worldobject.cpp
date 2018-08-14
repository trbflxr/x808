//
// Created by FLXR on 8/13/2018.
//

#include "worldobject.hpp"

namespace xe {

	WorldObject::WorldObject(const SpatialData &data) : spatial(data) { }

	void WorldObject::rotate(const vec3 &angles) {
		spatial.rotationAngles = angles;

		spatial.setRotationMatrix(quat::rotation(angles).toRotationMatrix());
	}

	void WorldObject::rotate(float x, float y, float z) {
		rotate({x, y, z});
	}

	void WorldObject::moveForward(float speed) {
		spatial.position += spatial.look * speed;
	}

	void WorldObject::moveBackward(float speed) {
		spatial.position -= spatial.look * speed;
	}

	void WorldObject::moveUp(float speed) {
		spatial.position -= spatial.up * speed;
	}

	void WorldObject::moveDown(float speed) {
		spatial.position += spatial.up * speed;
	}

	void WorldObject::moveRight(float speed) {
		spatial.position -= spatial.strafe * speed;
	}

	void WorldObject::moveLeft(float speed) {
		spatial.position += spatial.strafe * speed;
	}

}