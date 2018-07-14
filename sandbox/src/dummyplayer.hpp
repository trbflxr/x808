//
// Created by FLXR on 7/14/2018.
//

#ifndef X808_DUMMYPLAYER_HPP
#define X808_DUMMYPLAYER_HPP


#include <gfx/camera/fpscamera.hpp>

class DummyPlayer {
public:
	explicit DummyPlayer(xe::gfx::FPSCamera *camera);
	~DummyPlayer();

	void update(float delta);

	inline const xe::gfx::FPSCamera *getCamera() const { return camera; }

private:
	xe::gfx::FPSCamera *camera;

	xe::vec3 position;
	xe::vec3 rotation;

	bool mouseWasGrabbed;
	float mouseSensitivity;
	float speed;
	float sprintSpeed;
};


#endif //X808_DUMMYPLAYER_HPP
