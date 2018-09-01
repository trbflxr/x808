//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_SPOTLIGHT1_HPP
#define X808_SPOTLIGHT1_HPP


#include <xe/world/lights/light.hpp>

namespace xe {

	class XE_API SpotLight : public Light {
	public:
		float spotAngle;
		float spotBlur;

	public:
		explicit SpotLight(const string &id, const vec3 &color, float intensity, float falloff,
		                   float spotAngle, float spotBlur, bool shadow, Mesh *mesh, const mat4 &transformation);
		~SpotLight() override = default;
	};

}


#endif //X808_SPOTLIGHT1_HPP
