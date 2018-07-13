//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_AMBIENTLIGHT_HPP
#define X808_AMBIENTLIGHT_HPP


#include "baselight.hpp"

namespace xe { namespace gfx {

	class XE_API AmbientLight : public BaseLight {
	public:
		explicit AmbientLight(api::Shader *shader, const vec3 &ambientIntensity);

		void setUniforms(const Model *model, const Camera *camera) override;

		inline const vec3 &getAmbientIntensity() const { return ambientIntensity; }
		void setAmbientIntensity(const vec3 &value);

	private:
		vec3 ambientIntensity;
	};

}}


#endif //X808_AMBIENTLIGHT_HPP
