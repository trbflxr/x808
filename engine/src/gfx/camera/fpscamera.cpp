//
// Created by FLXR on 7/13/2018.
//

#include "fpscamera.hpp"
#include "application/input.hpp"
#include "application/application.hpp"

namespace xe { namespace gfx {

	FPSCamera::FPSCamera(const mat4 &projection) :
			Camera(projection) {

		mouseSensitivity = 0.002f;
		speed = 0.2f;
		sprintSpeed = speed * 4.0f;
		mouseWasGrabbed = false;

		yaw = 2.4f;
		pitch = 0.7f;
	}

	FPSCamera::~FPSCamera() {

	}

	void FPSCamera::focus() {
		Input::setMouseCursor(XE_NO_CURSOR);
	}

	void FPSCamera::update() {
		//temp
		uint windowWidth = Application::get().getWindowWidth();
		uint windowHeight = Application::get().getWindowHeight();

		vec2 windowCenter = vec2(windowWidth / 2.0f, windowHeight / 2.0f);

		if (Input::isMouseButtonClicked(XE_MOUSE_RIGHT)) {
			if (!Input::isMouseGrabbed()) {
				Input::setMouseGrabbed(true);
				Input::setMouseCursor(XE_NO_CURSOR);
			} else {
				Input::setMouseGrabbed(false);
				Input::setMouseCursor(1);
				mouseWasGrabbed = false;
			}
		}

		if (Input::isMouseGrabbed()) {
			vec2 mouse = Input::getMousePosition();
			mouse.x -= windowCenter.x;
			mouse.y -= windowCenter.y;
			if (mouseWasGrabbed) {
				yaw += mouse.x * mouseSensitivity;
				pitch += mouse.y * mouseSensitivity;
			}
			mouseWasGrabbed = true;
			Input::setMousePosition(windowCenter);

			quat orientation = getOrientation();
			rotation = orientation.toEulerAngles() * (180.0f / XE_PI);

			vec3 forward = getForwardDirection(orientation);
			vec3 right = getRightDirection(orientation);
			vec3 up = vec3::YAXIS;
			float speed = Input::isKeyPressed(XE_KEY_SHIFT) ? sprintSpeed : FPSCamera::speed;
			if (Input::isKeyPressed(XE_KEY_W))
				position += forward * speed;
			else if (Input::isKeyPressed(XE_KEY_S))
				position -= forward * speed;

			if (Input::isKeyPressed(XE_KEY_A))
				position -= right * speed;
			else if (Input::isKeyPressed(XE_KEY_D))
				position += right * speed;

			if (Input::isKeyPressed(XE_KEY_SPACE))
				position += up * speed;
			if (Input::isKeyPressed(XE_KEY_CONTROL))
				position -= up * speed;

			mat4 rotation = math::rotate(math::conjugate(orientation));
			mat4 translation = math::translate(-position);
			viewMatrix = rotation * translation;
		}

		if (Input::isKeyPressed(XE_KEY_ESCAPE)) {
			Input::setMouseGrabbed(false);
			Input::setMouseCursor(1);
			mouseWasGrabbed = false;
		}
	}

	quat FPSCamera::getOrientation() const {
		return math::rotationY(-yaw) * math::rotationX(-pitch);
	}

	vec3 FPSCamera::getForwardDirection(const quat &orientation) const {
		vec3 zaxis = vec3::ZAXIS;
		return math::rotate(orientation, -zaxis);
	}

	vec3 FPSCamera::getUpDirection(const quat &orientation) const {
		return math::rotate(orientation, vec3::YAXIS);
	}

	vec3 FPSCamera::getRightDirection(const quat &orientation) const {
		return math::rotate(orientation, vec3::XAXIS);
	}

}}