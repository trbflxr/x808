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
#include <xe/utils/string.hpp>
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
		void render3D(uint depth) const;

		void renderTexture(Texture *texture, uint size, int32 pos, int32 layer = 0, int32 channel = -1);

	private:
		void renderTexture(Shader* shader, Texture *texture, int32 data, const char *uniform, bool fullQuad);

	private:
		VertexArray *vao;
		IndexBuffer *ibo;

		Shader *renderTexture1D;
		Shader *renderTexture2D;
		Shader *renderTexture2DArray;
		Shader *renderTexture3D;
		Shader *renderTextureCube;
		Shader *renderTextureCubeArray;
	};

}}


#endif //X808_QUAD_HPP
