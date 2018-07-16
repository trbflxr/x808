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

	void DirectionalLight::setUniforms(const Model *model, const Camera *camera) {
		mat4 world = model->transform.toMatrix();
		mat4 mvp = camera->getProjectionMatrix() * camera->getViewMatrix() * world;

		setUniform("sys_MVP", &mvp.elements, sizeof(mat4), api::ShaderType::VERT);
		setUniform("sys_Model", &world.elements, sizeof(mat4), api::ShaderType::VERT);


		float specularPower = model->material->getSpecularIntensity();
		float specularIntensity = model->material->getSpecularPower();
		setUniform("sys_SpecularIntensity", &specularIntensity, sizeof(float), api::ShaderType::FRAG);
		setUniform("sys_SpecularPower", &specularPower, sizeof(float), api::ShaderType::FRAG);
		setUniform("sys_EyePos", &camera->getPosition(), sizeof(vec3), api::ShaderType::FRAG);
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