//
// Created by FLXR on 8/8/2018.
//

#include "final.hpp"
#include "gfx/renderer.hpp"
#include "resources/shadermanager.hpp"

namespace xe { namespace fx {

	Final::Final(uint width, uint height) :
			RenderEffect(width, height) {

		finalShader = new Shader("defaultFinalFX");

		float fxaaSpanMax = 8.0f;
		float fxaaReduceMul = 1.0f / fxaaSpanMax;
		float fxaaReduceMin = 1.0f / (fxaaSpanMax * 16.0f);

		finalShader->setUniform("fxaaSpanMax", &fxaaSpanMax, sizeof(float));
		finalShader->setUniform("fxaaReduceMin", &fxaaReduceMin, sizeof(float));
		finalShader->setUniform("fxaaReduceMul", &fxaaReduceMul, sizeof(float));
	}

	Final::~Final() {
		delete finalShader;
	}

	void Final::render(Quad *quad, api::Texture *srcTexture, bool useFXAA) const {
		Renderer::setViewport(0, 0, width, height);
		Renderer::clear(RendererBufferDepth);

		int32 fxaa = useFXAA;

		finalShader->bind();
		finalShader->setUniform("useFXAA", &fxaa, sizeof(int32));
		finalShader->updateUniforms();

		//bind to sampler0
		static uint slot = finalShader->getResource("sampler0");

		srcTexture->bind(slot);
		quad->render();
		srcTexture->unbind(slot);

		finalShader->unbind();
	}

}}
