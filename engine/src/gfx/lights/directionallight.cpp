//
// Created by FLXR on 7/13/2018.
//

#include "directionallight.hpp"

namespace xe { namespace gfx {

	DirectionalLight::DirectionalLight(api::Shader *shader, float intensity, uint color) :
			BaseLight(shader, intensity, color) {

		setUniformsInternal();

//		setShadowInfo(new ShadowInfo(mat4::ortho(-40, 40, -40, 40, -40, 40), 10, true, 0.0f));
		setShadowInfo(new ShadowInfo(mat4::ortho(-40, 40, -40, 40, -40, 40), 10, false));
	}

	void DirectionalLight::setUniformsInternal() {
		directionalLight.base = light;
		directionalLight.direction = quat::rotate(transform.getRotation(), -vec3::ZAXIS);

		setUniform("sys_ActiveDirectionalLight", &directionalLight,
		           sizeof(DirectionalLightStruct), api::Shader::FRAG);
	}

}}