//
// Created by FLXR on 7/13/2018.
//

#include "ambientlight.hpp"

namespace xe { namespace gfx {

	AmbientLight::AmbientLight(api::Shader *shader, float intensity, uint color) :
			BaseLight(shader, intensity, color) {

		setUniformsInternal();
	}

	void AmbientLight::setUniforms(const Model *model, const Camera *camera) {
		mat4 mvp = camera->getProjectionMatrix() * camera->getViewMatrix() * model->transform.toMatrix();

		setUniform("sys_MVP", &mvp.elements, sizeof(mat4), api::ShaderType::VERT);
	}

	void AmbientLight::setUniformsInternal() {
		vec4 c = color::decode(color);

		setUniform("sys_Intensity", &intensity, sizeof(float), api::ShaderType::FRAG);
		setUniform("sys_Color", &c, sizeof(vec4), api::ShaderType::FRAG);
	}

}}