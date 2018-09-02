//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_POINTLIGHT1_HPP
#define X808_POINTLIGHT1_HPP


#include <xe/gfx/lights/light.hpp>

namespace xe {

	class XE_API PointLight : public Light {
	public:
		explicit PointLight(const string &id, const vec3 &color, float intensity, float falloff,
		           bool shadow, Mesh *mesh, const mat4 &transformation);
		~PointLight() override = default;
	};

}


#endif //X808_POINTLIGHT1_HPP
