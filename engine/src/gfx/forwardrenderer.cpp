//
// Created by FLXR on 7/12/2018.
//
#include "forwardrenderer.hpp"
#include "renderer.hpp"

namespace xe { namespace gfx {

	ForwardRenderer::ForwardRenderer() {
		Renderer::enableCullFace(true);
		Renderer::enableDepthTesting(true);
		Renderer::enableDepthClamp(true);

		Renderer::setCullFace(CullFace::BACK);
	}

	ForwardRenderer::~ForwardRenderer() {

	}

	void ForwardRenderer::render(const Model *model, const Camera *camera) {
		Renderer::enableDepthTesting(true);

		//first run without blending
		Renderer::enableBlend(false);

		ambientLight->bind();
		ambientLight->setUniforms(model, camera);
		ambientLight->updateUniforms();

		model->mesh->render();

		ambientLight->unbind();


		//runs for all lights
		Renderer::enableBlend(true);
		Renderer::setBlendFunction(BlendFunction::ONE, BlendFunction::ONE);
		Renderer::enableDepthMask(false);
		Renderer::setDepthFunction(DepthFunction::EQUAL);

		for (auto &&light : lights) {
			if (!light->isEnabled()) continue;

			light->bind();

			light->setUniforms(model, camera);
			light->updateUniforms();

			model->mesh->render();

			light->unbind();
		}

		Renderer::setDepthFunction(DepthFunction::LESS);
		Renderer::enableDepthMask(true);
		Renderer::enableBlend(false);
	}

}}