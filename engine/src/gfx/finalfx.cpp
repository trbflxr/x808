//
// Created by FLXR on 3/2/2019.
//

#include <xe/gfx/finalfx.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/shadermanager.hpp>

namespace xe {


	FinalFX::FinalFX(uint width, uint height, bool fxaa) :
	RenderEffect(width,height){
		//fx final
		finalShader = GETSHADER("dFinalFX");
		sampler0 = finalShader->getSampler("sampler0");

		//texture
		TextureParameters params(TextureTarget::Tex2D);
		params.internalFormat = PixelInternalFormat::Rgba16f;
		params.format = PixelFormat::Rgba;
		params.pixelType = PixelType::Float;
		params.minFilter = TextureMinFilter::Nearest;
		params.magFilter = TextureMagFilter::Nearest;
		params.wrap = TextureWrap::Clamp;
		params.mipMapLevels = 0;
		params.anisotropy = 0;

		finalTexture = new Texture("finalFX", width, height, 0, params);

		finalFBO = new FrameBuffer("finalFBO");
		finalFBO->load({std::make_pair(Attachment::Color0, finalTexture)});

		//send fxaa flag to shader
		useFXAA(fxaa);
	}

	FinalFX::~FinalFX() {
		delete finalFBO;
		delete finalTexture;
	}

	void FinalFX::useFXAA(bool enabled) {
		fxaa = enabled;
		const int32 use = fxaa ? 1 : 0;

		finalShader->setUniform("useFXAA", &use, sizeof(int32));
	}

	void FinalFX::render(const Quad *quad) const {
		Renderer::clear(RendererBufferColor);
		Renderer::setViewport(0, 0, width, height);

		finalShader->bind();
		finalShader->updateUniforms();

		finalTexture->bind(sampler0);

		quad->render();

		finalTexture->unbind(sampler0);
		finalShader->unbind();
	}

}
