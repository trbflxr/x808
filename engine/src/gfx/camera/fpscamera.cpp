//
// Created by FLXR on 7/13/2018.
//

#include "fpscamera.hpp"

namespace xe { namespace gfx {

	FPSCamera::FPSCamera(const mat4 &projection) :
			Camera(projection),
			yaw(0.0f),
			pitch(0.0f) { }


	void FPSCamera::update() {
		mat4 rotation = mat4::rotate(quat::conjugate(getOrientation()));
		mat4 translation = mat4::translate(-position);
		viewMatrix = rotation * translation;
	}

	quat FPSCamera::getOrientation() const {
		return quat::rotationY(-yaw) * quat::rotationX(-pitch);
	}

	vec3 FPSCamera::getForwardDirection(const quat &orientation) const {
		return quat::rotate(orientation, -vec3::ZAXIS);
	}

	vec3 FPSCamera::getUpDirection(const quat &orientation) const {
		return quat::rotate(orientation, vec3::YAXIS);
	}

	vec3 FPSCamera::getRightDirection(const quat &orientation) const {
		return quat::rotate(orientation, vec3::XAXIS);
	}

}}