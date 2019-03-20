//
// Created by FLXR on 3/19/2019.
//

#include <xe/gfx/ssao.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/shadermanager.hpp>

namespace xe {

	SSAO::SSAO(uint width, uint height) :
			RenderEffect(width, height) {

		aoShader = GETSHADER("dSSAO");

		TextureParameters params(TextureTarget::Tex2D);
		params.internalFormat = PixelInternalFormat::R16f;
		params.format = PixelFormat::Red;
		params.pixelType = PixelType::Float;
		params.minFilter = TextureMinFilter::Linear;
		params.magFilter = TextureMagFilter::Linear;
		params.wrap = TextureWrap::Clamp;
		params.mipMapLevels = 0;
		params.anisotropy = 0;

		aoTexture = new Texture("ssao", width, height, 0, params);

		aoBuffer = new FrameBuffer("ssaoBuffer");
		aoBuffer->load({std::make_pair(Attachment::Color0, aoTexture)});
	}

	SSAO::~SSAO() {
		delete aoTexture;
		delete aoBuffer;
	}

	void SSAO::calculateAO(const Texture *normal, const Texture *position, const Quad *quad) {
		aoBuffer->bindDraw(Attachment::Color0);
		Renderer::setViewport(0, 0, width, height);
		Renderer::clear(RendererBufferColor);

		aoShader->bind();

		const uint n = aoShader->getSampler("sampler0");
		const uint p = aoShader->getSampler("sampler1");

		normal->bind(n);
		position->bind(p);

		quad->render();

		normal->unbind(n);
		position->unbind(p);

		aoShader->unbind();

		aoBuffer->unbind();
	}

}