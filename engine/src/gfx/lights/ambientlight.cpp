//
// Created by FLXR on 7/13/2018.
//

#include "ambientlight.hpp"

namespace xe { namespace gfx {

	AmbientLight::AmbientLight(api::Shader *shader, float intensity, uint color) :
			BaseLight(shader, intensity, color) {

		setUniformsInternal();
	}

	void AmbientLight::setUniforms(const Material *material, const Transform &transform, Camera *camera) {
		if (AmbientLight::transform.isDirty()) {
			setUniformsInternal();
			AmbientLight::transform.setDirty(false);
		}

		mat4 world = transform.toMatrix();
		mat4 mvp = camera->getViewProjection() * world;
		vec3 camPos = camera->transform.getTranslation();

		setUniform("sys_MVP", &mvp.elements, sizeof(mat4), api::Shader::VERT);
		setUniform("sys_Model", &world.elements, sizeof(mat4), api::Shader::VERT);
		setUniform("sys_EyePos", &camPos, sizeof(vec3), api::Shader::FRAG);

		float dispScale = material->getDispMapScale();
		float dispBias = material->getDispMapBias();
		setUniform("sys_DispMapScale", &dispScale, sizeof(float), api::Shader::FRAG);
		setUniform("sys_DispMapBias", &dispBias, sizeof(float), api::Shader::FRAG);

		setUserUniforms();

		bindSamplers(material);
	}

	void AmbientLight::setUniformsInternal() {
		setUniform("sys_Intensity", &light.intensity, sizeof(float), api::Shader::FRAG);
		setUniform("sys_Color", &light.color, sizeof(vec4), api::Shader::FRAG);
	}

}}