//
// Created by FLXR on 7/14/2018.
//

#ifndef X808_DUMMYPLAYER_HPP
#define X808_DUMMYPLAYER_HPP


#include <gfx/camera.hpp>
#include <window/event.hpp>
#include <gameobject.hpp>

class DummyPlayer : public xe::GameObject {
public:
	explicit DummyPlayer(xe::gfx::Camera *camera);
	~DummyPlayer();

	void update(float delta);

	void input(xe::Event &event);

	inline xe::gfx::Camera *getCamera() const { return camera; }

private:
	void move(const xe::vec3 &dir, float amt);

private:
	xe::gfx::Camera *camera;

	xe::vec3 position;
	xe::vec3 rotation;

	float mouseSensitivity;
	float speed;
	float sprintSpeed;

	bool mouseLocked;
};


#endif //X808_DUMMYPLAYER_HPP
