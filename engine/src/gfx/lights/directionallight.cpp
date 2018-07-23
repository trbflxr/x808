//
// Created by FLXR on 7/13/2018.
//

#include "directionallight.hpp"

namespace xe { namespace gfx {

	DirectionalLight::DirectionalLight(api::Shader *shader, const vec3 &direction, float intensity, uint color) :
			BaseLight(shader, intensity, color) {

		directionalLight.base = baseLight;
		directionalLight.direction = vec3::normalize(direction);

		setUniformsInternal();
	}

	void DirectionalLight::setUniformsInternal() {
		setUniform("sys_ActiveDirectionalLight", &directionalLight,
		           sizeof(DirectionalLightStruct), api::ShaderType::FRAG);
	}

	void DirectionalLight::setDirection(const vec3 &direction) {
		directionalLight.direction = vec3::normalize(direction);

		setUniformsInternal();
	}

}}