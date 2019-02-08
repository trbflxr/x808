//
// Created by FLXR on 2/8/2019.
//

#include <xe/gfx/layer.hpp>
#include <xe/gfx/renderer.hpp>

namespace xe {

	Layer::Layer() :
			app(Application::get()),
			window(app.getWindow()),
			visible(true) {

		const uint width = static_cast<uint>(app.getWindowSize().x);
		const uint height = static_cast<uint>(app.getWindowSize().y);

		TextureParameters params(TextureTarget::Tex2D);
		params.internalFormat = PixelInternalFormat::Depth32fStencil8;
		params.format = PixelFormat::DepthComponent;
		params.pixelType = PixelType::Float;
		params.minFilter = TextureMinFilter::Nearest;
		params.magFilter = TextureMagFilter::Nearest;
		params.wrap = TextureWrap::Clamp;
		params.mipMapLevels = 0;
		params.anisotropy = 0;

		depth = new Texture("depthStencil", width, height, 0, params, true);

		params.internalFormat = PixelInternalFormat::Rgba16f;
		params.format = PixelFormat::Rgba;
		renderTexture = new Texture("renderTexture", width, height, 0, params, true);


		buffer = new FrameBuffer("buffer");
		buffer->load({std::make_pair(Attachment::DepthStencil, depth),
		              std::make_pair(Attachment::Color0, renderTexture)});

	}

	Layer::~Layer() {
		delete buffer;
		delete renderTexture;
		delete depth;
	}

	void Layer::renderBegin() {
		const uint width = static_cast<uint>(app.getWindowSize().x);
		const uint height = static_cast<uint>(app.getWindowSize().y);

		buffer->bindDraw(Attachment::Color0);
		Renderer::setViewport(0, 0, width, height);
		Renderer::clear(RendererBufferColor | RendererBufferDepth);
	}

	void Layer::renderEnd() {
		buffer->unbind();
	}

}