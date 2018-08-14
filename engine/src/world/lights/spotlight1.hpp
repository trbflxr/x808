//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_SPOTLIGHT1_HPP
#define X808_SPOTLIGHT1_HPP


#include "light.hpp"

namespace xe {

	class XE_API SpotLight1 : public Light {
	public:
		float spotAngle;
		float spotBlur;

	public:
		explicit SpotLight1(const std::string_view &id, const vec3 &color, float intensity, float falloff,
		                   float spotAngle, float spotBlur, bool shadow, Mesh1 *mesh, const mat4 &transformation);

		mat4 getShadowViewMatrix() const;
		mat4 getShadowPerspectiveMatrix() const;
		mat4 getViewRayMatrix() const;
	};

}


#endif //X808_SPOTLIGHT1_HPP
