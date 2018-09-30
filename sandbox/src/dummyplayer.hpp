//
// Created by FLXR on 9/16/2018.
//

#ifndef X808_DUMMYPLAYER_HPP
#define X808_DUMMYPLAYER_HPP


#include <xe/gfx/camera.hpp>
#include <xe/app/application.hpp>

class DummyPlayer {
public:
	explicit DummyPlayer(xe::Camera *camera,
	                     float speed = 4.0f,
	                     float sprint = 4.0f,
	                     float sensitivity = 0.15f) :
			mouseLocked(false),
			camera(camera),
			mouseSensitivity(sensitivity),
			speed(speed),
			sprintSpeed(speed * sprint) { }

	void update(float delta) {
		static xe::Window &window = xe::Application::get().getWindow();
		static xe::vec2 windowSize = window.getSize();
		static xe::vec2 windowCenter = windowSize / 2.0f;
		static xe::vec2 lastMousePosition = xe::Mouse::getPosition();

		xe::Transform &transform = camera->transform;

		if (mouseLocked) {
			window.setMouseCursorGrabbed(true);
			window.setMouseCursorVisible(false);
		} else {
			window.setMouseCursorGrabbed(false);
			window.setMouseCursorVisible(true);
		}

		if (window.isMouseCursorGrabbed()) {
			xe::vec2 mouseChange = xe::Mouse::getPosition() - lastMousePosition;

			//rotate
			transform.rotate(-xe::vec3::UnitY, mouseChange.x * mouseSensitivity);
			transform.rotate(transform.getRotation().getLeft(), mouseChange.y * mouseSensitivity);

			xe::Mouse::setPosition(windowCenter, window);
			lastMousePosition = xe::Mouse::getPosition();

			//move
			float speed = xe::Keyboard::isKeyPressed(xe::Keyboard::LControl) ? sprintSpeed : DummyPlayer::speed;
			if (xe::Keyboard::isKeyPressed(xe::Keyboard::W)) {
				move(transform, transform.getRotation().getForward(), speed * delta);
			}
			if (xe::Keyboard::isKeyPressed(xe::Keyboard::S)) {
				move(transform, transform.getRotation().getBackward(), speed * delta);
			}

			if (xe::Keyboard::isKeyPressed(xe::Keyboard::A)) {
				move(transform, transform.getRotation().getLeft(), speed * delta);
			}
			if (xe::Keyboard::isKeyPressed(xe::Keyboard::D)) {
				move(transform, transform.getRotation().getRight(), speed * delta);
			}

			if (xe::Keyboard::isKeyPressed(xe::Keyboard::Space)) {
				move(transform, xe::vec3::UnitY, speed * delta);
			}
			if (xe::Keyboard::isKeyPressed(xe::Keyboard::LShift)) {
				move(transform, -xe::vec3::UnitY, speed * delta);
			}

			camera->update();
		}

		if (!mouseLocked) {
			window.setMouseCursorGrabbed(false);
			window.setMouseCursorVisible(true);
		}
	}

	void input(xe::Event &event) {
		if (event.type == xe::Event::MouseButtonPressed) {
			if (event.mouseButton.button == xe::Mouse::Right) {
				mouseLocked = !mouseLocked;
			}
			event.handled = true;
		}
		if (event.type == xe::Event::KeyPressed) {
			if (event.key.code == xe::Keyboard::Escape) {
				mouseLocked = false;
			}
			event.handled = true;
		}
	}

private:
	void move(xe::Transform &transform, const xe::vec3 &dir, float amt) {
		transform.setPosition(transform.getPosition() + (dir * amt));
	}

private:
	bool mouseLocked;

	xe::Camera *camera;

	float mouseSensitivity;
	float speed;
	float sprintSpeed;
};


#endif //X808_DUMMYPLAYER_HPP
