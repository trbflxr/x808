//
// Created by FLXR on 3/20/2019.
//

#include <xe/gfx/fx/hbao.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/shadermanager.hpp>

namespace xe { namespace fx {

	HBAO::HBAO(uint width, uint height) :
			RenderEffect(width, height) {

		aoShader = GETSHADER("dHBAO");

		TextureParameters params(TextureTarget::Tex2D);
		params.internalFormat = PixelInternalFormat::R16f;
		params.format = PixelFormat::Red;
		params.pixelType = PixelType::Float;
		params.minFilter = TextureMinFilter::Linear;
		params.magFilter = TextureMagFilter::Linear;
		params.wrap = TextureWrap::Clamp;
		params.mipMapLevels = 0;
		params.anisotropy = 0;

		aoTexture = new Texture("hbao", width, height, 0, params);

		aoBuffer = new FrameBuffer("hbaoBuffer");
		aoBuffer->load({std::make_pair(Attachment::Color0, aoTexture)});
	}

	HBAO::~HBAO() {
		delete aoTexture;
		delete aoBuffer;
	}

	void HBAO::calculateAO(const Texture *normal, const Texture *depth, const Camera *camera, const Quad *quad) {
		aoBuffer->bindDraw(Attachment::Color0);
		Renderer::setViewport(0, 0, width, height);
		Renderer::clear(RendererBufferColor);

		aoShader->bind();

		const uint n = aoShader->getSampler("sampler0");
		const uint d = aoShader->getSampler("sampler1");

		const mat4 &m = camera->getProjection();

		aoShader->setUniform("invProj", &m, sizeof(mat4));
		aoShader->updateUniforms();

		normal->bind(n);
		depth->bind(d);

		quad->render();

		normal->unbind(n);
		depth->unbind(d);

		aoShader->unbind();

		aoBuffer->unbind();
	}

}}
