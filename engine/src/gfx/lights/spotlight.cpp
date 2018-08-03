//
// Created by FLXR on 7/16/2018.
//

#include "spotlight.hpp"

namespace xe {

	SpotLight::SpotLight(api::Shader *shader, const PointLight::Attenuation &attenuation, float intensity,
	                     uint color, float fovDeg, uint shadowMapSizePower2, float shadowSoftness,
	                     float lightBleedReduction, float minVariance) :
			PointLight(shader, attenuation, intensity, color) {

		spotLight.cutoff = cosf(to_rad(fovDeg) / 2.0f);

		setUniformsInternal();

		if (shadowMapSizePower2) {
			setShadowInfo(new ShadowInfo(mat4::perspective(fovDeg, 1.0f, 0.1f, pointLight.range),
			                             shadowMapSizePower2, false, shadowSoftness,
			                             lightBleedReduction, minVariance));
		}
	}

	void SpotLight::setUniformsInternal() {
		spotLight.direction = quat::rotate(transform.getRotation(), -vec3::ZAXIS);

		PointLight::setUniformsInternal();

		setUniform("sys_ActiveSpotLight", &spotLight, sizeof(SpotLightStruct), api::Shader::FRAG);
	}

	void SpotLight::setFov(float fovDeg) {
		spotLight.cutoff = cosf(to_rad(fovDeg) / 2.0f);

		setUniformsInternal();
	}

}