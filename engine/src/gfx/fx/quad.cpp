//
// Created by FLXR on 8/7/2018.
//

#include <gfx/api/texture.hpp>
#include "quad.hpp"
#include "gfx/renderer.hpp"
#include "resources/shadermanager.hpp"

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
		renderTexture1D = GETSHADER("defaultRenderTexture1D");
		renderTexture2D = GETSHADER("defaultRenderTexture2D");
		renderTexture2DArray = GETSHADER("defaultRenderTexture2DArray");
		renderTexture3D = GETSHADER("defaultRenderTexture3D");
		renderTextureCube = GETSHADER("defaultRenderTextureCube");
		renderTextureCubeArray = GETSHADER("defaultRenderTextureCubeArray");
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

	void Quad::renderToTexture(api::Texture *texture, float scale, uint pos, uint layer, int32 channel) {
		uint sizeX = static_cast<uint>(width * scale);
		uint sizeY = static_cast<uint>(height * scale);

		uint posX = width - sizeX;
		uint posY = sizeY * pos;

		Renderer::setViewport(posX, posY, sizeX, sizeY);

		layer = static_cast<uint>(math::clampf(layer, 0, texture->getDepth()));
		channel = static_cast<int32>(math::clampf(channel, -1, 3));

		switch (texture->getTarget()) {
			case api::TextureTarget::TEX1D: {
				renderTexture1D->bind();
				texture->bind(renderTexture1D->getResources().front()->getRegister());
				render();
				renderTexture1D->unbind();
				break;
			}

			case api::TextureTarget::TEX2D: {
				renderTexture2D->bind();
				renderTexture2D->setUniform("channel", (byte *) channel);
				texture->bind(renderTexture2D->getResources().front()->getRegister());
				render();
				renderTexture2D->unbind();
				break;
			}

			case api::TextureTarget::TEX3D: {
				renderTexture3D->bind();
				renderTexture3D->setUniform("layer", (byte *) layer);
				texture->bind(renderTexture3D->getResources().front()->getRegister());
				render();
				renderTexture3D->unbind();
				break;
			}

			case api::TextureTarget::TEX2D_ARRAY:{
				renderTexture2DArray->bind();
				renderTexture2DArray->setUniform("layer", (byte *) layer);
				texture->bind(renderTexture2DArray->getResources().front()->getRegister());
				render();
				renderTexture2DArray->unbind();
				break;
			}

			case api::TextureTarget::TEX_CUBE_MAP: {
				renderTextureCube->bind();
				texture->bind(renderTextureCube->getResources().front()->getRegister());
				renderFullQuad();
				renderTextureCube->unbind();
				break;
			}

			case api::TextureTarget::TEX_CUBE_MAP_ARRAY: {
				renderTextureCubeArray->bind();
				renderTextureCubeArray->setUniform("layer", (byte *) layer);
				texture->bind(renderTextureCubeArray->getResources().front()->getRegister());
				renderFullQuad();
				renderTextureCubeArray->unbind();
				break;
			}
		}
	}

}}
