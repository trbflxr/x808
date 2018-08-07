//
// Created by FLXR on 7/13/2018.
//

#include "baselight.hpp"
#include "utils/log.hpp"

namespace xe {

	BaseLight::BaseLight(api::Shader *shader, float intensity, uint color) :
			ForwardRendererShader(shader),
			enabled(true),
			shadowInfo(nullptr) {

		light.color = color::decode(color);
		light.intensity = intensity;
	}

	BaseLight::~BaseLight() {
		delete shadowInfo;
	}

	void BaseLight::setUniforms(const Material *material, const Transform &transform, Camera *camera) {
		if (BaseLight::transform.isDirty()) {
			setUniformsInternal();
			BaseLight::transform.setDirty(false);
		}

		mat4 world = transform.toMatrix();
		mat4 mvp = camera->getViewProjection() * world;
		vec3 camPos = camera->transform.getTranslation();

		setUniform("MVP", &mvp.elements, sizeof(mat4));
		setUniform("model", &world.elements, sizeof(mat4));
		setUniform("eyePos", &camPos, sizeof(vec3));

		float specularPower = material->getSpecularIntensity();
		float specularIntensity = material->getSpecularPower();
		float dispScale = material->getDispMapScale();
		float dispBias = material->getDispMapBias();
		setUniform("specularIntensity", &specularIntensity, sizeof(float));
		setUniform("specularPower", &specularPower, sizeof(float));
		setUniform("dispMapScale", &dispScale, sizeof(float));
		setUniform("dispMapBias", &dispBias, sizeof(float));

		setUserUniforms();

		bindSamplers(material);
	}

	void BaseLight::setColor(uint color) {
		light.color = color::decode(color);
		setUniformsInternal();
	}

	void BaseLight::setIntensity(float intensity) {
		light.intensity = intensity;
		setUniformsInternal();
	}

	void BaseLight::setShadowInfo(ShadowInfo *shadowInfo) {
		delete BaseLight::shadowInfo;
		BaseLight::shadowInfo = shadowInfo;
		XE_ASSERT(shadowInfo->shadowMapSizePower2 <= 10, "Max shadowMap size: 10");
	}

	void BaseLight::updateLightCamera(Camera *lightCamera, Camera *mainCamera) {
		lightCamera->unhookEntity();
		lightCamera->transform.setRotation(transform.getRotation());
		lightCamera->transform.setTranslation(transform.getTranslation());
	}

}