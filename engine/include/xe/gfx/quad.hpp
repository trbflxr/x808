//
// Created by FLXR on 8/7/2018.
//

#ifndef X808_QUAD_HPP
#define X808_QUAD_HPP


#include <xe/common.hpp>
#include <xe/gfx/rendereffect.hpp>
#include <xe/gfx/vertexarray.hpp>
#include <xe/gfx/indexbuffer.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/texture.hpp>

namespace xe {

	class XE_API Quad : public RenderEffect {
	public:
		explicit Quad(uint width, uint height);
		~Quad() override;

		void render() const;
		void renderBlend() const;
		void renderFullQuad() const;
		void renderFullQuadBlend() const;

		void renderTexture(const Texture *tex, float size = 1.0f, int32 pos = 0, int32 data = 0);

	private:
		void renderTexture(const Shader *shader, const Texture *tex, int32 data, bool fullQuad);

	private:
		VertexArray *vao;
		IndexBuffer *ibo;

		const Shader *renderTexture2D;
		const Shader *renderTexture2DArray;
	};

}


#endif //X808_QUAD_HPP
