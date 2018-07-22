//
// Created by FLXR on 7/16/2018.
//

#include "pointlight.hpp"

namespace xe { namespace gfx {

	//todo: move to constructor?
	static constexpr short COLOR_DEPTH = 256;

	PointLight::PointLight(api::Shader *shader, const vec3 &position,
	                       const vec3 &attenuation, float intensity, uint color) :
			BaseLight(shader, intensity, color) {

		pointLight.base = baseLight;
		pointLight.attenuation = attenuation;
		pointLight.position = position;
		pointLight.attenuation = attenuation;
		pointLight.range = calcRange(attenuation);

		setUniformsInternal();
	}

	void PointLight::setUniforms(const Model *model, const Camera *camera) {
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

	void PointLight::setUniformsInternal() {
		setUniform("sys_ActivePointLight", &pointLight, sizeof(PointLightStruct), api::ShaderType::FRAG);
	}

	void PointLight::setAttenuation(const vec3 &attenuation) {
		pointLight.attenuation = attenuation;
		pointLight.range = calcRange(attenuation);

		setUniformsInternal();
	}

	void PointLight::setPosition(const vec3 &position) {
		pointLight.position = position;

		setUniformsInternal();
	}

	float PointLight::calcRange(const vec3 &attenuation) {
		const float x = attenuation.z;
		const float y = attenuation.y;
		const float z = attenuation.x - COLOR_DEPTH * baseLight.intensity *
		                                __max(__max(baseLight.color.x, baseLight.color.y), baseLight.color.z);

		return (-y + sqrtf(y * y - 4 * x * z)) / (2 * x);
	}

}}