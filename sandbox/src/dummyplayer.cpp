//
// Created by FLXR on 7/14/2018.
//

#include <application/application.hpp>
#include "dummyplayer.hpp"

using namespace xe;

DummyPlayer::DummyPlayer(xe::gfx::Camera *camera) :
		camera(camera) {

	mouseSensitivity = 0.15f;
	speed = 4.0f;
	sprintSpeed = speed * 4.0f;
	mouseLocked = false;

	camera->hookEntity(this);
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
	}

	if (window.isMouseCursorGrabbed()) {
		vec2i mouseChange = Mouse::getPosition() - lastMousePosition;

		//rotate
		transform.rotate(-vec3::YAXIS, to_rad(mouseChange.x * mouseSensitivity));
		transform.rotate(transform.getRotation().getLeft(), to_rad(mouseChange.y * mouseSensitivity));

		Mouse::setPosition(windowCenter, window);
		lastMousePosition = Mouse::getPosition();


		//move
		float speed = Keyboard::isKeyPressed(Keyboard::LControl) ? sprintSpeed : DummyPlayer::speed;
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			move(transform.getRotation().getForward(), speed * delta);
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			move(transform.getRotation().getBackward(), speed * delta);
		}

		if (Keyboard::isKeyPressed(Keyboard::A)) {
			move(transform.getRotation().getLeft(), speed * delta);
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			move(transform.getRotation().getRight(), speed * delta);
		}

		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			move(vec3::YAXIS, speed * delta);
		}
		if (Keyboard::isKeyPressed(Keyboard::LShift)) {
			move(-vec3::YAXIS, speed * delta);
		}

		camera->update();
	}

	if (!mouseLocked) {
		window.setMouseCursorGrabbed(false);
		window.setMouseCursorVisible(true);
	}

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

void DummyPlayer::move(const xe::vec3 &dir, float amt) {
	transform.setTranslation(transform.getTranslation() + (dir * amt));
}
