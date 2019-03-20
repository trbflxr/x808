//
// Created by FLXR on 3/20/2019.
//

#ifndef X808_HBAO_HPP
#define X808_HBAO_HPP


#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/rendereffect.hpp>
#include <xe/gfx/quad.hpp>
#include <xe/gfx/camera.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

	class XE_API HBAO : public RenderEffect, NonCopyable {
	public:
		explicit HBAO(uint width, uint height);
		~HBAO() override;

		void calculateAO(const Texture *normal, const Texture *depth, const Camera *camera, const Quad *quad);

		inline const Texture *getAO() const { return aoTexture; }

	private:
		FrameBuffer *aoBuffer;
		Texture *aoTexture;
		const Shader *aoShader;
	};

}


#endif //X808_HBAO_HPP
