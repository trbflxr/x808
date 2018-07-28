//
// Created by FLXR on 7/13/2018.
//

#include "ambientlight.hpp"

namespace xe { namespace gfx {

	AmbientLight::AmbientLight(api::Shader *shader, float intensity, uint color) :
			BaseLight(shader, intensity, color) {

		setUniformsInternal();
	}

	void AmbientLight::setUniformsInternal() {
		setUniform("sys_Intensity", &light.intensity, sizeof(float), api::Shader::FRAG);
		setUniform("sys_Color", &light.color, sizeof(vec4), api::Shader::FRAG);
	}

}}