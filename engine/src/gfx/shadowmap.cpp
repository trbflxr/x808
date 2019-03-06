//
// Created by FLXR on 3/5/2019.
//

#include <xe/gfx/shadowmap.hpp>
#include <xe/resources/shadermanager.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/gfx/scene.hpp>

namespace xe {

	ShadowMap::ShadowMap(uint size) :
			size(size) {

		TextureParameters params(TextureTarget::Tex2D);
		params.internalFormat = PixelInternalFormat::Rg16f;
		params.format = PixelFormat::Rg;
		params.pixelType = PixelType::Float;
		params.magFilter = TextureMagFilter::Linear;
		params.minFilter = TextureMinFilter::Linear;
		params.wrap = TextureWrap::ClampToEdge;
		params.mipMapLevels = 0;
		params.anisotropy = 0;

		texture = new Texture("ShadowMapTexture", size, size, 0, params);

		params.internalFormat = PixelInternalFormat::DepthComponent16;
		params.format = PixelFormat::DepthComponent;
		depthTexture = new Texture("ShadowMapDepthTexture", size, size, 0, params);

		buffer = new FrameBuffer("ShadowMapBuffer");
		buffer->load({std::make_pair(Attachment::Depth, depthTexture),
		              std::make_pair(Attachment::Color0, texture)});

		shader = GETSHADER("dVsm");
	}

	ShadowMap::~ShadowMap() {
		delete buffer;
		delete texture;
		delete depthTexture;
	}

	void ShadowMap::render(const SpotLight *light, const Scene *scene) {
		Renderer::enableBlend(false);
		Renderer::enableDepthTesting(true);
		Renderer::enableDepthMask(true);
		Renderer::enableCullFace(true);
		Renderer::setCullFace(CullFace::Back);

		buffer->bindDraw(Attachment::Color0);
		Renderer::setViewport(0, 0, size, size);
		Renderer::clear(RendererBufferColor | RendererBufferDepth);

		shader->bind();

		const mat4 &view = light->getView();
		const mat4 &proj = light->getProjection();

		shader->setUniform("view", &view, sizeof(mat4));
		shader->setUniform("projection", &proj, sizeof(mat4));

		for (const auto &m : scene->getModels()) {
			shader->setUniform("model", &m->toMatrix(), sizeof(mat4));
			shader->updateUniforms();

			m->render(BeginMode::Triangles);
		}

		shader->unbind();

		buffer->unbind();
	}

}
