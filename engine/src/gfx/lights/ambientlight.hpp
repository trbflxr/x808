//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_AMBIENTLIGHT_HPP
#define X808_AMBIENTLIGHT_HPP


#include "baselight.hpp"

namespace xe { namespace gfx {

	class XE_API AmbientLight : public BaseLight {
	public:
		explicit AmbientLight(api::Shader *shader, float intensity, uint color = color::WHITE);

		void setUniforms(const Model *model, const Camera *camera) override;

	protected:
		void setUniformsInternal() override;
	};

}}


#endif //X808_AMBIENTLIGHT_HPP
