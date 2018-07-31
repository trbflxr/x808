//
// Created by FLXR on 7/12/2018.
//

#include "forwardrenderer.hpp"
#include "renderer.hpp"
#include "resources/shadermanager.hpp"
#include "gfx/api/texture2d.hpp"
#include "gfx/lights/shadowmapshader.hpp"

namespace xe { namespace gfx {

	ForwardRenderer::ForwardRenderer(uint width, uint height, Camera *camera, uint shadowMapSize) :
			width(width),
			height(height),
			camera(camera),
			enableShadows(shadowMapSize > 0 && shadowMapShader != nullptr) {

		Renderer::enableCullFace(true);
		Renderer::enableDepthTesting(true);
		Renderer::enableDepthClamp(true);

		Renderer::setCullFace(CullFace::BACK);

		//default shaders
		ambientLight = new AmbientLight(GETSHADER("forwardAmbient"), 0.1f, color::WHITE);
		shadowMapShader = new ShadowMapShader(GETSHADER("shadowMap"));
		shadowMapBlurShader = new ShadowMapBlurShader(GETSHADER("filterGaussBlur"));

		lightCamera = new Camera(mat4(1.0f));

		shadowBuffer0 = api::FrameBuffer::create(shadowMapSize, shadowMapSize,
		                                         api::FrameBuffer::RG32F, api::TextureFilter::LINEAR);

		shadowBuffer1 = api::FrameBuffer::create(shadowMapSize, shadowMapSize,
		                                         api::FrameBuffer::RG32F, api::TextureFilter::LINEAR);

		//shadows stuff
		//todo: embed plane2
		dummyMesh = new Mesh("assets/models/plane2.obj");
		dummyMaterial = new Material(nullptr, 1.0f, 8.0f);
		dummyTransform.rotate(quat(vec3::XAXIS, to_rad(-90)));
		dummyTransform.rotate(quat(vec3::ZAXIS, to_rad(180)));

		dummyGameObject.transform.setTranslation({0.0f, 0.0f, 0.0f});
		dummyGameObject.transform.setRotation(quat(vec3::YAXIS, to_rad(180.0f)));
	}

	ForwardRenderer::~ForwardRenderer() {
		delete shadowBuffer0;
		delete shadowBuffer1;

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

		ambientLight->bind();

		for (auto &&target : targets) {
			ambientLight->setUniforms(target.material, target.transform, camera);
			ambientLight->updateUniforms();

			target.mesh->render();
		}


		dummyMaterial->setTexture(shadowBuffer1->getTexture());

		ambientLight->setUniforms(dummyMaterial, dummyTransform, camera);
		ambientLight->updateUniforms();

		dummyMesh->render();


		ambientLight->unbind();


		//other lights
		for (auto &&light : lights) {
			if (!light->isEnabled()) continue;

			shadowVarianceMin = 0.0f;
			shadowLightBleedingReduction = 0.0f;

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
				shadowBuffer0->getTexture()->bind(shadowMapLoc);
			}

			for (auto &&target : targets) {
				mat4 lm = lightMatrix * target.transform.toMatrix();
				light->setUniform("sys_LightMat", &lm, sizeof(mat4), api::Shader::VERT);
				light->setUniform("sys_shadowVarianceMin", &shadowVarianceMin, sizeof(float), api::Shader::FRAG);
				light->setUniform("sys_shadowLightBleedingReduction",
				                  &shadowLightBleedingReduction, sizeof(float), api::Shader::FRAG);

				light->setUniforms(target.material, target.transform, camera);
				light->updateUniforms();

				target.mesh->render();
			}

			if (shadowMapLoc) {
				shadowBuffer0->getTexture()->unbind(shadowMapLoc);
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

		if (shadowInfo) {
			shadowBuffer0->bind();
			shadowBuffer0->clear();

			lightCamera->setProjection(shadowInfo->projection);
			lightCamera->hookEntity(light);

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

			shadowBuffer0->unbind();

			lightCamera->unhookEntity();

			//blur shadow map
			blurShadowMap(shadowInfo->shadowSoftness);
		}
	}

	void ForwardRenderer::blurShadowMap(float blurAmount) {
		//set camera
		lightCamera->setProjection(mat4(1.0f));
		lightCamera->hookEntity(&dummyGameObject);

		shadowMapBlurShader->bind();

		//x blur
		vec2 scale(1.0f / (shadowBuffer0->getWidth() * blurAmount), 0.0f);
		shadowMapBlurShader->setUniform("sys_BlurScale", &scale, sizeof(vec2), api::Shader::FRAG);
		applyFilter(shadowMapBlurShader, shadowBuffer0, shadowBuffer1);

		//y blur
		scale = vec2(0.0f, 1.0f / (shadowBuffer0->getWidth() * blurAmount));
		shadowMapBlurShader->setUniform("sys_BlurScale", &scale, sizeof(vec2), api::Shader::FRAG);
		applyFilter(shadowMapBlurShader, shadowBuffer1, shadowBuffer0);

		shadowMapBlurShader->unbind();

		lightCamera->unhookEntity();
	}

	void ForwardRenderer::applyFilter(ShadowMapBlurShader *filter, api::FrameBuffer *src, api::FrameBuffer *dest) {
		XE_ASSERT(src != dest);

		dummyMaterial->setTexture(src->getTexture());

		dest->bind();
		dest->clear();

		filter->setUniforms(dummyMaterial, dummyTransform, lightCamera);
		filter->updateUniforms();

		dummyMesh->render();

		dest->unbind();
	}

}}