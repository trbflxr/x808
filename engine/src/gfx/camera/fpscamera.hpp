//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_FPSCAMERA_HPP
#define X808_FPSCAMERA_HPP


#include "camera.hpp"

namespace xe { namespace gfx {

	class XE_API FPSCamera : public Camera {
	public:
		explicit FPSCamera(const mat4 &projection);
		~FPSCamera();

		void focus() override;
		void update() override;

	private:
		quat getOrientation() const;
		vec3 getForwardDirection(const quat &orientation) const;
		vec3 getUpDirection(const quat &orientation) const;
		vec3 getRightDirection(const quat &orientation) const;

	private:
		//temp
		float mouseSensitivity;
		float speed;
		float sprintSpeed;
		float pitch;
		float yaw;
		bool mouseWasGrabbed;
	};

}}


#endif //X808_FPSCAMERA_HPP
