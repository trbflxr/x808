//
// Created by FLXR on 8/8/2018.
//

#include <xe/gfx/renderer.hpp>
#include <xe/gfx/fx/final.hpp>
#include <xe/resources/shadermanager.hpp>

namespace xe { namespace fx {

	Final::Final(uint width, uint height, bool useFXAA) :
			RenderEffect(width, height) {

		//fx final
		BaseShader *finalFX = new BaseShader("dFinalFX", {
				ShaderFile::fromSource(ShaderType::Vert, ShaderManager::getSource("commonGeneric_vert")),
				ShaderFile::fromSource(ShaderType::Frag, ShaderManager::getSource("finalScene_frag"),
				                       {ShaderManager::getSource("fxaa_include")})
		});
		ShaderManager::add(finalFX);
		finalShader = new Shader(finalFX);
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

		finalTexture = new Texture("FinalTexture", width, height, 0, params);

		finalFBO = new FrameBuffer("FinalSceneFBO");
		finalFBO->load({std::make_pair(Attachment::Color0, finalTexture)});

		//send fxaa flag to shader
		Final::useFXAA(useFXAA);
	}

	Final::~Final() {
		delete finalShader;
		delete finalFBO;
		delete finalTexture;
	}

	void Final::useFXAA(bool enabled) {
		useFXAA_ = enabled;
		int32 use = useFXAA_ ? 1 : 0;

		finalShader->setUniform("useFXAA", &use, sizeof(int32));
	}

	void Final::render(Quad *quad) const {
		Renderer::clear(RendererBufferColor);
		Renderer::setViewport(0, 0, width, height);

		finalShader->bind();
		finalShader->updateUniforms();

		finalTexture->bind(sampler0);

		quad->render();

		finalTexture->unbind(sampler0);
		finalShader->unbind();
	}

}}
