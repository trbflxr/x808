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
		mat4 world = model->transform.toMatrix();
		mat4 mvp = camera->getProjectionMatrix() * camera->getViewMatrix() * world;

		setUniform("sys_MVP", &mvp.elements, sizeof(mat4), api::Shader::VERT);
		setUniform("sys_Model", &world.elements, sizeof(mat4), api::Shader::VERT);

		float dispScale = model->material->getDispMapScale();
		float dispBias = model->material->getDispMapBias();
		setUniform("sys_DispMapScale", &dispScale, sizeof(float), api::Shader::FRAG);
		setUniform("sys_DispMapBias", &dispBias, sizeof(float), api::Shader::FRAG);

		setUniform("sys_EyePos", &camera->getPosition(), sizeof(vec3), api::Shader::FRAG);
	}

	void AmbientLight::setUniformsInternal() {
		setUniform("sys_Intensity", &baseLight.intensity, sizeof(float), api::Shader::FRAG);
		setUniform("sys_Color", &baseLight.color, sizeof(vec4), api::Shader::FRAG);
	}

}}