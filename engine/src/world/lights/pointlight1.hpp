//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_POINTLIGHT1_HPP
#define X808_POINTLIGHT1_HPP


#include <array>
#include "light.hpp"

namespace xe {

	class XE_API PointLight1 : public Light {
	public:
		PointLight1(const std::string_view &id, const vec3 &color, float intensity, float falloff,
		            bool shadow, Mesh1 *mesh, const mat4 &transformation);

		mat4 getShadowPerspectiveMatrix() const;
		std::array<mat4, 6> getShadowViewMatrices() const;
		std::array<mat4, 6> getViewRayMatrices() const;

	private:
		static mat4 *rotationMatrices;
	};

}


#endif //X808_POINTLIGHT1_HPP
