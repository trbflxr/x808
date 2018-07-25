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
		explicit DirectionalLight(api::Shader *shader, bool castShadow, const vec3 &direction,
		                          float intensity, uint color = color::WHITE);

		inline const vec3 &getDirection() const { return directionalLight.direction; }
		void setDirection(const vec3 &direction);

	protected:
		void setUniformsInternal() override;

	private:
		DirectionalLightStruct directionalLight;
	};

}}


#endif //X808_DIRECTIONALLIGHT_HPP
