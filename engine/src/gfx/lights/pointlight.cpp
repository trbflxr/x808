//
// Created by FLXR on 8/13/2018.
//

#include <xe/gfx/lights/pointlight.hpp>

namespace xe {

	PointLight::PointLight(const string &id, const vec3 &color, float intensity, float falloff,
	                       bool shadow, Mesh *mesh, const mat4 &transformation) :
			Light(id, Type::Point, color, intensity, falloff, shadow, transformation, mesh) {

		PointLight::mesh = mesh;

		const float pointRadius = falloff;
		const vec3 scaler(pointRadius, pointRadius, pointRadius);

		boundsMatrix = mat4::scale(scaler);
	}

}