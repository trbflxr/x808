//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_DIRECTIONALLIGHT_HPP
#define X808_DIRECTIONALLIGHT_HPP


#include "baselight.hpp"

namespace xe { namespace gfx {

	class XE_API DirectionalLight : public BaseLight {
	protected:
		struct DirectionalLightStruct {
			BaseLightStruct base;
			vec3 direction;
		};

	public:
		explicit DirectionalLight(api::Shader *shader, float intensity,
		                          uint color = color::WHITE,
		                          uint shadowMapSizePower2 = 0,
		                          float shadowArea = 80.0f,
		                          float shadowSoftness = 1.0f,
		                          float lightBleedReduction = 0.2f,
		                          float minVariance = 0.00002f);

		void updateLightCamera(Camera *lightCamera, Camera *mainCamera) override;

	protected:
		void setUniformsInternal() override;

	private:
		DirectionalLightStruct directionalLight;

		float halfShadowArea;
	};

}}


#endif //X808_DIRECTIONALLIGHT_HPP
