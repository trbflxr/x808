//
// Created by FLXR on 7/14/2018.
//

#include <application/input.hpp>
#include <application/application.hpp>
#include "dummyplayer.hpp"

using namespace xe;

DummyPlayer::DummyPlayer(xe::gfx::FPSCamera *camera) :
		camera(camera) {

	mouseSensitivity = 1.00f;
	speed = 4.0f;
	sprintSpeed = speed * 4.0f;
	mouseWasGrabbed = false;
}

DummyPlayer::~DummyPlayer() {
	delete camera;
}

void DummyPlayer::update(float delta) {
	static uint windowWidth = Application::get().getWindowWidth();
	static uint windowHeight = Application::get().getWindowHeight();

	static vec2 windowCenter = vec2(windowWidth / 2.0f, windowHeight / 2.0f);

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
		mouse -= windowCenter;
		mouse *= (mouseSensitivity * delta);
		if (mouseWasGrabbed) {
			camera->setYaw(camera->getYaw() + mouse.x);
			camera->setPitch(camera->getPitch() + mouse.y);
		}
		mouseWasGrabbed = true;
		Input::setMousePosition(windowCenter);


		quat orientation = camera->getOrientation();
		rotation = orientation.toEulerAngles();

		vec3 forward = camera->getForwardDirection(orientation);
		vec3 right = camera->getRightDirection(orientation);
		vec3 up = vec3::YAXIS;
		float speed = Input::isKeyPressed(XE_KEY_CONTROL) ? sprintSpeed : DummyPlayer::speed;
		if (Input::isKeyPressed(XE_KEY_W))
			position += forward * speed * delta;
		else if (Input::isKeyPressed(XE_KEY_S))
			position -= forward * speed * delta;

		if (Input::isKeyPressed(XE_KEY_A))
			position -= right * speed * delta;
		else if (Input::isKeyPressed(XE_KEY_D))
			position += right * speed * delta;

		if (Input::isKeyPressed(XE_KEY_SPACE))
			position += up * speed * delta;
		if (Input::isKeyPressed(XE_KEY_SHIFT))
			position -= up * speed * delta;

		camera->setPosition(position);
		camera->setRotation(rotation);
	}

	if (Input::isKeyPressed(XE_KEY_ESCAPE)) {
		Input::setMouseGrabbed(false);
		Input::setMouseCursor(1);
		mouseWasGrabbed = false;
	}


	camera->update();
}
