//
// Created by FLXR on 9/1/2018.
//

#include <xe/gfx/fx/hdr.hpp>
#include <xe/resources/shadermanager.hpp>
#include <xe/gfx/renderer.hpp>

namespace xe { namespace fx {

	HDR::HDR(uint width, uint height) :
			RenderEffect(width, height) {

		createShaders();
		createTextures();

		static const vec2 defaultExposure(1000.0f, 0.0f);

		exposureSB = new StorageBuffer(sizeof(vec2));

		exposureSB->bind();
		exposureSB->update(&defaultExposure, sizeof(vec2));
		exposureSB->unbind();
	}

	HDR::~HDR() {
		delete luminosityTexture;
		delete tempScene;

		delete exposureSB;
	}

	void HDR::createTextures() {
		TextureParameters params(TextureTarget::Tex2D);
		params.internalFormat = PixelInternalFormat::R16f;
		params.format = PixelFormat::Red;
		params.pixelType = PixelType::Float;
		params.minFilter = TextureMinFilter::LinearMipMapLinear;
		params.magFilter = TextureMagFilter::Linear;
		params.wrap = TextureWrap::Clamp;
		params.mipMapLevels = MIP_MAP_AUTO;
		params.anisotropy = 0;

		luminosityTexture = new Texture("LuminosityTexture", width, height, 0, params);

		params.internalFormat = PixelInternalFormat::Rgba16f;
		params.format = PixelFormat::Rgba;
		params.minFilter = TextureMinFilter::Nearest;
		params.magFilter = TextureMagFilter::Nearest;
		params.mipMapLevels = 0;

		tempScene = new Texture("TempScene", width, height, 0, params);
	}

	void HDR::createShaders() {
		luminosityShader = GETSHADER("dLuminosity");
		autoExposureShader = GETSHADER("dAutoExposure");
		scaleSceneShader = GETSHADER("dScaleScene");

		//get samplers
		aeSampler0 = autoExposureShader->getSampler("sampler0");
		ssSampler0 = scaleSceneShader->getSampler("sampler0");
	}

	void HDR::calcExposure(const Texture *sceneTexture) {
		luminosity(sceneTexture);
		autoExposure();
	}

	void HDR::scaleScene(Quad *quad, const FrameBuffer *sceneFBO, const Texture *sceneTexture) {
		sceneTexture->copyTo(tempScene);

		sceneFBO->bindDraw(Attachment::Color0);

		Renderer::clear(RendererBufferColor);
		Renderer::setViewport(0, 0, width, height);

		scaleSceneShader->bind();
		tempScene->bind(ssSampler0);

		exposureSB->bind(0);
		quad->render();
		exposureSB->unbind(0);

		tempScene->unbind(ssSampler0);
		scaleSceneShader->unbind();

		sceneFBO->unbind();
	}

	void HDR::luminosity(const Texture *sceneTexture) {
		static constexpr uint wgSize = 32;
		static constexpr int32 unit0 = 0;
		static constexpr int32 unit1 = 1;

		luminosityShader->bind();

		sceneTexture->bindImageUnit(unit0, TextureAccess::ReadOnly);
		luminosityShader->setUniform("sampler0", &unit0, sizeof(int32));

		luminosityTexture->bindImageUnit(unit1, TextureAccess::WriteOnly);
		luminosityShader->setUniform("sampler1", &unit1, sizeof(int32));

		Renderer::dispatchCompute(sceneTexture->getWidth() / wgSize, sceneTexture->getHeight() / wgSize, 1);
		Renderer::setMemoryBarrier(MemBarrier::ShaderImageAccess);

		luminosityTexture->generateMipMaps(TextureTarget::Tex2D);

		sceneTexture->unbind(unit0);
		luminosityTexture->unbind(unit1);

		luminosityShader->unbind();
	}

	void HDR::autoExposure() {
		autoExposureShader->bind();

		const uint mipMap = luminosityTexture->getMaxMipMap();
		autoExposureShader->setUniform("luminosityLOD", &mipMap, sizeof(int32));

		exposureSB->bind(0);

		luminosityTexture->bind(aeSampler0);

		Renderer::dispatchCompute(1, 1, 1);
		Renderer::setMemoryBarrier(MemBarrier::ShaderStorage);

		luminosityTexture->unbind(aeSampler0);

		exposureSB->unbind(0);

		autoExposureShader->unbind();
	}

}}
