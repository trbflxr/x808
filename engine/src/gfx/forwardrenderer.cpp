//
// Created by FLXR on 7/12/2018.
//
#include <ecs/components/spritecomponent.hpp>
#include "forwardrenderer.hpp"
#include "renderer.hpp"

namespace xe { namespace gfx {

	ForwardRenderer::ForwardRenderer(uint width, uint height, uint shadowMapSize, const Camera *camera) :
			width(width),
			height(height),
			camera(camera),
			enableShadows(shadowMapSize != 0) {

		Renderer::enableCullFace(true);
		Renderer::enableDepthTesting(true);
		Renderer::enableDepthClamp(true);

		Renderer::setCullFace(CullFace::BACK);

		if (enableShadows) {
			shadowBuffer = api::FrameBuffer::create(shadowMapSize, shadowMapSize, api::FrameBuffer::COLOR);
			shadowBuffer->setClearColor({1, 0, 1, 1});
		}
	}

	ForwardRenderer::~ForwardRenderer() {
		delete shadowBuffer;
	}

	void ForwardRenderer::begin() {

	}

	void ForwardRenderer::submit(const Mesh *mesh, const Material *material, const Transform &transform) {
		targets.emplace_back(mesh, material, transform);
	}

	void ForwardRenderer::flush(SpriteComponent *s) {
		Renderer::enableDepthTesting(true);

		//first run without blending
		Renderer::enableBlend(false);

		ambientLight->bind();

		for (auto &&target : targets) {
			ambientLight->setUniforms(target.material, target.transform, camera);
			ambientLight->updateUniforms();

			target.mesh->render();
		}

		ambientLight->unbind();

		//shadows
		if (enableShadows) {
			shadowBuffer->bind();
			shadowBuffer->clear();

			for (auto &&light : lights) {
				if (!light->isEnabled() || !light->isCastShadow()) continue;

				light->bind();

				for (auto &&target : targets) {
					light->setUniforms(target.material, target.transform, camera);
					light->updateUniforms();

					target.mesh->render();
				}

				light->unbind();
			}

			shadowBuffer->unbind();
		}

		//runs for all lights
		Renderer::enableBlend(true);
		Renderer::setBlendFunction(BlendFunction::ONE, BlendFunction::ONE);
		Renderer::enableDepthMask(false);
		Renderer::setDepthFunction(DepthFunction::EQUAL);

		Renderer::setViewport(0, 0, width, height);
		Renderer::setClearColor(color::BLACK);

		for (auto &&light : lights) {
			if (!light->isEnabled()) continue;

			light->bind();

			uint shadowMap = light->getSamplerLocation("shadowMap");
			if (shadowMap) {

			}

			for (auto &&target : targets) {
				light->setUniforms(target.material, target.transform, camera);
				light->updateUniforms();

				target.mesh->render();
			}

			if (shadowMap) {

			}

			light->unbind();
		}

		Renderer::setDepthFunction(DepthFunction::LESS);
		Renderer::enableDepthMask(true);
		Renderer::enableBlend(false);

		targets.clear();


		s->texture = shadowBuffer->getTexture();
	}

}}