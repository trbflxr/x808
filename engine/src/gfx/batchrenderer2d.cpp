//
// Created by FLXR on 9/10/2018.
//

#include <algorithm>
#include <xe/config.hpp>
#include <xe/gfx/batchrenderer2d.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/shadermanager.hpp>

namespace xe {

	BatchRenderer2D::BatchRenderer2D(uint width, uint height, Camera *camera,
	                                 bool enableLighting,
	                                 const Shader *customShader,
	                                 const Shader *customTextShader) :
			camera(camera),
			enableLighting(enableLighting) {

		XE_ASSERT(!customTextShader, "Not implemented yet...");

		if (enableLighting) {
			static constexpr uint lightsUboLocation = 2;

			BufferLayout l;
			l.push<vec4>("position");
			l.push<vec4>("color");

			lightUBO = new UniformBuffer(BufferStorage::Dynamic, lightsUboLocation, l, gConfig.maxPointLights2D);

			if (customShader) {
				renderer = new Renderer2D(width, height, camera, customShader);
			} else {
				renderer = new Renderer2D(width, height, camera, GETSHADER("dLightRenderer"));
			}

			renderer->getShader()->bindUniformBlock("Lights", lightsUboLocation);

		} else {
			renderer = new Renderer2D(width, height, camera, customShader);
		}

		textRenderer = new TextRenderer(width, height, camera);

		static TextureParameters params(TextureTarget::Tex2D);
		params.internalFormat = PixelInternalFormat::Rgba16;
		params.format = PixelFormat::Rgba;
		params.pixelType = PixelType::UnsignedByte;
		params.minFilter = TextureMinFilter::Nearest;
		params.magFilter = TextureMagFilter::Nearest;
		params.wrap = TextureWrap::Clamp;
		params.mipMapLevels = 0;
		params.anisotropy = 0;

		renderTexture = new Texture("r2dRenderTexture", width, height, 0, params, true);

		params.internalFormat = PixelInternalFormat::DepthComponent16;
		params.format = PixelFormat::DepthComponent;
		depthTexture = new Texture("r2dDepthTexture", width, height, 0, params, true);

		buffer = new FrameBuffer("r2dBuffer");
		buffer->load({std::make_pair(Attachment::Color0, renderTexture),
		              std::make_pair(Attachment::Depth, depthTexture)});
	}

	BatchRenderer2D::~BatchRenderer2D() {
		delete renderer;
		delete textRenderer;

		delete buffer;
		delete renderTexture;
		delete depthTexture;
	}

	void BatchRenderer2D::submit(const IRenderable2D *target) {
		if (!target->isVisible()) return;

		const Texture *texture = target->getTexture();

		if (texture && texture->hasTransparency()) {
			transparentTargets.push_back(target);
		} else {
			targets.push_back(target);
		}
	}

	void BatchRenderer2D::submit(const Text *text) {
		BatchRenderer2D::text.push_back(text);
	}

	void BatchRenderer2D::submit(const Light2D *light) {
		if (lights.size() + 1 > gConfig.maxPointLights2D) {
			XE_CORE_ERROR("Maximum 2d lights reached (", gConfig.maxPointLights2D, ")");
			return;
		}

		lights.push_back(light);
	}

	void BatchRenderer2D::setAmbientLight(const vec3 &color) {
		XE_ASSERT(enableLighting, "Have to create renderer with lighting support for use it");
		ambient = color;

		renderer->getShader()->setUniform("ambient", &ambient, sizeof(vec3));
		renderer->getShader()->updateUniforms();
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
			if (!lights.empty()) {
				int32 size = static_cast<int32>(lights.size());

				renderer->getShader()->setUniform("lightsSize", &size, sizeof(int32));
				renderer->getShader()->updateUniforms();
			}

			for (uint i = 0; i < lights.size(); ++i) {
				vec4 lightPos = vec4(lights[i]->getPosition().x, lights[i]->getPosition().y, 0.0f, 0.0f);
				vec4 lightColor = vec4(lights[i]->getColor(), lights[i]->getIntensity());

				lightUBO->bind();
				lightUBO->update(&lightPos, 0, i);
				lightUBO->update(&lightColor, 1, i);
				lightUBO->unbind();
			}

			renderSpritesInternal();

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