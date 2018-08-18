//
// Created by FLXR on 8/8/2018.
//

#ifndef X808_FINAL_HPP
#define X808_FINAL_HPP


#include <xe/common.hpp>
#include <xe/gfx/fx/rendereffect.hpp>
#include <xe/gfx/fx/quad.hpp>
#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/shader.hpp>

namespace xe { namespace fx {

	class XE_API Final : public RenderEffect {
	public:
		explicit Final(uint width, uint height);
		~Final() override;

		void useFXAA(bool enabled);

		void render(Quad *quad) const;

		inline const FrameBuffer *getFinalFBO() const { return finalFBO; }
		inline const Texture *getFinalTexture() const { return finalTexture; }

	private:
		Shader *finalShader;
		FrameBuffer *finalFBO;
		Texture *finalTexture;

		bool useFXAA_;
	};

}}


#endif //X808_FINAL_HPP
