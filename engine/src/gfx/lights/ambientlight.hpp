//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_AMBIENTLIGHT_HPP
#define X808_AMBIENTLIGHT_HPP


#include "baselight.hpp"

namespace xe {

	class XE_API AmbientLight : public BaseLight {
	public:
		explicit AmbientLight(api::BaseShader *shader, float intensity, uint color = color::WHITE);

		void setUniforms(const Material *material, const Transform &transform, Camera *camera) override;

	protected:
		void setUniformsInternal() override;
	};

}


#endif //X808_AMBIENTLIGHT_HPP
