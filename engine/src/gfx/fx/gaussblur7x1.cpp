//
// Created by FLXR on 8/11/2018.
//

#include "gaussblur7x1.hpp"

namespace xe { namespace fx {

	GaussBlur7x1::GaussBlur7x1(uint width, uint height) :
			RenderEffect(width, height) {

		shader = new Shader("defaultGaussBlur7x1FX");
	}

	GaussBlur7x1::~GaussBlur7x1() {
		delete shader;
	}

	void GaussBlur7x1::render(Quad *quad, api::Texture *srcTexture, api::FrameBufferOld *dest, const vec2 &scale) {
		if (!enabled) return;

		dest->bind();
		dest->clear(RendererBufferDepth);

		shader->bind();
		shader->setUniform("blurScale", &scale, sizeof(vec2));
		shader->updateUniforms();

		//bind to sampler0
		static uint slot = shader->getResource("sampler0");

		srcTexture->bind(slot);
		quad->render();
		srcTexture->unbind(slot);

		shader->unbind();

		dest->unbind();
	}

}}
