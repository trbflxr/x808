//
// Created by FLXR on 7/26/2018.
//

#ifndef X808_SHADOWMAPSHADER_HPP
#define X808_SHADOWMAPSHADER_HPP


#include "gfx/forwardrenderershader.hpp"

namespace xe { namespace gfx {

	class XE_API ShadowMapShader : public ForwardRendererShader {
	public:
		explicit ShadowMapShader(api::Shader *shader);

		void setUniforms(const Material *material, const Transform &transform, Camera *camera) override;

	protected:
		void setUniformsInternal() override { }
	};

}}


#endif //X808_SHADOWMAPSHADER_HPP
