//
// Created by FLXR on 3/19/2019.
//

#ifndef X808_SSAO_HPP
#define X808_SSAO_HPP


#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/rendereffect.hpp>
#include <xe/gfx/quad.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

	class XE_API SSAO : public RenderEffect, NonCopyable {
	public:
		explicit SSAO(uint width, uint height);
		~SSAO() override;

		void calculateAO(const Texture *normal, const Texture *position, const Quad *quad);

		inline const Texture *getAO() const { return aoTexture; }

	private:
		FrameBuffer *aoBuffer;
		Texture *aoTexture;
		const Shader *aoShader;
	};

}

#endif //X808_SSAO_HPP
