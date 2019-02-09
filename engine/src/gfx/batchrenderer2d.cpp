//
// Created by FLXR on 9/10/2018.
//

#include <algorithm>
#include <xe/gfx/batchrenderer2d.hpp>
#include <xe/gfx/renderer.hpp>

namespace xe {

	BatchRenderer2D::BatchRenderer2D(uint width, uint height, Camera *camera,
	                                 bool enableLighting,
	                                 Shader *customShader,
	                                 Shader *customTextShader) :
			camera(camera),
			enableLighting(enableLighting) {

		XE_ASSERT(!customTextShader, "Not implemented yet...");

		if (enableLighting) { //fixme
			Shader *lightShader = new Shader("lightShader", {
					ShaderFile::fromFile(ShaderType::Vert, "light2d.vert"),
					ShaderFile::fromFile(ShaderType::Frag, "light2d.frag")
			});

			renderer = new Renderer2D(width, height, camera, lightShader);
		} else {
			renderer = new Renderer2D(width, height, camera, customShader);
		}

//		renderer = new Renderer2D(width, height, camera, customShader);
		textRenderer = new TextRenderer(width, height, camera);

		static TextureParameters params(TextureTarget::Tex2D);
		params.internalFormat = PixelInternalFormat::Depth32fStencil8;
		params.format = PixelFormat::DepthComponent;
		params.pixelType = PixelType::Float;
		params.minFilter = TextureMinFilter::Nearest;
		params.magFilter = TextureMagFilter::Nearest;
		params.wrap = TextureWrap::Clamp;
		params.mipMapLevels = 0;
		params.anisotropy = 0;

		depth = new Texture("r2dDepthStencil", width, height, 0, params, true);

		params.internalFormat = PixelInternalFormat::Rgba16f;
		params.format = PixelFormat::Rgba;
		renderTexture = new Texture("r2dRenderTexture", width, height, 0, params, true);

		buffer = new FrameBuffer("r2dBuffer");
		buffer->load({std::make_pair(Attachment::DepthStencil, depth),
		              std::make_pair(Attachment::Color0, renderTexture)});
	}

	BatchRenderer2D::~BatchRenderer2D() {
		delete renderer;
		delete textRenderer;

		delete buffer;
		delete renderTexture;
		delete depth;
	}

	void BatchRenderer2D::submit(const IRenderable2D *target) {
		if (!target->isVisible()) return;

		const Texture *texture = target->getTexture();

		if (texture && texture->getParams().format == PixelFormat::Rgba) {
			transparentTargets.push_back(target);
		} else {
			targets.push_back(target);
		}
	}

	void BatchRenderer2D::submit(const Text *text) {
		BatchRenderer2D::text.push_back(text);
	}

	void BatchRenderer2D::submit(const Light2D *light) {
		lights.push_back(light);
	}

	void BatchRenderer2D::render() {
		if (targets.empty() && transparentTargets.empty()) return;

		renderer->updateCamera();

		static constexpr float color[4] = {0, 0, 0, 0};
		static constexpr float depth[4] = {1, 1, 1, 1};

		//buffer
		buffer->bindDraw(Attachment::Color0);
		Renderer::setViewport(0, 0, renderer->getWidth(), renderer->getHeight());
		Renderer::clearBufferF(Attachment::Color0, color);
		Renderer::clearBufferF(Attachment::Depth, depth);


		if (enableLighting) {
			for (const auto &l : lights) {
				vec2 lightPos = l->getPosition();
				vec3 lightColor = l->getColor();
				vec2 id = vec2(l->getIntensity(), l->getDistance());

				renderer->getShader()->setUniform("lightPosition", &lightPos, sizeof(vec2));
				renderer->getShader()->setUniform("lightColor", &lightColor, sizeof(vec3));
				renderer->getShader()->setUniform("intensityDistance", &id, sizeof(vec2));

				renderer->getShader()->updateUniforms();

				renderSpritesInternal();
			}
			lights.clear();

		} else {
			renderSpritesInternal();
		}

		if (!text.empty()) {
			textRenderer->updateCamera();

			Renderer::enableDepthMask(true);
			Renderer::enableDepthTesting(false);
			textRenderer->render(text);

			text.clear();
		}

		buffer->unbind();
	}

	void BatchRenderer2D::renderSpritesInternal() {
		std::sort(targets.begin(), targets.end(),
		          [](const IRenderable2D *a, const IRenderable2D *b) {
			          return a->getTexture() > b->getTexture();
		          });

		renderer->render(targets);
		targets.clear();

		//draw transparent
		if (!transparentTargets.empty()) {
			//todo: there must be a better solution
			std::sort(transparentTargets.begin(), transparentTargets.end(),
			          [](const IRenderable2D *a, const IRenderable2D *b) {
				          return a->getLayer() < b->getLayer();
			          });

			renderer->render(transparentTargets);
			transparentTargets.clear();
		}
	}

	void BatchRenderer2D::clear() {
		transparentTargets.clear();
		targets.clear();
		text.clear();
		lights.clear();
	}

}