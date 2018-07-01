//
// Created by FLXR on 7/1/2018.
//

#include "transform.hpp"

xe::Transform::Transform() :
		position(0, 0, 0),
		rotation(0, 0, 0, 1),
		scale(1, 1, 1),
		parent(nullptr),
		parentMatrix(1.0f) { }

void xe::Transform::move(const xe::vec3 &direction) {
	position += direction;
}

void xe::Transform::rotate(float deg, const xe::vec3 &axis) {
	rotation = math::rotation(to_rad(deg), axis) * math::normalize(rotation);
}

void xe::Transform::lookAt(const xe::vec3 &point, const xe::vec3 &up) {
	rotation = getLookAtRotation(point, up);
}

xe::quat xe::Transform::getLookAtRotation(const xe::vec3 &point, const xe::vec3 &up) const {
	return xe::quat(math::initRotation(math::normalize(point - position), up));
}

xe::mat4 xe::Transform::getTransformation() const {
	mat4 t = math::translate(position);
	mat4 r = rotation.toRotationMatrix();
	mat4 s = math::scale(scale);

	return getParentMatrix() * t * r * s;
}

xe::quat xe::Transform::getTransformedRot() const {
	return parent ? parent->getTransformedRot() * rotation : rotation;
}

xe::mat4 xe::Transform::getParentMatrix() const {
	return parent ? parent->getTransformation() : mat4(1.0f);
}

