//
// Created by FLXR on 3/2/2019.
//

#include <xe/gfx/gbuffer.hpp>
#include <xe/resources/shadermanager.hpp>
#include <xe/resources/texturemanager.hpp>
#include <xe/gfx/renderer.hpp>

namespace xe {

	GBuffer::GBuffer(uint width, uint height) :
			width(width),
			height(height),
			renderSize(width, height),
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

		Renderer::enableBlend(false);
		Renderer::enableStencilTest(false);
		Renderer::enableCullFace(true);
		Renderer::setCullFace(CullFace::Back);

		gBuffer->unbind();
	}

	void GBuffer::passLightAccumulation(const Quad *quad, const FrameBuffer *final) const {
		final->bindDraw(Attachment::Color0);

		Renderer::clear(RendererBufferColor);
		Renderer::setViewport(0, 0, width, height);

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
		Renderer::setViewport(0, 0, width, height);

		geometryShader->bind();

		geometryShader->setUniform("cullTest", &ct, sizeof(int32));
		geometryShader->setUniform("enableWireframe", &wf, sizeof(int32));
		geometryShader->setUniform("renderSize", &renderSize, sizeof(vec2));

		renderModels(BeginMode::Triangles, geometryShader, models);

		if (drawLightObjects) {
			geometryShader->setUniform("cullTest", &disabled, sizeof(int32));
			renderLights(BeginMode::Triangles, geometryShader, lights);
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

		renderLightBounds(stencilShader, light);

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

		renderLightBounds(spotShader, light);

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

		renderLightBounds(pointShader, light);

		specularTexture->unbind(s);
		normalTexture->unbind(n);
		positionTexture->unbind(p);

		pointShader->unbind();
	}

	void GBuffer::renderModels(BeginMode mode, const Shader *shader, const std::vector<Model *> &models) const {
		for (const auto &m : models) {
			const mat4 &model = m->toMatrix();

			//world matrix
			shader->setUniform("model", &model, sizeof(mat4));

			const Material *mt = m->getMaterial();

			const vec3 &diffuseColor = mt->getDiffuseColor();
			const vec3 &specularColor = mt->getSpecularColor();
			const float emission = mt->getEmission();
			const float specularShininess = mt->getSpecularShininess();
			const float displacementStrength = mt->getDisplacementStrength();


			//set mesh uniforms
			shader->setUniform("diffuseColor", &diffuseColor, sizeof(vec3));
			shader->setUniform("emissionStrength", &emission, sizeof(float));
			shader->setUniform("specularColor", &specularColor, sizeof(vec3));
			shader->setUniform("specularShininess", &specularShininess, sizeof(float));
			shader->setUniform("displacementStrength", &displacementStrength, sizeof(float));

			//textures
			int32 df = setTexture(shader, mt->getDiffuse(), "diffuseTexture", "enableDiffuseTexture");
			int32 sp = setTexture(shader, mt->getSpecular(), "specularTexture", "enableSpecularTexture");
			int32 nr = setTexture(shader, mt->getNormal(), "normalTexture", "enableNormalTexture");
			int32 ds = setTexture(shader, mt->getDisplacement(), "dispTexture", "enableDispTexture");
			int32 pr = setTexture(shader, mt->getParallax(), "parallaxTexture", "enableParallaxTexture");

			shader->updateUniforms();
			m->render(mode);

			if (df != -1) mt->getDiffuse()->unbind(df);
			if (sp != -1) mt->getSpecular()->unbind(sp);
			if (nr != -1) mt->getNormal()->unbind(nr);
			if (ds != -1) mt->getDisplacement()->unbind(ds);
			if (pr != -1) mt->getParallax()->unbind(pr);
		}
	}

	void GBuffer::renderLights(BeginMode mode, const Shader *shader, const std::vector<Light *> &lights) const {
		static constexpr int32 disabled = 0;

		for (const auto &light : lights) {
			if (!light->getMesh()) continue;

			//transform
			const mat4 model = light->toMatrix();
			shader->setUniform("model", &model, sizeof(mat4));

			//values
			shader->setUniform("diffuseColor", &light->getColor(), sizeof(vec3));
			shader->setUniform("emissionStrength", &disabled, sizeof(float));
			shader->setUniform("specularColor", &vec3::Zero(), sizeof(vec3));
			shader->setUniform("specularShininess", &disabled, sizeof(float));
			shader->setUniform("displacementStrength", &disabled, sizeof(float));

			//disable textures
			shader->setUniform("enableDiffuseTexture", &disabled, sizeof(int32));
			shader->setUniform("enableSpecularTexture", &disabled, sizeof(int32));
			shader->setUniform("enableNormalTexture", &disabled, sizeof(int32));
			shader->setUniform("enableDispTexture", &disabled, sizeof(int32));
			shader->setUniform("enableParallaxTexture", &disabled, sizeof(int32));

			//set cull face for light object
			if (light->getType() == LightType::Spot) {
				Renderer::setCullFace(CullFace::Back);
			} else {
				Renderer::setCullFace(CullFace::Front);
			}

			//render
			shader->updateUniforms();
			light->getMesh()->render(mode);

			//display bounds
			if (drawLightBounds) {
				Renderer::enableCullFace(false);
				Renderer::setPolygonMode(MaterialFace::FrontAndBack, PolygonMode::Line);

				renderLightBounds(shader, light);

				Renderer::setPolygonMode(MaterialFace::FrontAndBack, PolygonMode::Fill);
				Renderer::enableCullFace(true);
			}
		}

		Renderer::setCullFace(CullFace::Back);
	}

	void GBuffer::renderLightBounds(const Shader *shader, const Light *light) const {
		const mat4 &model = light->toMatrix().clearScale() * light->getBoundsMatrix();

		shader->setUniform("model", &model, sizeof(mat4));
		shader->updateUniforms();

		light->getMesh()->render(BeginMode::Triangles);
	}

	int32 GBuffer::setTexture(const Shader *shader, const Texture *t, const char *sampler, const char *enable) const {
		static constexpr int32 enabled = 1;
		static constexpr int32 disabled = 0;

		if (!t) {
			shader->setUniform(enable, &disabled, sizeof(int32));
			return -1;
		}

		shader->setUniform(enable, &enabled, sizeof(int32));

		const uint slot = shader->getSampler(sampler);
		t->bind(slot);

		return slot;
	}

}
