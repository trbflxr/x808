//
// Created by FLXR on 3/20/2019.
//

#include <xe/gfx/fx/blur.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/shadermanager.hpp>

namespace xe { namespace fx {

	Blur::Blur(uint width, uint height) :
			RenderEffect(width, height),
			sampler0(0) {

		blurShader = GETSHADER("dBlur");
		sampler0 = blurShader->getSampler("sampler0");

		const vec2 targetSize = vec2(width, height);
		blurShader->setUniform("targetSize", &targetSize, sizeof(vec2));

		TextureParameters params(TextureTarget::Tex2D);
		params.internalFormat = PixelInternalFormat::Rgba16f;
		params.format = PixelFormat::Rgba;
		params.pixelType = PixelType::Float;
		params.minFilter = TextureMinFilter::Linear;
		params.magFilter = TextureMagFilter::Linear;
		params.wrap = TextureWrap::Clamp;
		params.mipMapLevels = 0;
		params.anisotropy = 0;

		blurTextureVert = new Texture("blurVert", width, height, 0, params);
		blurTextureHor = new Texture("blurHor", width, height, 0, params);

		blurBuffer = new FrameBuffer("blurBuffer");
		blurBuffer->load({std::make_pair(Attachment::Color0, blurTextureVert),
		                  std::make_pair(Attachment::Color1, blurTextureHor)});
	}

	Blur::~Blur() {
		delete blurTextureVert;
		delete blurTextureHor;
		delete blurBuffer;
	}

	void Blur::blur(const Texture *texture, const Quad *quad) {
		static constexpr int32 vert = 0;
		static constexpr int32 hor = 0;

		blurBuffer->bindDraw(Attachment::Color0);
		Renderer::setViewport(0, 0, width, height);
		Renderer::clear(RendererBufferColor);

		blurShader->bind();

		//vert pass
		texture->bind(sampler0);

		blurShader->setUniform("vertPass", &vert, sizeof(int32));
		blurShader->updateUniforms();

		quad->render();

		texture->unbind(sampler0);

		//hor pass
		blurBuffer->bindDrawAttachment(Attachment::Color1);
		Renderer::clear(RendererBufferColor);

		blurTextureVert->bind(sampler0);

		blurShader->setUniform("vertPass", &hor, sizeof(int32));
		blurShader->updateUniforms();

		quad->render();

		blurTextureVert->unbind(sampler0);

		blurShader->unbind();

		blurBuffer->unbind();
	}

}}
