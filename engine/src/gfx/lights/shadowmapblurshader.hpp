//
// Created by FLXR on 7/30/2018.
//

#ifndef X808_SHADOWMAPBLURSHADER_HPP
#define X808_SHADOWMAPBLURSHADER_HPP


#include "gfx/forwardrenderershader.hpp"

namespace xe { namespace gfx {

	class XE_API ShadowMapBlurShader : public ForwardRendererShader {
	public:
		explicit ShadowMapBlurShader(api::Shader *shader);

		void setUniforms(const Material *material, const Transform &transform, Camera *camera) override;

	protected:
		void setUniformsInternal() override { }
	};

}}


#endif //X808_SHADOWMAPBLURSHADER_HPP
