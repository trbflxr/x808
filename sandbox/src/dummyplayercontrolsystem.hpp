//
// Created by FLXR on 7/29/2018.
//

#ifndef X808_DUMMYPLAYERCONTROLSYSTEM_HPP
#define X808_DUMMYPLAYERCONTROLSYSTEM_HPP


#include <xe/ecs/ecssystem.hpp>
#include <xe/ecs/components/transformcomponent.hpp>
#include <xe/app/application.hpp>
#include <xe/window/window.hpp>
#include <xe/window/keyboard.hpp>
#include <xe/window/mouse.hpp>
#include "dummyplayercomponent.hpp"

class DummyPlayerControlSystem : public xe::BaseECSSystem {
public:
	explicit DummyPlayerControlSystem() :
			BaseECSSystem(),
			mouseLocked(false) {

		addComponentType(DummyPlayerComponent::ID);
		addComponentType(xe::TransformComponent::ID);
	}

	void updateComponents(float delta, xe::BaseECSComponent **components) override {
		static xe::Window &window = xe::Application::get().getWindow();
		static xe::vec2u windowSize = window.getSize();
		static xe::vec2i windowCenter = xe::vec2i(windowSize.x / 2, windowSize.y / 2);
		static xe::vec2i lastMousePosition = xe::Mouse::getPosition();

		DummyPlayerComponent *player = (DummyPlayerComponent *) components[0];
		xe::Transform &transform = ((xe::TransformComponent *) components[1])->transform;

		if (mouseLocked) {
			window.setMouseCursorGrabbed(true);
			window.setMouseCursorVisible(false);
		} else {
			window.setMouseCursorGrabbed(false);
			window.setMouseCursorVisible(true);
		}

		if (window.isMouseCursorGrabbed()) {
			xe::vec2i mouseChange = xe::Mouse::getPosition() - lastMousePosition;


			//rotate
			transform.rotate(-xe::vec3::UnitY, mouseChange.x * player->mouseSensitivity);
			transform.rotate(transform.getRotation().getLeft(), mouseChange.y * player->mouseSensitivity);

			xe::Mouse::setPosition(windowCenter, window);
			lastMousePosition = xe::Mouse::getPosition();


			//move
			float speed = xe::Keyboard::isKeyPressed(xe::Keyboard::LControl) ? player->sprintSpeed : player->speed;
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

			memcpy(&player->camera->transform, &transform, sizeof(xe::Transform));
			player->camera->update();
		}

		if (!mouseLocked) {
			window.setMouseCursorGrabbed(false);
			window.setMouseCursorVisible(true);
		}
	}

	void inputComponents(xe::Event &event, xe::BaseECSComponent **components) override {
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
		transform.setTranslation(transform.getTranslation() + (dir * amt));
	}

private:
	bool mouseLocked;
};


#endif //X808_DUMMYPLAYERCONTROLSYSTEM_HPP
