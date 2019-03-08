//
// Created by FLXR on 3/6/2019.
//

#include <xe/gfx/shadows.hpp>
#include <xe/gfx/scene.hpp>
#include <xe/resources/shadermanager.hpp>
#include <xe/gfx/renderer.hpp>

namespace xe {

	Shadows::Shadows(ShadowParameters params) :
			params(params),
			spotShadowsIndex(0) {

		TextureParameters tp(TextureTarget::Tex2DArray);
		tp.internalFormat = PixelInternalFormat::Rg16f;
		tp.format = PixelFormat::Rg;
		tp.pixelType = PixelType::Float;
		tp.magFilter = TextureMagFilter::Linear;
		tp.minFilter = TextureMinFilter::Linear;
		tp.wrap = TextureWrap::Clamp;

		spotTexture = new Texture("ST", params.spotSize, params.spotSize, params.maxSpotCount, tp);

		tp.internalFormat = PixelInternalFormat::DepthComponent16;
		tp.format = PixelFormat::DepthComponent;
		spotDepthTexture = new Texture("SDT", params.spotSize, params.spotSize, params.maxSpotCount, tp);

		spotBuffer = new FrameBuffer("SB");
		spotBuffer->load({std::make_pair(Attachment::Depth, spotDepthTexture),
		                  std::make_pair(Attachment::Color0, spotTexture)});

		spotShader = GETSHADER("dSpotShadows");
		spotShader->bindUniformBlock("SpotShadows", 2);

		BufferLayout layout;
		layout.push<mat4>("view");
		layout.push<mat4>("projection");

		spotUBO = new UniformBuffer(BufferStorage::Dynamic, 2, layout, params.maxSpotCount);
	}

	Shadows::~Shadows() {
		delete spotBuffer;
		delete spotUBO;
		delete spotTexture;
		delete spotDepthTexture;
	}

	void Shadows::render(const Scene *scene) {
		spotShadowsIndex = 0;


		spotUBO->bind();
		for (const auto &light : scene->getSpotLights()) {
			if (!light->isShadowed() || (uint) spotShadowsIndex - 1 == params.maxSpotCount) {
				light->setShadowId(-1);
				continue;
			}

			spotUBO->update(&light->getView(), 0, spotShadowsIndex);
			spotUBO->update(&light->getProjection(), 1, spotShadowsIndex);

			light->setShadowId(spotShadowsIndex);
			++spotShadowsIndex;
		}
		spotUBO->unbind();

		renderSpotShadows(scene);
	}

	void Shadows::renderSpotShadows(const Scene *scene) {
		Renderer::enableBlend(false);
		Renderer::enableDepthTesting(true);
		Renderer::enableDepthMask(true);
		Renderer::enableCullFace(true);
		Renderer::setCullFace(CullFace::Back);

		spotBuffer->bindDraw(Attachment::Color0);
		Renderer::setViewport(0, 0, params.spotSize, params.spotSize);
		Renderer::clear(RendererBufferColor | RendererBufferDepth);

		spotShader->bind();

		for (const auto &m : scene->getModels()) {
			spotShader->setUniform("model", &m->toMatrix(), sizeof(mat4));
			spotShader->updateUniforms();

			m->renderInstanced(BeginMode::Triangles, spotShadowsIndex);
		}

		spotShader->unbind();

		spotBuffer->unbind();
	}

}
