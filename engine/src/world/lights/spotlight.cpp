//
// Created by FLXR on 8/13/2018.
//

#include <xe/world/lights/spotlight.hpp>

namespace xe {

	SpotLight::SpotLight(const string &id, const vec3 &color, float intensity, float falloff,
	                     float spotAngle, float spotBlur, bool shadow, Mesh *mesh, const mat4 &transformation) :
			Light(id, Type::Spot, color, intensity, falloff, shadow, transformation, mesh),
			spotAngle(spotAngle / 2.0f),
			spotBlur(spotBlur) {

		const float spotDepth = falloff / 4.0f;
		const float spotRadius = spotDepth * tanf(SpotLight::spotAngle);

		const vec3 scaler(spotRadius, spotRadius, spotDepth);
		const vec3 shifter(0.0f, 0.0f, -falloff);

		boundsMatrix = mat4::translation(shifter) * mat4::scale(scaler);

		perspective = mat4::perspective(to_deg(spotAngle * 2.0f), 1.0f, 0.01f, 100.0f);
	}

}