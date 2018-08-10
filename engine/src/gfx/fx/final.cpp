//
// Created by FLXR on 8/8/2018.
//

#include "final.hpp"
#include "gfx/renderer.hpp"
#include "resources/shadermanager.hpp"

namespace xe { namespace fx {

	Final::Final(uint width, uint height) :
			RenderEffect(width, height) { }

	Final::~Final() {
		delete finalTexture;
		delete finalFBO;
	}

	void Final::load() {
		loadPrograms();
		loadBuffers();
	}

	void Final::loadPrograms() {
		finalShader = GETSHADER("defaultFinalScene");
	}

	void Final::loadBuffers() {
		static api::TextureParameters params(TextureTarget::Tex2D,
		                                     PixelInternalFormat::Rgba16f,
		                                     PixelFormat::Rgba,
		                                     PixelType::Float);

		finalTexture = api::Texture::create(width, height, 0, params);

		finalFBO = api::FrameBuffer::create("FinalScene");
		finalFBO->load({std::pair<Attachment, api::Texture *>(Attachment::Color0, finalTexture)});
	}

	void Final::render(Quad *quad) {
		Renderer::setViewport(0, 0, width, height);
		Renderer::clear(RendererBufferDepth);

		finalShader->bind();

		//bind to sampler0
		static uint slot = finalShader->getResources()[0]->getRegister();

		finalTexture->bind(slot);
		quad->render();
		finalTexture->unbind(slot);

		finalShader->unbind();
	}

}}
