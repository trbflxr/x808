//
// Created by FLXR on 7/13/2018.
//

#include "fpscamera.hpp"
#include "application/input.hpp"

namespace xe { namespace gfx {

	FPSCamera::FPSCamera(const mat4 &projection) :
			Camera(projection) {

	}

	FPSCamera::~FPSCamera() {

	}

	void FPSCamera::focus() {
		Input::setMouseCursor(XE_NO_CURSOR);
	}

	void FPSCamera::update() {
		//temp
		viewMatrix = math::translate(-position);
	}

	quat FPSCamera::getOrientation() const {
		return xe::quat();
	}

	vec3 FPSCamera::getForwardDirection(const quat &orientation) const {
		return xe::vec3();
	}

	vec3 FPSCamera::getUpDirection(const quat &orientation) const {
		return xe::vec3();
	}

	vec3 FPSCamera::getRightDirection(const quat &orientation) const {
		return xe::vec3();
	}

}}