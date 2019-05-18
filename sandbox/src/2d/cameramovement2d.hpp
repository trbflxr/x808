//
// Created by FLXR on 5/18/2019.
//

#ifndef X808_CAMERAMOVEMENT2D_HPP
#define X808_CAMERAMOVEMENT2D_HPP


#include <xe/gfx/camera.hpp>
#include <xe/window/keyboard.hpp>

class CameraMovement2D {
public:
  explicit CameraMovement2D(xe::Camera *camera, float speed) :
      camera(camera),
      speed(speed) { }

  void update(float delta) {
    xe::vec3 camPos = camera->getPosition();

    if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::D)) {
      camPos.x += speed * delta;
    }
    if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::A)) {
      camPos.x -= speed * delta;
    }
    if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::W)) {
      camPos.y += speed * delta;
    }
    if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::S)) {
      camPos.y -= speed * delta;
    }
    camera->setPosition(camPos);
  }

private:
  xe::Camera *camera;
  float speed;
};


#endif //X808_CAMERAMOVEMENT2D_HPP
