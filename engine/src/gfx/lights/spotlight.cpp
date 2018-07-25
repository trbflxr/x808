//
// Created by FLXR on 7/16/2018.
//

#include "spotlight.hpp"

namespace xe { namespace gfx {

	SpotLight::SpotLight(api::Shader *shader, bool castShadow, const vec3 &position, const vec3 &direction,
	                     float cutoff, const vec3 &attenuation, float intensity, uint color) :
			PointLight(shader, castShadow, position, attenuation, intensity, color) {

		spotLight.direction = direction;
		spotLight.cutoff = cutoff;

		setUniformsInternal();
	}

	void SpotLight::setUniformsInternal() {
		PointLight::setUniformsInternal();

		setUniform("sys_ActiveSpotLight", &spotLight, sizeof(SpotLightStruct), api::Shader::FRAG);
	}

	void SpotLight::setDirection(const vec3 &direction) {
		spotLight.direction = direction;

		setUniformsInternal();
	}

	void SpotLight::setCutoff(float cutoff) {
		spotLight.cutoff = cutoff;

		setUniformsInternal();
	}


}}