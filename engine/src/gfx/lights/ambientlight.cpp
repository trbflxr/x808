//
// Created by FLXR on 7/13/2018.
//

#include "ambientlight.hpp"

namespace xe { namespace gfx {

	AmbientLight::AmbientLight(api::Shader *shader, const vec3 &ambientIntensity) :
			BaseLight(shader),
			ambientIntensity(ambientIntensity) {

		setUniform("sys_AmbientIntensity", &ambientIntensity, sizeof(vec3), api::ShaderType::FRAG);
	}

	void AmbientLight::setUniforms(const Model *model, const Camera *camera) {
		mat4 mvp = camera->getProjectionMatrix() * camera->getViewMatrix() * model->transform.toMatrix();

		setUniform("sys_MVP", &mvp.elements, sizeof(mat4), api::ShaderType::VERT);
	}

	void AmbientLight::setAmbientIntensity(const vec3 &value) {
		ambientIntensity = value;
		setUniform("sys_AmbientIntensity", &ambientIntensity, sizeof(vec3), api::ShaderType::FRAG);
	}

}}