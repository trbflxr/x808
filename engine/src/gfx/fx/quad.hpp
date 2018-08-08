//
// Created by FLXR on 8/7/2018.
//

#ifndef X808_QUAD_HPP
#define X808_QUAD_HPP


#include "common.hpp"
#include "rendereffect.hpp"
#include "gfx/api/shader.hpp"
#include "gfx/api/vertexarray.hpp"

namespace xe { namespace fx {

	class XE_API Quad : public RenderEffect {
	public:
		explicit Quad(uint width, uint height);
		~Quad();

		void load() override;
		void unload() override;
		void reload() override;

		void render();
		void renderBlendBlend();
		void renderFullQuad();
		void renderFullQuadBlend();
		void render3D(uint depth);

		void renderToTexture(api::Texture *texture, float scale, uint pos, uint layer = 0, int32 channel = -1);

	protected:
		void loadPrograms() override;
		void loadBuffers() override;

	private:
		api::VertexArray *vao;

		api::Shader *renderTexture1D;
		api::Shader *renderTexture2D;
		api::Shader *renderTexture2DArray;
		api::Shader *renderTexture3D;
		api::Shader *renderTextureCube;
		api::Shader *renderTextureCubeArray;
	};

}}


#endif //X808_QUAD_HPP
