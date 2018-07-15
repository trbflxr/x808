//
// Created by FLXR on 7/14/2018.
//

#include <application/application.hpp>
#include "dummyplayer.hpp"

using namespace xe;

DummyPlayer::DummyPlayer(xe::gfx::FPSCamera *camera) :
		camera(camera) {

	mouseSensitivity = 0.003f;
	speed = 4.0f;
	sprintSpeed = speed * 4.0f;
	mouseWasGrabbed = false;
	mouseLocked = false;
}

DummyPlayer::~DummyPlayer() {
	delete camera;
}

void DummyPlayer::update(float delta) {
	static Window &window = Application::get().getWindow();
	static vec2u windowSize = window.getSize();
	static vec2i windowCenter = vec2i(windowSize.x / 2, windowSize.y / 2);

	static vec2i lastMousePosition = Mouse::getPosition();

	if (mouseLocked) {
		window.setMouseCursorGrabbed(true);
		window.setMouseCursorVisible(false);
	} else {
		window.setMouseCursorGrabbed(false);
		window.setMouseCursorVisible(true);
		mouseWasGrabbed = false;
	}

	if (window.isMouseCursorGrabbed()) {
		vec2i mouseChange = Mouse::getPosition() - lastMousePosition;

		if (mouseWasGrabbed) {
			camera->setYaw(camera->getYaw() + mouseChange.x* mouseSensitivity);
			camera->setPitch(camera->getPitch() + mouseChange.y* mouseSensitivity);
		}
		mouseWasGrabbed = true;

		Mouse::setPosition(windowCenter, window);
		lastMousePosition = Mouse::getPosition();

		quat orientation = camera->getOrientation();
		rotation = orientation.toEulerAngles();

		vec3 forward = camera->getForwardDirection(orientation);
		vec3 right = camera->getRightDirection(orientation);
		vec3 up = vec3::YAXIS;
		float speed = Keyboard::isKeyPressed(Keyboard::LControl) ? sprintSpeed : DummyPlayer::speed;
		if (Keyboard::isKeyPressed(Keyboard::W))
			position += forward * speed * delta;
		else if (Keyboard::isKeyPressed(Keyboard::S))
			position -= forward * speed * delta;

		if (Keyboard::isKeyPressed(Keyboard::A))
			position -= right * speed * delta;
		else if (Keyboard::isKeyPressed(Keyboard::D))
			position += right * speed * delta;

		if (Keyboard::isKeyPressed(Keyboard::Space))
			position += up * speed * delta;
		if (Keyboard::isKeyPressed(Keyboard::LShift))
			position -= up * speed * delta;

		camera->setPosition(position);
		camera->setRotation(rotation);
	}

	if (!mouseLocked) {
		window.setMouseCursorGrabbed(false);
		window.setMouseCursorVisible(true);
		mouseWasGrabbed = false;
	}

	camera->update();
}

void DummyPlayer::input(xe::Event &event) {
	if (event.type == Event::MouseButtonPressed) {
		if (event.mouseButton.button == Mouse::Right) {
			mouseLocked = !mouseLocked;
		}
		event.handled = true;
	}
	if (event.type == Event::KeyPressed) {
		if (event.key.code == Keyboard::Escape) {
			mouseLocked = false;
		}
		event.handled = true;
	}
}
