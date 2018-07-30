//
// Created by FLXR on 7/12/2018.
//

#include "forwardrenderer.hpp"
#include "renderer.hpp"
#include "resources/shadermanager.hpp"
#include "gfx/lights/shadowmapshader.hpp"

namespace xe { namespace gfx {

	ForwardRenderer::ForwardRenderer(uint width, uint height, const Camera *camera, uint shadowMapSize,
	                                 api::Shader *shadowMapShader,
	                                 api::Shader *defaultShader) :
			width(width),
			height(height),
			camera(camera),
			enableShadows(shadowMapSize > 0 && shadowMapShader != nullptr) {

		Renderer::enableCullFace(true);
		Renderer::enableDepthTesting(true);
		Renderer::enableDepthClamp(true);

		Renderer::setCullFace(CullFace::BACK);

		ForwardRenderer::shadowMapShader = new ShadowMapShader(shadowMapShader);
		ambientLight = new AmbientLight(defaultShader, 0.1f, color::WHITE);

		lightCamera = new Camera(mat4(1.0f));
		shadowBuffer = api::FrameBuffer::create(shadowMapSize, shadowMapSize, api::FrameBuffer::RG32F);
	}

	ForwardRenderer::~ForwardRenderer() {
		delete shadowBuffer;
		delete ambientLight;
	}

	void ForwardRenderer::begin() {
		Renderer::enableDepthTesting(true);
	}

	void ForwardRenderer::submit(const Mesh *mesh, const Material *material, const Transform &transform) {
		targets.emplace_back(mesh, material, transform);
	}

	void ForwardRenderer::flush() {
		//first run without blending
		//ambient light
		Renderer::enableBlend(false);

		ambientLight->bind();

		for (auto &&target : targets) {
			ambientLight->setUniforms(target.material, target.transform, camera);
			ambientLight->updateUniforms();

			target.mesh->render();
		}

		ambientLight->unbind();


		//other lights
		for (auto &&light : lights) {
			if (!light->isEnabled()) continue;

			shadowBias = 0;

			renderShadows(light);

			//render to screen
			Renderer::enableBlend(true);
			Renderer::setBlendFunction(BlendFunction::ONE, BlendFunction::ONE);
			Renderer::enableDepthMask(false);
			Renderer::setDepthFunction(DepthFunction::EQUAL);

			Renderer::setViewport(0, 0, width, height);

			light->bind();

			uint shadowMapLoc = light->getSamplerLocation("shadowMap");
			if (shadowMapLoc) {
				shadowBuffer->getTexture()->bind(shadowMapLoc);
			}

			for (auto &&target : targets) {
				light->setLightMatrix(lightMatrix * target.transform.toMatrix());
				light->setUniforms(target.material, target.transform, camera);
				light->updateUniforms();

				target.mesh->render();
			}

			if (shadowMapLoc) {
				shadowBuffer->getTexture()->unbind(shadowMapLoc);
			}

			light->unbind();

			Renderer::setDepthFunction(DepthFunction::LESS);
			Renderer::enableDepthMask(true);
			Renderer::enableBlend(false);
		}

		targets.clear();
	}

	void ForwardRenderer::renderShadows(BaseLight *light) {
		static const mat4 biasMatrix = mat4::scale({0.5f, 0.5f, 0.5f}) * mat4::translation({1.0f, 1.0f, 1.0f});

		const ShadowInfo *shadowInfo = light->getShadowInfo();

		shadowBuffer->bind();
		shadowBuffer->clear();

		if (shadowInfo) {
			lightCamera->setProjection(shadowInfo->projection);
			lightCamera->hookEntity(light);

			lightMatrix = biasMatrix * lightCamera->getViewProjection();
			shadowBias = shadowInfo->bias / shadowBuffer->getWidth();

			shadowMapShader->bind();

			for (auto &&target : targets) {
				shadowMapShader->setUniforms(nullptr, target.transform, lightCamera);
				shadowMapShader->updateUniforms();

				if (shadowInfo->flipFaces) Renderer::setCullFace(CullFace::FRONT);

				target.mesh->render();

				if (shadowInfo->flipFaces) Renderer::setCullFace(CullFace::BACK);
			}

			shadowMapShader->unbind();
		}

		shadowBuffer->unbind();
	}

}}