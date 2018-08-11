//
// Created by FLXR on 7/12/2018.
//

#include <window/event.hpp>
#include <GL/glew.h>
#include "forwardrenderer.hpp"
#include "renderer.hpp"
#include "resources/shadermanager.hpp"

namespace xe {

	ForwardRenderer::ForwardRenderer(uint width, uint height, Camera *camera, bool useFXAA) :
			IRenderer3D(width, height, camera),
			useFXAA(useFXAA),
			lightMatrix(mat4::scale({0.0f, 0.0f, 0.0f})) {

		Renderer::enableCullFace(true);
		Renderer::enableDepthTesting(true);
		Renderer::enableDepthClamp(true);

		Renderer::setCullFace(CullFace::Back);

		//default shaders
		ambientLight = new AmbientLight(GETSHADER("defaultForwardAmbient"), 0.1f, color::WHITE);
		shadowMapShader = new ForwardRendererShader(GETSHADER("defaultShadowMap"));

		screenBuffer = api::FrameBufferOld::create(width, height, api::FrameBufferOld::COLOR);

		//shadows stuff
		lightCamera = new Camera(mat4(1.0f));

		for (uint i = 0; i < NUM_SHADOW_MAPS; ++i) {
			uint size = static_cast<uint>(1 << (i + 1));
			shadowBuffers0[i] = api::FrameBufferOld::create(size, size,
			                                                api::FrameBufferOld::RG32F, TextureMinFilter::Linear);

			shadowBuffers1[i] = api::FrameBufferOld::create(size, size,
			                                                api::FrameBufferOld::RG32F, TextureMinFilter::Linear);
		}

		//fx
		quad = new fx::Quad(width, height);
		finalFx = new fx::Final(width, height);
		blurFx = new fx::GaussBlur7x1(width, height);
	}

	ForwardRenderer::~ForwardRenderer() {
		for (uint i = 0; i < NUM_SHADOW_MAPS; ++i) {
			delete shadowBuffers0[i];
			delete shadowBuffers1[i];
		}

		delete screenBuffer;

		delete ambientLight;
		delete shadowMapShader;

		delete quad;
		delete finalFx;
		delete blurFx;
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

		screenBuffer->bind();
		screenBuffer->setClearColor({0.0f, 0.0f, 0.0f, 0.0f});
		screenBuffer->clear(RendererBufferColor | RendererBufferDepth);

		ambientLight->bind();

		for (auto &&target : targets) {
			ambientLight->setUniforms(target.material, target.transform, camera);
			ambientLight->updateUniforms();

			target.mesh->render();
		}

		ambientLight->unbind();

		screenBuffer->unbind();

		//other lights
		for (auto &&light : lights) {
			if (!light->isEnabled()) continue;

			const uint index = renderShadows(light);

			//render to screen
			Renderer::enableBlend(true);
			Renderer::setBlendFunction(BlendFunction::One, BlendFunction::One);
			Renderer::enableDepthMask(false);
			Renderer::setDepthFunction(DepthFunction::Equal);

			screenBuffer->bind();
			screenBuffer->clear(RendererBufferDepth);

			light->bind();

			uint shadowMapLoc = light->getResource("shadowMap");
			if (shadowMapLoc) {
				shadowBuffers0[index]->getTexture()->bind(shadowMapLoc);
			}

			for (auto &&target : targets) {
				mat4 lm = lightMatrix * target.transform.toMatrix();
				light->setUniform("lightMat", &lm, sizeof(mat4));
				light->setUniform("shadowVarianceMin", &shadowVarianceMin, sizeof(float));
				light->setUniform("shadowLightBleedingReduction",
				                  &shadowLightBleedingReduction, sizeof(float));

				light->setUniforms(target.material, target.transform, camera);
				light->updateUniforms();

				target.mesh->render();
			}

			if (shadowMapLoc) {
				shadowBuffers0[index]->getTexture()->unbind(shadowMapLoc);
			}

			light->unbind();

			Renderer::setDepthFunction(DepthFunction::Less);
			Renderer::enableDepthMask(true);
			Renderer::enableBlend(false);

			screenBuffer->unbind();
		}

		finalFx->render(quad, screenBuffer->getTexture(), useFXAA);

		targets.clear();
	}

	uint ForwardRenderer::renderShadows(BaseLight *light) {
		static const mat4 biasMatrix = mat4::scale({0.5f, 0.5f, 0.5f}) * mat4::translation({1.0f, 1.0f, 1.0f});

		const ShadowInfo *shadowInfo = light->getShadowInfo();

		uint shadowMapIndex = 0;
		if (shadowInfo) {
			shadowMapIndex = shadowInfo->shadowMapSizePower2 - 1;
		}

		shadowBuffers0[shadowMapIndex]->bind();
		shadowBuffers0[shadowMapIndex]->setClearColor({1.0f, 1.0f, 0.0f, 0.0f});
		shadowBuffers0[shadowMapIndex]->clear(RendererBufferColor | RendererBufferDepth);

		if (shadowInfo) {
			lightCamera->setProjection(shadowInfo->projection);
			light->updateLightCamera(lightCamera, camera);

			//uniforms for light
			lightMatrix = biasMatrix * lightCamera->getViewProjection();
			shadowVarianceMin = shadowInfo->minVariance;
			shadowLightBleedingReduction = shadowInfo->lightBleedReduction;

			shadowMapShader->bind();

			for (auto &&target : targets) {
				shadowMapShader->setUniforms(nullptr, target.transform, lightCamera);
				shadowMapShader->updateUniforms();

				if (shadowInfo->flipFaces) Renderer::setCullFace(CullFace::Front);

				target.mesh->render();

				if (shadowInfo->flipFaces) Renderer::setCullFace(CullFace::Back);
			}

			shadowMapShader->unbind();

			//blur shadow map
			const float shadowSoftness = shadowInfo->shadowSoftness;
			if (shadowSoftness) {
				blurShadowMap(shadowMapIndex, shadowSoftness);
			}

		} else {
			lightMatrix = mat4::scale({0.0f, 0.0f, 0.0f});
			shadowVarianceMin = 0.0f;
			shadowLightBleedingReduction = 0.0f;
		}

		shadowBuffers0[shadowMapIndex]->unbind();

		return shadowMapIndex;
	}

	void ForwardRenderer::blurShadowMap(uint index, float blurAmount) {
		//x blur
		vec2 scale(blurAmount / shadowBuffers0[index]->getWidth(), 0.0f);
		blurFx->render(quad, shadowBuffers0[index]->getTexture(), shadowBuffers1[index], scale);

		//y blur
		scale = vec2(0.0f, blurAmount / shadowBuffers0[index]->getWidth());
		blurFx->render(quad, shadowBuffers1[index]->getTexture(), shadowBuffers0[index], scale);
	}

	void ForwardRenderer::input(Event &event) {
		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Key::F1) {
				useFXAA = !useFXAA;
			}
			if (event.key.code == Keyboard::Key::F2) {
				blurFx->toggle();
			}
		}
	}

}