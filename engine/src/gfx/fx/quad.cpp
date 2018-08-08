//
// Created by FLXR on 8/7/2018.
//

#include "quad.hpp"
#include "gfx/renderer.hpp"

namespace xe { namespace fx {

	Quad::Quad(uint width, uint height) :
			RenderEffect(width, height) { }

	Quad::~Quad() {
		delete vao;
	}

	void Quad::load() {
		loadPrograms();
		loadBuffers();
	}

	void Quad::unload() { }

	void Quad::reload() { }

	void Quad::loadPrograms() {

	}

	void Quad::loadBuffers() {
		vao = api::VertexArray::create();
	}

	void Quad::render() {
		vao->bind();
		vao->drawArrays(3);
		vao->unbind();
	}

	void Quad::renderBlendBlend() {
		Renderer::enableBlend(true);
		Renderer::setBlendEquation(BlendEquation::ADD);
		Renderer::setBlendFunction(BlendFunction::ONE, BlendFunction::ONE);

		render();

		Renderer::enableBlend(false);
	}

	void Quad::renderFullQuad() {
		vao->bind();
		vao->drawArrays(6);
		vao->unbind();
	}

	void Quad::renderFullQuadBlend() {
		Renderer::enableBlend(true);
		Renderer::setBlendEquation(BlendEquation::ADD);
		Renderer::setBlendFunction(BlendFunction::ONE, BlendFunction::ONE);

		renderFullQuad();

		Renderer::enableBlend(false);
	}

	void Quad::render3D(uint depth) {
		vao->bind();
		vao->drawArraysInstanced(3, depth);
		vao->unbind();
	}

}}
