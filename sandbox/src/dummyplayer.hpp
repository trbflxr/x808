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
      window(xe::Application::get().getWindow()),
      camera(camera),
      mouseSensitivity(sensitivity),
      speed(speed / xe::Config::get().tickRate),
      sprintSpeed(DummyPlayer::speed * sprint) {

    windowSize = window.getSize();
    windowCenter = windowSize / 2.0f;
    lastMousePosition = windowCenter;
  }

  void update(float delta) {
    if (mouseLocked) {
      window.setMouseCursorGrabbed(true);
      window.setMouseCursorVisible(false);
    } else {
      window.setMouseCursorGrabbed(false);
      window.setMouseCursorVisible(true);
    }

    if (window.isMouseCursorGrabbed()) {
      xe::vec2 mouseChange = xe::Mouse::getPosition(window) - lastMousePosition;

      //rotate
      camera->rotate(xe::vec3::UnitYN(), mouseChange.x * mouseSensitivity);
      camera->rotate(camera->getRotation().getRight(), mouseChange.y * mouseSensitivity);

      xe::Mouse::setPosition(windowCenter, window);
      lastMousePosition = xe::Mouse::getPosition(window);

      //move
      float speed = xe::Keyboard::isKeyPressed(xe::Keyboard::LControl) ? sprintSpeed : DummyPlayer::speed;
      if (xe::Keyboard::isKeyPressed(xe::Keyboard::W)) {
        move(camera->getRotation().getForward(), speed * delta);
      }
      if (xe::Keyboard::isKeyPressed(xe::Keyboard::S)) {
        move(camera->getRotation().getBackward(), speed * delta);
      }

      if (xe::Keyboard::isKeyPressed(xe::Keyboard::A)) {
        move(camera->getRotation().getLeft(), speed * delta);
      }
      if (xe::Keyboard::isKeyPressed(xe::Keyboard::D)) {
        move(camera->getRotation().getRight(), speed * delta);
      }

      if (xe::Keyboard::isKeyPressed(xe::Keyboard::Space)) {
        move(xe::vec3::UnitY(), speed * delta);
      }
      if (xe::Keyboard::isKeyPressed(xe::Keyboard::LShift)) {
        move(xe::vec3::UnitYN(), speed * delta);
      }
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
        if (mouseLocked) {
          xe::Mouse::setPosition(windowCenter, window);
        }
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
  void move(const xe::vec3 &dir, float amt) {
    camera->setPosition(camera->getPosition() + (dir * amt));
  }

private:
  bool mouseLocked;
  xe::Window &window;
  xe::vec2 windowSize;
  xe::vec2 windowCenter;
  xe::vec2 lastMousePosition;

  xe::Camera *camera;

  float mouseSensitivity;
  float speed;
  float sprintSpeed;
};


#endif //X808_DUMMYPLAYER_HPP