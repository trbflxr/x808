//
// Created by FLXR on 6/30/2018.
//

#ifndef X808_ORTHOGRAPHICCAMERA_HPP
#define X808_ORTHOGRAPHICCAMERA_HPP


#include "camera.hpp"

namespace xe { namespace gfx {

	class OrthographicCamera : public Camera {
	public:
		explicit OrthographicCamera(const mat4 &projection) : Camera(projection) { }

		void update() override {
			viewMatrix = math::translate(position);
		}
	};

}}


#endif //X808_ORTHOGRAPHICCAMERA_HPP
