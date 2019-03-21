//
// Created by FLXR on 3/2/2019.
//

#include <xe/gfx/fx/finalfx.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/shadermanager.hpp>

namespace xe { namespace fx {

	FinalFX::FinalFX(uint width, uint height) :
			RenderEffect(width, height) {
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
	}

	FinalFX::~FinalFX() {
		delete finalFBO;
		delete finalTexture;
	}

	void FinalFX::render(const Quad *quad) const {
		Renderer::setViewport(0, 0, width, height);

		finalShader->bind();
		finalShader->updateUniforms();

		finalTexture->bind(sampler0);

		quad->render();

		finalTexture->unbind(sampler0);
		finalShader->unbind();
	}

}}
