//
// Created by FLXR on 7/16/2018.
//

#include "pointlight.hpp"

namespace xe {

	static constexpr short COLOR_DEPTH = 256;

	PointLight::PointLight(api::Shader *shader, const Attenuation &attenuation, float intensity, uint color) :
			BaseLight(shader, intensity, color) {

		pointLight.base = light;
		pointLight.attenuation = attenuation;
		pointLight.range = calcRange(attenuation);

		setUniformsInternal();
	}

	void PointLight::setUniformsInternal() {
		pointLight.position = transform.getTranslation();

		setUniform("sys_ActivePointLight", &pointLight, sizeof(PointLightStruct));
	}

	void PointLight::setAttenuation(const Attenuation &attenuation) {
		pointLight.attenuation = attenuation;
		pointLight.range = calcRange(attenuation);

		setUniformsInternal();
	}

	float PointLight::calcRange(const Attenuation &attenuation) {
		const float x = attenuation.exponent;
		const float y = attenuation.linear;
		const float z = attenuation.constant - COLOR_DEPTH * light.intensity *
		                                       __max(__max(light.color.x, light.color.y), light.color.z);

		return (-y + sqrtf(y * y - 4 * x * z)) / (2 * x);
	}

}