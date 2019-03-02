//
// Created by FLXR on 3/2/2019.
//

#ifndef X808_FINALFX_HPP
#define X808_FINALFX_HPP


#include <xe/common.hpp>
#include <xe/gfx/rendereffect.hpp>
#include <xe/gfx/quad.hpp>
#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/shader.hpp>

namespace xe {

	class XE_API FinalFX : public RenderEffect {
	public:
		explicit FinalFX(uint width, uint height, bool fxaa = true);
		~FinalFX() override;

		void useFXAA(bool enabled) const;

		void render(Quad *quad) const;

		inline const FrameBuffer *getFinalFBO() const { return finalFBO; }
		inline const Texture *getFinalTexture() const { return finalTexture; }

	private:
		uint sampler0;

		const Shader *finalShader;
		FrameBuffer *finalFBO;
		Texture *finalTexture;

		mutable bool fxaa;
	};

}


#endif //X808_FINALFX_HPP
