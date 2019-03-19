//
// Created by FLXR on 3/19/2019.
//

#include <xe/gfx/ssao.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/shadermanager.hpp>

namespace xe {

	SSAO::SSAO(uint width, uint height) :
			RenderEffect(width, height) {

		shader = GETSHADER("dSSAO");

		TextureParameters params(TextureTarget::Tex2D);
		params.internalFormat = PixelInternalFormat::R16f;
		params.format = PixelFormat::Red;
		params.pixelType = PixelType::Float;
		params.minFilter = TextureMinFilter::Linear;
		params.magFilter = TextureMagFilter::Linear;
		params.wrap = TextureWrap::Clamp;
		params.mipMapLevels = 0;
		params.anisotropy = 0;

		texture = new Texture("ssao", width, height, 0, params);

		buffer = new FrameBuffer("ssaoBuffer");
		buffer->load({std::make_pair(Attachment::Color0, texture)});
	}

	SSAO::~SSAO() {
		delete texture;
		delete buffer;
	}

	void SSAO::calculateAO(const Texture *normal, const Texture *position, const Quad* quad) {
		buffer->bindDraw(Attachment::Color0);

		Renderer::clear(RendererBufferColor);

		shader->bind();

		const uint n = shader->getSampler("sampler0");
		const uint p = shader->getSampler("sampler1");

		normal->bind(n);
		position->bind(p);

		shader->updateUniforms();
		quad->render();

		normal->unbind(n);
		position->unbind(p);

		shader->unbind();

		buffer->unbind();
	}

}