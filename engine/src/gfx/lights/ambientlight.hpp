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
	};

}}


#endif //X808_AMBIENTLIGHT_HPP
