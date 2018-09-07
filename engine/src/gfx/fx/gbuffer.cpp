//
// Created by FLXR on 8/18/2018.
//

#include <xe/gfx/fx/gbuffer.hpp>
#include <xe/resources/shadermanager.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/gfx/scenerenderer.hpp>
#include <xe/gfx/defaultuniforms.hpp>

#include "xe/gfx/fx/gbuffer.hpp"

namespace xe { namespace fx {

	GBuffer::GBuffer(uint width, uint height) :
			RenderEffect(width, height),
			drawWireframe(false),
			drawLightObjects(false),
			drawLightBounds(false) {

		createShaders();
		createTextures();

		gBuffer = new FrameBuffer("GBuffer");
		gBuffer->load({std::make_pair(Attachment::DepthStencil, depthStencilTexture),
		               std::make_pair(Attachment::Color0, diffuseTexture),
		               std::make_pair(Attachment::Color1, normalDepthTexture),
		               std::make_pair(Attachment::Color2, specularTexture),
		               std::make_pair(Attachment::Color6, lightDiffuseTexture),
		               std::make_pair(Attachment::Color7, lightSpecularTexture)});
	}

	GBuffer::~GBuffer() {
		delete geometryShader;
		delete stencilShader;
		delete spotShader;
		delete pointShader;
		delete accumulationShader;

		delete depthStencilTexture;
		delete diffuseTexture;
		delete normalDepthTexture;
		delete specularTexture;
		delete lightDiffuseTexture;
		delete lightSpecularTexture;

		delete gBuffer;
	}

	void GBuffer::createTextures() {
		//textures
		static TextureParameters params(TextureTarget::Tex2D);
		params.internalFormat = PixelInternalFormat::Depth32fStencil8;
		params.format = PixelFormat::DepthComponent;
		params.pixelType = PixelType::Float;
		params.minFilter = TextureMinFilter::Linear;
		params.magFilter = TextureMagFilter::Linear;
		params.wrap = TextureWrap::Clamp;
		params.mipMapLevels = 0;
		params.anisotropy = 0;

		depthStencilTexture = new Texture("GBufferDepthStencil", width, height, 0, params);

		///
		params.internalFormat = PixelInternalFormat::Rgba16f;
		params.format = PixelFormat::Rgba;

		diffuseTexture = new Texture("GBufferDiffuse", width, height, 0, params);
		lightDiffuseTexture = new Texture("GBufferLightDiffuse", width, height, 0, params);
		lightSpecularTexture = new Texture("GBufferLightSpecular", width, height, 0, params);

		///
		params.internalFormat = PixelInternalFormat::Rgba16;
		params.format = PixelFormat::Rgba;

		specularTexture = new Texture("GBufferSpecular", width, height, 0, params);

		///
		params.internalFormat = PixelInternalFormat::Rgba32f;
		params.format = PixelFormat::Rgba;

		normalDepthTexture = new Texture("GBufferNormalDepth", width, height, 0, params);
	}

	void GBuffer::createShaders() {
		//includes
		std::vector<string> geomInclude{ShaderManager::getSource("1_cameraSpatials_ubo"),
		                                ShaderManager::getSource("gBufferFunctions_include"),
		                                ShaderManager::getSource("linearDepth_include")};

		std::vector<string> lightingInclude{ShaderManager::getSource("1_cameraSpatials_ubo"),
		                                    ShaderManager::getSource("lightingFunctions_include"),
		                                    ShaderManager::getSource("positionFromDepth_include"),
		                                    ShaderManager::getSource("linearDepth_include")};


		//shaders
		BaseShader *geomBase = new BaseShader("dGeomShader", {
				ShaderFile::fromSource(ShaderType::Vert, ShaderManager::getSource("geometry_vert")),

				ShaderFile::fromSource(ShaderType::TessControl, ShaderManager::getSource("gBufferGeometry_tesc"),
				                       {ShaderManager::getSource("1_cameraSpatials_ubo"),
				                        ShaderManager::getSource("culling_include")}),

				ShaderFile::fromSource(ShaderType::TessEval, ShaderManager::getSource("gBufferGeometry_tese")),

				ShaderFile::fromSource(ShaderType::Geom, ShaderManager::getSource("gBufferGeometry_geom"),
				                       {ShaderManager::getSource("1_cameraSpatials_ubo")}),

				ShaderFile::fromSource(ShaderType::Frag, ShaderManager::getSource("gBufferGeometry_frag"),
				                       {geomInclude})
		});
		geometryShader = new Shader(geomBase);


		BaseShader *stencilBase = new BaseShader("dStencil", {
				ShaderFile::fromSource(ShaderType::Vert, ShaderManager::getSource("gBufferStencil_vert"),
				                       {ShaderManager::getSource("1_cameraSpatials_ubo")})
		});
		stencilShader = new Shader(stencilBase);


		BaseShader *spotLightBase = new BaseShader("dSpotLight", {
				ShaderFile::fromSource(ShaderType::Vert, ShaderManager::getSource("gBufferStencil_vert"),
				                       {ShaderManager::getSource("1_cameraSpatials_ubo")}),

				ShaderFile::fromSource(ShaderType::Frag, ShaderManager::getSource("gBufferLightingSpot_frag"),
				                       {lightingInclude})
		});
		spotShader = new Shader(spotLightBase);


		BaseShader *pointLightBase = new BaseShader("dPointLight", {
				ShaderFile::fromSource(ShaderType::Vert, ShaderManager::getSource("gBufferStencil_vert"),
				                       {ShaderManager::getSource("1_cameraSpatials_ubo")}),

				ShaderFile::fromSource(ShaderType::Frag, ShaderManager::getSource("gBufferLightingPoint_frag"),
				                       {lightingInclude})
		});
		pointShader = new Shader(pointLightBase);


		BaseShader *accumulationBase = new BaseShader("dAccumulation", {
				ShaderFile::fromSource(ShaderType::Vert, ShaderManager::getSource("commonGeneric_vert")),
				ShaderFile::fromSource(ShaderType::Frag, ShaderManager::getSource("gBufferAccumulation_frag"))
		});
		accumulationShader = new Shader(accumulationBase);

	}

	void GBuffer::passDeferredShading(const Scene *scene) const {
		static Attachment attachments[2] = {Attachment::Color6,
		                                    Attachment::Color7};

		gBuffer->bindDraw(attachments, 2);

		Renderer::clear(RendererBufferColor);

		//fill gbuffer
		passGeometry(scene);

		//accumulate lighting
		Renderer::enableStencilTest(true);
		Renderer::enableBlend(true);
		Renderer::setBlendEquation(BlendEquation::Add);
		Renderer::setBlendFunction(BlendFunction::One, BlendFunction::One);

		for (const auto &light : scene->getLights()) {
			switch (light->getType()) {
				case Light::Type::Spot: {
					passStencil(light);
					passSpotLight((SpotLight *) light);
					break;
				}

				case Light::Type::Point: {
					passStencil(light);
					passPointLight((PointLight *) light);
					break;
				}

				default: break;
			}
		}

		Renderer::enableBlend(false);
		Renderer::enableStencilTest(false);
		Renderer::enableCullFace(true);
		Renderer::setCullFace(CullFace::Back);

		gBuffer->unbind();
	}

	void GBuffer::passLightAccumulation(Quad *quad, const FrameBuffer *finalScene) const {

		finalScene->bindDraw(Attachment::Color0);

		Renderer::clear(RendererBufferColor);
		Renderer::setViewport(0, 0, width, height);

		accumulationShader->bind();

		const uint dSlot = accumulationShader->getSampler("sampler0");
		const uint ldSlot = accumulationShader->getSampler("sampler1");
		const uint slSlot = accumulationShader->getSampler("sampler2");

		diffuseTexture->bind(dSlot);
		lightDiffuseTexture->bind(ldSlot);
		lightSpecularTexture->bind(slSlot);

		accumulationShader->updateUniforms();
		quad->render();

		lightSpecularTexture->unbind(slSlot);
		lightDiffuseTexture->unbind(ldSlot);
		diffuseTexture->unbind(dSlot);

		accumulationShader->unbind();

		finalScene->unbind();
	}

	void GBuffer::passGeometry(const Scene *scene) const {
		static Attachment attachments[4] = {Attachment::Color0,
		                                    Attachment::Color1,
		                                    Attachment::Color2};
		vec2 renderSize(width, height);


		gBuffer->bindDraw(attachments, 4);

		Renderer::clear(RendererBufferColor | RendererBufferDepth);
		Renderer::setViewport(0, 0, width, height);

		int32 enabled = drawWireframe ? 1 : 0;

		geometryShader->bind();
		geometryShader->setUniform("enableWireframe", &enabled, sizeof(int32));
		geometryShader->setUniform("renderSize", &renderSize, sizeof(vec2));

		scene->render(BeginMode::Patches, geometryShader, drawLightObjects, drawLightBounds);

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

		SceneRenderer::drawLightBounds(light, stencilShader);

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
		const uint ndSlot = spotShader->getSampler("sampler0");
		const uint sSlot = spotShader->getSampler("sampler1");

		normalDepthTexture->bind(ndSlot);
		specularTexture->bind(sSlot);

		const vec3 &pos = light->transform.getPosition();
		const vec3 &look = light->transform.getRotation().getForward();

		//light uniforms
		spotShader->setUniform(uniform::lightPosition, &pos, sizeof(vec3));
		spotShader->setUniform(uniform::lightColor, &light->color, sizeof(vec3));
		spotShader->setUniform(uniform::lightIntensity, &light->intensity, sizeof(float));
		spotShader->setUniform(uniform::lightFalloff, &light->falloff, sizeof(float));

		//spot light uniforms
		spotShader->setUniform(uniform::lightDirection, &look, sizeof(vec3));
		spotShader->setUniform(uniform::lightSpotAngle, &light->spotAngle, sizeof(float));
		spotShader->setUniform(uniform::lightSpotBlur, &light->spotBlur, sizeof(float));

		SceneRenderer::drawLightBounds(light, spotShader);

		specularTexture->unbind(sSlot);
		normalDepthTexture->unbind(ndSlot);

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
		const uint ndSlot = pointShader->getSampler("sampler0");
		const uint sSlot = pointShader->getSampler("sampler1");

		normalDepthTexture->bind(ndSlot);
		specularTexture->bind(sSlot);

		const vec3 &pos = light->transform.getPosition();

		//light uniforms
		pointShader->setUniform(uniform::lightPosition, &pos, sizeof(vec3));
		pointShader->setUniform(uniform::lightColor, &light->color, sizeof(vec3));
		pointShader->setUniform(uniform::lightIntensity, &light->intensity, sizeof(float));
		pointShader->setUniform(uniform::lightFalloff, &light->falloff, sizeof(float));

		SceneRenderer::drawLightBounds(light, pointShader);

		specularTexture->unbind(sSlot);
		normalDepthTexture->unbind(ndSlot);

		pointShader->unbind();
	}

}}