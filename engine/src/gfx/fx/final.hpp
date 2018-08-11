//
// Created by FLXR on 8/8/2018.
//

#ifndef X808_FINAL_HPP
#define X808_FINAL_HPP


#include "common.hpp"
#include "rendereffect.hpp"
#include "quad.hpp"
#include "gfx/shader.hpp"
#include "gfx/api/framebuffer.hpp"

namespace xe { namespace fx {

	class XE_API Final : public RenderEffect {
	public:
		explicit Final(uint width, uint height);
		~Final();

		void render(Quad *quad, api::Texture *srcTexture, bool useFXAA = false) const;

	private:
		Shader *finalShader;
	};

}}


#endif //X808_FINAL_HPP
