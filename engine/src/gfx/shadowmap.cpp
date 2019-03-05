//
// Created by FLXR on 3/5/2019.
//

#include <xe/gfx/shadowmap.hpp>
#include <xe/resources/shadermanager.hpp>
#include <xe/gfx/renderer.hpp>

namespace xe {

	ShadowMap::ShadowMap(uint size) :
			size(size) {

		TextureParameters params(TextureTarget::Tex2D);
		params.internalFormat = PixelInternalFormat::Rg16f;
		params.format = PixelFormat::Rg;
		params.pixelType = PixelType::Float;
		params.magFilter = TextureMagFilter::Nearest;
		params.minFilter = TextureMinFilter::Nearest;
		params.wrap = TextureWrap::ClampToEdge;
		params.mipMapLevels = 0;
		params.anisotropy = 0;

		texture = new Texture("ShadowMapTexture", size, size, 0, params);

		params.internalFormat = PixelInternalFormat::DepthComponent;
		params.format = PixelFormat::DepthComponent;
		depthTexture = new Texture("ShadowMapDepthTexture", size, size, 0, params);

		buffer = new FrameBuffer("ShadowMapBuffer");
		buffer->load({std::make_pair(Attachment::Depth, depthTexture),
		              std::make_pair(Attachment::Color5, texture)});

//		buffer = new FrameBuffer("ShadowMapBuffer");
//		buffer->load({std::make_pair(Attachment::Color5, texture)});

		shader = GETSHADER("dVsm");
		shader->bindUniformBlock("Camera", 1);
	}

	ShadowMap::~ShadowMap() {
		delete buffer;
		delete texture;
		delete depthTexture;
	}

	void ShadowMap::render(const std::vector<Model *> &models, bool rawZ) {
		buffer->bindDraw(Attachment::Color5);
		Renderer::setViewport(0, 0, size, size);
		Renderer::clear(RendererBufferColor | RendererBufferDepth);

		shader->bind();

		const int32 rz = rawZ ? 1 : 0;
		shader->setUniform("rawZ", &rz, sizeof(int32));

		for (const auto &m : models) {
			shader->setUniform("model", &m->toMatrix(), sizeof(mat4));
			shader->updateUniforms();

			m->render(BeginMode::Triangles);
		}

		shader->unbind();

		buffer->unbind();
	}

}
