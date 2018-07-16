//
// Created by FLXR on 7/16/2018.
//

#ifndef X808_POINTLIGHT_HPP
#define X808_POINTLIGHT_HPP


#include "baselight.hpp"

namespace xe { namespace gfx {

	class PointLight : public BaseLight {
	protected:
		struct PointLightStruct {
			BaseLightStruct base;
			vec3 attenuation;
			vec3 position;
			float range;
		};

	public:
		explicit XE_API PointLight(api::Shader *shader, const vec3 &position, const vec3 &attenuation,
		                    float intensity, uint color = color::WHITE);

		void setUniforms(const Model *model, const Camera *camera) override;

		inline const vec3 &getAttenuation() const { return pointLight.attenuation; }
		void setAttenuation(const vec3 &attenuation);

		inline const vec3 &getPosition() const { return pointLight.position; }
		void setPosition(const vec3 &position);

		inline float getRange() const { return pointLight.range; }

	protected:
		void setUniformsInternal() override;

	private:
		PointLightStruct pointLight;
	};

}}


#endif //X808_POINTLIGHT_HPP
