//
// Created by FLXR on 8/7/2018.
//

#ifndef X808_QUAD_HPP
#define X808_QUAD_HPP


#include <xe/common.hpp>
#include <xe/gfx/fx/rendereffect.hpp>
#include <xe/gfx/vertexarray.hpp>
#include <xe/gfx/indexbuffer.hpp>
#include <xe/gfx/enums.hpp>
#include <xe/string.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/texture.hpp>

namespace xe { namespace fx {

	class XE_API Quad : public RenderEffect {
	public:
		explicit Quad(uint width, uint height);
		~Quad() override;

		void render() const;
		void renderBlend() const;
		void renderFullQuad() const;
		void renderFullQuadBlend() const;

		void renderTexture(const Texture *texture, float size = 1.0f, int32 pos = 0, int32 channel = -1);

	private:
		void renderTexture(const Shader *shader, const Texture *texture, int32 channel, bool fullQuad);

	private:
		VertexArray *vao;
		IndexBuffer *ibo;

		const Shader *renderTexture2D;
	};

}}


#endif //X808_QUAD_HPP
