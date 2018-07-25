//
// Created by FLXR on 7/13/2018.
//

#include "baselight.hpp"
#include "utils/log.hpp"

namespace xe { namespace gfx {

	BaseLight::BaseLight(api::Shader *shader, bool castShadow, float intensity, uint color) :
			ForwardRendererShader(shader),
			enabled(true),
			castShadow(castShadow) {

		baseLight.color = color::decode(color);
		baseLight.intensity = intensity;
	}

	void BaseLight::setColor(uint color) {
		baseLight.color = color::decode(color);
		setUniformsInternal();
	}

	void BaseLight::setIntensity(float intensity) {
		baseLight.intensity = intensity;
		setUniformsInternal();
	}

}}