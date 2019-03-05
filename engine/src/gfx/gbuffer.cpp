//
// Created by FLXR on 3/2/2019.
//

#include <xe/gfx/gbuffer.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/gfx/deferredrenderer.hpp>
#include <xe/resources/shadermanager.hpp>
#include <xe/resources/texturemanager.hpp>

namespace xe {

	GBuffer::GBuffer(uint width, uint height, DeferredRenderer *renderer) :
			width(width),
			height(height),
			renderSize(width, height),
			renderer(renderer),
			cullTest(true),
			drawWireframe(false),
			drawLightObjects(false),
			drawLightBounds(false) {

		createShaders();
		createTextures();

		gBuffer = new FrameBuffer("GBuffer");
		gBuffer->load({std::make_pair(Attachment::DepthStencil, depthStencilTexture),
		               std::make_pair(Attachment::Color0, diffuseTexture),
		               std::make_pair(Attachment::Color1, normalTexture),
		               std::make_pair(Attachment::Color2, specularTexture),
		               std::make_pair(Attachment::Color3, positionTexture),
		               std::make_pair(Attachment::Color6, lightDiffuseTexture),
		               std::make_pair(Attachment::Color7, lightSpecularTexture)});
	}

	GBuffer::~GBuffer() {
		delete depthStencilTexture;
		delete diffuseTexture;
		delete normalTexture;
		delete specularTexture;
		delete positionTexture;
		delete lightDiffuseTexture;
		delete lightSpecularTexture;

		delete gBuffer;
	}

	void GBuffer::createTextures() {
		TextureParameters params(TextureTarget::Tex2D);
		params.internalFormat = PixelInternalFormat::Depth32fStencil8;
		params.format = PixelFormat::DepthComponent;
		params.pixelType = PixelType::Float;
		params.minFilter = TextureMinFilter::Nearest;
		params.magFilter = TextureMagFilter::Nearest;
		params.wrap = TextureWrap::Clamp;
		params.mipMapLevels = 0;
		params.anisotropy = 0;

		depthStencilTexture = new Texture("GBufferDepthStencil", width, height, 0, params);

		params.internalFormat = PixelInternalFormat::Rgba16f;
		params.format = PixelFormat::Rgba;
		diffuseTexture = new Texture("GBufferDiffuse", width, height, 0, params);
		specularTexture = new Texture("GBufferSpecular", width, height, 0, params);
		lightSpecularTexture = new Texture("GBufferLightSpecular", width, height, 0, params);

		params.internalFormat = PixelInternalFormat::Rgb16f;
		params.format = PixelFormat::Rgb;
		normalTexture = new Texture("GBufferNormal", width, height, 0, params);
		positionTexture = new Texture("GBufferPosition", width, height, 0, params);
		lightDiffuseTexture = new Texture("GBufferLightDiffuse", width, height, 0, params);
	}

	void GBuffer::createShaders() {
		geometryShader = GETSHADER("dGeomShader");
		stencilShader = GETSHADER("dStencil");
		accumulationShader = GETSHADER("dAccumulation");
		spotShader = GETSHADER("dSpotLight");
		pointShader = GETSHADER("dPointLight");

		geometryShader->bindUniformBlock("Camera", 1);
		stencilShader->bindUniformBlock("Camera", 1);
		spotShader->bindUniformBlock("Camera", 1);
		pointShader->bindUniformBlock("Camera", 1);
	}

	void GBuffer::passGeometry(const std::vector<Model *> &models, const std::vector<Light *> &lights) const {
		static Attachment attachments[2] = {Attachment::Color6,
		                                    Attachment::Color7};

		gBuffer->bindDraw(attachments, 2);

		Renderer::setViewport(0, 0, width, height);
		Renderer::clear(RendererBufferColor);

		//fill gbuffer
		passGeometryInternal(models, lights);

		//accumulate lighting
		Renderer::enableStencilTest(true);
		Renderer::enableBlend(true);
		Renderer::setBlendEquation(BlendEquation::Add);
		Renderer::setBlendFunction(BlendFunction::One, BlendFunction::One);

		for (const auto &light : lights) {
			switch (light->getType()) {
				case LightType::Spot: {
					passStencil(light);
					passSpotLight(dynamic_cast<const SpotLight *>(light));
					break;
				}

				case LightType::Point: {
					passStencil(light);
					passPointLight(dynamic_cast<const PointLight *>(light));
					break;
				}

				default: break;
			}
		}

		gBuffer->unbind();
	}

	void GBuffer::passLightAccumulation(const Quad *quad, const FrameBuffer *final) const {
		final->bindDraw(Attachment::Color0);

		Renderer::clear(RendererBufferColor);

		accumulationShader->bind();

		const uint d = accumulationShader->getSampler("sampler0");
		const uint ld = accumulationShader->getSampler("sampler1");
		const uint sl = accumulationShader->getSampler("sampler2");

		diffuseTexture->bind(d);
		lightDiffuseTexture->bind(ld);
		lightSpecularTexture->bind(sl);

		accumulationShader->updateUniforms();
		quad->render();

		lightSpecularTexture->unbind(sl);
		lightDiffuseTexture->unbind(ld);
		diffuseTexture->unbind(d);

		accumulationShader->unbind();

		final->unbind();
	}

	void GBuffer::passGeometryInternal(const std::vector<Model *> &models, const std::vector<Light *> &lights) const {
		static Attachment attachments[4] = {Attachment::Color0,
		                                    Attachment::Color1,
		                                    Attachment::Color2,
		                                    Attachment::Color3};

		static constexpr int32 disabled = 0;
		const int32 ct = cullTest ? 1 : 0;
		const int32 wf = drawWireframe ? 1 : 0;

		gBuffer->bindDraw(attachments, 4);

		Renderer::clear(RendererBufferColor | RendererBufferDepth);

		geometryShader->bind();

		geometryShader->setUniform("cullTest", &ct, sizeof(int32));
		geometryShader->setUniform("enableWireframe", &wf, sizeof(int32));
		geometryShader->setUniform("renderSize", &renderSize, sizeof(vec2));

		renderer->renderModels(BeginMode::Triangles, geometryShader, models);

		if (drawLightObjects) {
			geometryShader->setUniform("cullTest", &disabled, sizeof(int32));
			renderer->renderLights(BeginMode::Triangles, geometryShader, lights);
		}

		geometryShader->unbind();
	}

	void GBuffer::passStencil(const Light *light) const {
		gBuffer->bindDrawAttachment(Attachment::None);

		Renderer::enableDepthMask(false);
		Renderer::enableDepthTesting(true);
		Renderer::enableCullFace(false);
		Renderer::clear(RendererBufferStencil);

		Renderer::setStencilFunc(StencilFunction::Always, 0, 0);
		Renderer::setStencilOpSeparate(StencilFace::Back, StencilOp::Keep, StencilOp::IncrWrap, StencilOp::Keep);
		Renderer::setStencilOpSeparate(StencilFace::Front, StencilOp::Keep, StencilOp::DecrWrap, StencilOp::Keep);

		stencilShader->bind();

		renderer->renderLightBounds(stencilShader, light);

		stencilShader->unbind();
	}

	void GBuffer::passSpotLight(const SpotLight *light) const {
		static Attachment attachments[2] = {Attachment::Color6,
		                                    Attachment::Color7};

		gBuffer->bindDrawAttachments(attachments, 2);

		Renderer::setStencilFunc(StencilFunction::Notequal, 0, 0xFF);

		Renderer::enableDepthTesting(false);
		Renderer::enableCullFace(true);
		Renderer::setCullFace(CullFace::Front);

		spotShader->bind();
		const uint n = spotShader->getSampler("sampler0");
		const uint s = spotShader->getSampler("sampler1");
		const uint p = spotShader->getSampler("sampler2");

		normalTexture->bind(n);
		specularTexture->bind(s);
		positionTexture->bind(p);

		const vec3 &pos = light->getPosition();
		const vec3 &look = light->getRotation().getForward();
		const vec3 &color = light->getColor();
		const float intensity = light->getIntensity();
		const float falloff = light->getFalloff();
		const float spotAngle = light->getSpotAngle();
		const float spotBlur = light->getSpotBlur();

		//light uniforms
		spotShader->setUniform("lightPosition", &pos, sizeof(vec3));
		spotShader->setUniform("lightColor", &color, sizeof(vec3));
		spotShader->setUniform("lightIntensity", &intensity, sizeof(float));
		spotShader->setUniform("lightFalloff", &falloff, sizeof(float));

		//spot light uniforms
		spotShader->setUniform("lightDirection", &look, sizeof(vec3));
		spotShader->setUniform("lightSpotAngle", &spotAngle, sizeof(float));
		spotShader->setUniform("lightSpotBlur", &spotBlur, sizeof(float));

		renderer->renderLightBounds(spotShader, light);

		specularTexture->unbind(s);
		normalTexture->unbind(n);
		positionTexture->unbind(p);

		spotShader->unbind();
	}

	void GBuffer::passPointLight(const PointLight *light) const {
		static Attachment attachments[2] = {Attachment::Color6,
		                                    Attachment::Color7};

		gBuffer->bindDrawAttachments(attachments, 2);

		Renderer::setStencilFunc(StencilFunction::Notequal, 0, 0xFF);

		Renderer::enableDepthTesting(false);
		Renderer::enableCullFace(true);
		Renderer::setCullFace(CullFace::Back);

		pointShader->bind();
		const uint n = pointShader->getSampler("sampler0");
		const uint s = pointShader->getSampler("sampler1");
		const uint p = pointShader->getSampler("sampler2");

		normalTexture->bind(n);
		specularTexture->bind(s);
		positionTexture->bind(p);

		const vec3 &pos = light->getPosition();
		const vec3 &color = light->getColor();
		const float intensity = light->getIntensity();
		const float falloff = light->getFalloff();

		//light uniforms
		pointShader->setUniform("lightPosition", &pos, sizeof(vec3));
		pointShader->setUniform("lightColor", &color, sizeof(vec3));
		pointShader->setUniform("lightIntensity", &intensity, sizeof(float));
		pointShader->setUniform("lightFalloff", &falloff, sizeof(float));

		renderer->renderLightBounds(pointShader, light);

		specularTexture->unbind(s);
		normalTexture->unbind(n);
		positionTexture->unbind(p);

		pointShader->unbind();
	}

}
