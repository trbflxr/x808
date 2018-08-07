//
// Created by FLXR on 7/13/2018.
//

#include "ambientlight.hpp"

namespace xe {

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

		setUniform("MVP", &mvp.elements, sizeof(mat4));
		setUniform("model", &world.elements, sizeof(mat4));
		setUniform("eyePos", &camPos, sizeof(vec3));

		float dispScale = material->getDispMapScale();
		float dispBias = material->getDispMapBias();
		setUniform("dispMapScale", &dispScale, sizeof(float));
		setUniform("dispMapBias", &dispBias, sizeof(float));

		setUserUniforms();

		bindSamplers(material);
	}

	void AmbientLight::setUniformsInternal() {
		setUniform("intensity", &light.intensity, sizeof(float));
		setUniform("color", &light.color, sizeof(vec4));
	}

}