//
// Created by FLXR on 7/16/2018.
//

#ifndef X808_POINTLIGHT_HPP
#define X808_POINTLIGHT_HPP


#include "baselight.hpp"

namespace xe { namespace gfx {

	class XE_API PointLight : public BaseLight {
	protected:
		struct PointLightStruct {
			BaseLightStruct base;
			vec3 attenuation;
			vec3 position;
			float range;
		};

	public:
		explicit PointLight(api::Shader *shader, bool castShadow, const vec3 &position, const vec3 &attenuation,
		                    float intensity, uint color = color::WHITE);

		inline const vec3 &getAttenuation() const { return pointLight.attenuation; }
		void setAttenuation(const vec3 &attenuation);

		inline const vec3 &getPosition() const { return pointLight.position; }
		void setPosition(const vec3 &position);

		inline float getRange() const { return pointLight.range; }

	protected:
		void setUniformsInternal() override;

	private:
		float calcRange(const vec3 &attenuation);

	protected:
		PointLightStruct pointLight;
	};

}}


#endif //X808_POINTLIGHT_HPP
