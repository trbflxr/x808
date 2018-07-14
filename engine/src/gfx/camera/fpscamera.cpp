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
		mat4 rotation = math::rotate(math::conjugate(getOrientation()));
		mat4 translation = math::translate(-position);
		viewMatrix = rotation * translation;
	}

	quat FPSCamera::getOrientation() const {
		return math::rotationY(-yaw) * math::rotationX(-pitch);
	}

	vec3 FPSCamera::getForwardDirection(const quat &orientation) const {
		return math::rotate(orientation, -vec3::ZAXIS);
	}

	vec3 FPSCamera::getUpDirection(const quat &orientation) const {
		return math::rotate(orientation, vec3::YAXIS);
	}

	vec3 FPSCamera::getRightDirection(const quat &orientation) const {
		return math::rotate(orientation, vec3::XAXIS);
	}

}}