//
// Created by FLXR on 7/13/2018.
//

#include "directionallight.hpp"

namespace xe {

	DirectionalLight::DirectionalLight(api::Shader *shader, float intensity, uint color,
	                                   uint shadowMapSizePower2, float shadowArea, float shadowSoftness,
	                                   float lightBleedReduction, float minVariance) :
			BaseLight(shader, intensity, color),
			halfShadowArea(shadowArea / 2.0f) {

		setUniformsInternal();

		if (shadowMapSizePower2) {
			setShadowInfo(new ShadowInfo(mat4::ortho(-halfShadowArea, halfShadowArea, -halfShadowArea,
			                                         halfShadowArea, -halfShadowArea, halfShadowArea),
			                             shadowMapSizePower2, false, shadowSoftness,
			                             lightBleedReduction, minVariance));
		}
	}

	void DirectionalLight::setUniformsInternal() {
		directionalLight.base = light;
		directionalLight.direction = quat::rotate(transform.getRotation(), -vec3::ZAXIS);

		setUniform("activeDirectionalLight", &directionalLight, sizeof(DirectionalLightStruct));
	}

	void DirectionalLight::updateLightCamera(Camera *lightCamera, Camera *mainCamera) {
		lightCamera->unhookEntity();

		vec3 pos = mainCamera->transform.getTranslation() +
		           mainCamera->transform.getRotation().getForward() * halfShadowArea;

		quat rot = transform.getRotation();

		float worldTexelSize = (halfShadowArea * 2.0f) / (1 << shadowInfo->shadowMapSizePower2);

		vec3 lightSpaceCameraPos = pos.rotate(quat::conjugate(rot));
		lightSpaceCameraPos.x = worldTexelSize * floorf(lightSpaceCameraPos.x / worldTexelSize);
		lightSpaceCameraPos.y = worldTexelSize * floorf(lightSpaceCameraPos.y / worldTexelSize);

		pos = lightSpaceCameraPos.rotate(rot);

		lightCamera->transform.setTranslation(pos);
		lightCamera->transform.setRotation(rot);
	}

}