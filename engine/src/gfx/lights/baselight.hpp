//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_BASELIGHT_HPP
#define X808_BASELIGHT_HPP


#include "gfx/forwardrenderershader.hpp"
#include "gfx/color.hpp"

namespace xe { namespace gfx {

	class XE_API BaseLight : public ForwardRendererShader {
	protected:
		struct BaseLightStruct {
			vec4 color;
			float intensity;
		};

	public:
		inline bool isEnabled() const { return enabled; }
		inline void setEnabled(bool enable) { BaseLight::enabled = enable; }

		inline bool isCastShadow() const { return castShadow; }
		inline void setCastShadow(bool enable) { BaseLight::castShadow = enable; }

		inline vec4 getColor() const { return baseLight.color; }
		void setColor(uint color);

		inline float getIntensity() const { return baseLight.intensity; }
		void setIntensity(float intensity);

	protected:
		explicit BaseLight(api::Shader *shader, bool castShadow, float intensity, uint color = color::WHITE);

	protected:
		bool castShadow;
		bool enabled;
		BaseLightStruct baseLight;
	};

}}


#endif //X808_BASELIGHT_HPP
