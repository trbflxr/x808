//
// Created by FLXR on 8/18/2018.
//

#ifndef X808_GBUFFER_HPP
#define X808_GBUFFER_HPP


#include <xe/common.hpp>
#include <xe/gfx/fx/quad.hpp>
#include <xe/gfx/fx/rendereffect.hpp>
#include <xe/gfx/texture.hpp>
#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/scene.hpp>

namespace xe { namespace fx {

	class XE_API GBuffer : public RenderEffect{
	public:
		explicit GBuffer(uint width, uint height);
		~GBuffer() override;

	private:
		bool enableWireframe;

		FrameBuffer* gBuffer;

		Shader *geometryShader;
		Shader *stencilShader;
		Shader *spotShader;
		Shader *pointShader;
		Shader *accumulationShader;

		Texture* depthStencilTexture;
		Texture* diffuseTexture;
		Texture* normalDepthTexture;
		Texture* specularTexture;
		Texture* velocityTexture;
		Texture* lightDiffuseTexture;
		Texture* lightSpecularTexture;
	};


}}


#endif //X808_GBUFFER_HPP
