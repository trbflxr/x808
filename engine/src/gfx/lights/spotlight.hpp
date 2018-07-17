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
		explicit SpotLight(api::Shader *shader, const vec3 &position, const vec3 &direction, float cutoff,
		                   const vec3 &attenuation, float intensity, uint color = color::WHITE);

		void setUniforms(const Model *model, const Camera *camera) override;

		inline const vec3 &getDirection() const { return spotLight.direction; }
		void setDirection(const vec3 &direction);

		inline float getCutoff() const { return spotLight.cutoff; }
		void setCutoff(float cutoff);

	protected:
		void setUniformsInternal() override;

	protected:
		SpotLightStruct spotLight;
	};

}}


#endif //X808_SPOTLIGHT_HPP
