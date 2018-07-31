//
// Created by FLXR on 7/16/2018.
//

#ifndef X808_SPOTLIGHT_HPP
#define X808_SPOTLIGHT_HPP


#include "pointlight.hpp"

namespace xe { namespace gfx {

	class XE_API SpotLight : public PointLight {
	protected:
		struct SpotLightStruct {
			vec3 direction;
			float cutoff;
		};

	public:
		explicit SpotLight(api::Shader *shader, const Attenuation &attenuation, float intensity,
		                   uint color = color::WHITE,
		                   float fovDeg = 170.0f,
		                   uint shadowMapSizePower2 = 0,
		                   float shadowSoftness = 1.0f,
		                   float lightBleedReduction = 0.2f,
		                   float minVariance = 0.00002f);

		inline float getFov() const { return acosf(spotLight.cutoff) * 2.0f; }
		void setFov(float fovDeg);

	protected:
		void setUniformsInternal() override;

	protected:
		SpotLightStruct spotLight;
	};

}}


#endif //X808_SPOTLIGHT_HPP
