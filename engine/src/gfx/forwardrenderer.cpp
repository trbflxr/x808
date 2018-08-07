//
// Created by FLXR on 7/12/2018.
//

#include "forwardrenderer.hpp"
#include "renderer.hpp"
#include "resources/shadermanager.hpp"
#include "gfx/api/texture2d.hpp"

namespace xe {

	ForwardRenderer::ForwardRenderer(uint width, uint height, Camera *camera, bool useFXAA) :
			IRenderer3D(width, height, camera),
			useFXAA(useFXAA),
			lightMatrix(mat4::scale({0.0f, 0.0f, 0.0f})) {

		Renderer::enableCullFace(true);
		Renderer::enableDepthTesting(true);
		Renderer::enableDepthClamp(true);

		Renderer::setCullFace(CullFace::BACK);

		//default shaders
		ambientLight = new AmbientLight(GETSHADER("defaultForwardAmbient"), 0.1f, color::WHITE);
		shadowMapShader = new ForwardRendererShader(GETSHADER("defaultShadowMap"));
		shadowMapBlurShader = new ForwardRendererShader(GETSHADER("defaultFXGaussBlur"));

		screenBuffer = api::FrameBuffer::create(width, height, api::FrameBuffer::COLOR);

		if (useFXAA) {
			fxaaFilter = new ForwardRendererShader(GETSHADER("defaultFXFXAA"));

			float a = 8.0f;
			float b = 1.0f / 128.0f;
			float c = 1.0f / 8.0f;
			vec2 textureSize = vec2(1.0f / width, 1.0f / height);

			fxaaFilter->setUniform("fxaaSpanMax", &a, sizeof(float));
			fxaaFilter->setUniform("fxaaReduceMin", &b, sizeof(float));
			fxaaFilter->setUniform("fxaaReduceMul", &c, sizeof(float));
			fxaaFilter->setUniform("inverseFilterTextureSize", &textureSize, sizeof(vec2));
		} else {
			fxaaFilter = new ForwardRendererShader(GETSHADER("defaultFXNULL"));
		}

		//shadows stuff
		lightCamera = new Camera(mat4(1.0f));

		for (uint i = 0; i < NUM_SHADOW_MAPS; ++i) {
			uint size = static_cast<uint>(1 << (i + 1));
			shadowBuffers0[i] = api::FrameBuffer::create(size, size,
			                                             api::FrameBuffer::RG32F, api::TextureFilter::BILINEAR);

			shadowBuffers1[i] = api::FrameBuffer::create(size, size,
			                                             api::FrameBuffer::RG32F, api::TextureFilter::BILINEAR);
		}

		dummyMesh = Mesh::createPlaneMesh();
		dummyMaterial = new Material(nullptr, 1.0f, 8.0f);
		dummyTransform.rotate(quat(vec3::XAXIS, -90.0f));
		dummyTransform.rotate(quat(vec3::ZAXIS, 180.0f));

		dummyGameObject.transform.setTranslation({0.0f, 0.0f, 0.0f});
		dummyGameObject.transform.setRotation(quat(vec3::YAXIS, 180.0f));
	}

	ForwardRenderer::~ForwardRenderer() {
		for (uint i = 0; i < NUM_SHADOW_MAPS; ++i) {
			delete shadowBuffers0[i];
			delete shadowBuffers1[i];
		}

		delete screenBuffer;

		delete ambientLight;
		delete shadowMapShader;
		delete shadowMapBlurShader;

		delete dummyMesh;
		delete dummyMaterial;
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
		screenBuffer->clear(RENDERER_BUFFER_COLOR | RENDERER_BUFFER_DEPTH);

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
			Renderer::setBlendFunction(BlendFunction::ONE, BlendFunction::ONE);
			Renderer::enableDepthMask(false);
			Renderer::setDepthFunction(DepthFunction::EQUAL);

			screenBuffer->bind();
			screenBuffer->clear(RENDERER_BUFFER_DEPTH);

			light->bind();

			uint shadowMapLoc = light->getSamplerLocation("shadowMap");
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

			Renderer::setDepthFunction(DepthFunction::LESS);
			Renderer::enableDepthMask(true);
			Renderer::enableBlend(false);

			screenBuffer->unbind();
		}

		applyFilter(fxaaFilter, screenBuffer, nullptr);

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
		shadowBuffers0[shadowMapIndex]->clear(RENDERER_BUFFER_COLOR | RENDERER_BUFFER_DEPTH);

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

				if (shadowInfo->flipFaces) Renderer::setCullFace(CullFace::FRONT);

				target.mesh->render();

				if (shadowInfo->flipFaces) Renderer::setCullFace(CullFace::BACK);
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
		//set camera
		lightCamera->setProjection(mat4(1.0f));
		lightCamera->hookEntity(&dummyGameObject);

		shadowMapBlurShader->bind();

		//x blur
		vec2 scale(blurAmount / shadowBuffers0[index]->getWidth(), 0.0f);
		shadowMapBlurShader->setUniform("blurScale", &scale, sizeof(vec2));
		applyFilter(shadowMapBlurShader, shadowBuffers0[index], shadowBuffers1[index]);

		//y blur
		scale = vec2(0.0f, blurAmount / shadowBuffers0[index]->getWidth());
		shadowMapBlurShader->setUniform("blurScale", &scale, sizeof(vec2));
		applyFilter(shadowMapBlurShader, shadowBuffers1[index], shadowBuffers0[index]);

		shadowMapBlurShader->unbind();

		lightCamera->unhookEntity();
	}

	void
	ForwardRenderer::applyFilter(ForwardRendererShader *filter, api::FrameBuffer *src, api::FrameBuffer *dest) {
		XE_ASSERT(src != dest);

		dummyMaterial->setTexture(src->getTexture());

		if (dest) {
			dest->bind();
			dest->clear(RENDERER_BUFFER_DEPTH);
		} else {
			Renderer::setViewport(0, 0, width, height);
			Renderer::clear(RENDERER_BUFFER_DEPTH);
		}

		filter->setUniforms(dummyMaterial, dummyTransform, lightCamera);
		filter->updateUniforms();

		dummyMesh->render();

		if (dest) {
			dest->unbind();
		}
	}

}