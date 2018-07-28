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
		explicit DirectionalLight(api::Shader *shader, float intensity, uint color = color::WHITE);

	protected:
		void setUniformsInternal() override;

	protected:
		DirectionalLightStruct directionalLight;
	};

}}


#endif //X808_DIRECTIONALLIGHT_HPP
