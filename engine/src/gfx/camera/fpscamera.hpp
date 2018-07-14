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

		void update() override;

		inline float getPitch() const { return pitch; }
		inline void setPitch(float pitch) { FPSCamera::pitch = pitch; }
		inline float getYaw() const { return yaw; }
		inline void setYaw(float yaw) { FPSCamera::yaw = yaw; }

		quat getOrientation() const;
		vec3 getForwardDirection(const quat &orientation) const;
		vec3 getUpDirection(const quat &orientation) const;
		vec3 getRightDirection(const quat &orientation) const;

	private:
		float pitch;
		float yaw;
	};

}}


#endif //X808_FPSCAMERA_HPP
