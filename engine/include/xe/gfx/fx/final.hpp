//
// Created by FLXR on 8/8/2018.
//

#ifndef X808_FINAL_HPP
#define X808_FINAL_HPP


#include <xe/common.hpp>
#include <xe/gfx/fx/rendereffect.hpp>
#include <xe/gfx/fx/quad.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/framebuffer.hpp>

namespace xe { namespace fx {

	class XE_API Final : public RenderEffect {
	public:
		explicit Final(uint width, uint height);
		~Final();

		void render(Quad *quad, Texture *srcTexture, bool useFXAA = false) const;

	private:
		Shader *finalShader;
	};

}}


#endif //X808_FINAL_HPP
