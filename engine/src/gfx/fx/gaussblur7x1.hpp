//
// Created by FLXR on 8/11/2018.
//

#ifndef X808_GAUSSBLUR7X1_HPP
#define X808_GAUSSBLUR7X1_HPP


#include "common.hpp"
#include "rendereffect.hpp"
#include "quad.hpp"
#include "gfx/api/framebuffer_old.hpp"
#include "gfx/shader.hpp"

namespace xe { namespace fx {

	class XE_API GaussBlur7x1 : public RenderEffect {
	public:
		explicit GaussBlur7x1(uint width, uint height);
		~GaussBlur7x1();

		void render(Quad *quad, api::Texture *srcTexture, api::FrameBufferOld *dest, const vec2 &scale);

	private:
		Shader *shader;
	};

}}

#endif //X808_GAUSSBLUR7X1_HPP
