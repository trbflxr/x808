//
// Created by FLXR on 8/8/2018.
//

#include <xe/gfx/renderer.hpp>
#include <xe/gfx/fx/final.hpp>

namespace xe { namespace fx {

	Final::Final(uint width, uint height) :
			RenderEffect(width, height),
			useFXAA_(true) {

		finalShader = new Shader("dFinalFX");

		static TextureParameters params;
		params.internalFormat = PixelInternalFormat::Rgba16f;
		params.format = PixelFormat::Rgba;
		params.pixelType = PixelType::Float;
		params.minFilter = TextureMinFilter::Linear;
		params.magFilter = TextureMagFilter::Linear;
		params.wrap = TextureWrap::Clamp;
		params.mipMapLevels = 0;
		params.anisotropy = 0;

		finalTexture = new Texture(width, height, 0, params);

		finalFBO = new FrameBuffer("FinalSceneFBO");
		finalFBO->load({std::make_pair(Attachment::Color0, finalTexture)});
	}

	Final::~Final() {
		delete finalShader;
		delete finalFBO;
		delete finalTexture;
	}

	void Final::useFXAA(bool enabled) {
		useFXAA_ = enabled;

		int32 fxaa = useFXAA_;
		finalShader->setUniform("useFXAA", &fxaa, sizeof(int32));
	}

	void Final::render(Quad *quad) const {
//		Renderer::clear(RendererBufferColor);
		Renderer::setViewport(0, 0, width, height);


		finalShader->bind();
		finalShader->updateUniforms();

		uint slot = finalShader->getSampler("sampler0");
		finalTexture->bind(slot);

		quad->render();

		finalTexture->unbind(slot);
		finalShader->unbind();
	}

}}
