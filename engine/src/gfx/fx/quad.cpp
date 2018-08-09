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

		byte pChannel[sizeof(int32)];
		memcpy(pChannel, &channel, sizeof(int32));

		byte pLayer[sizeof(uint)];
		memcpy(pLayer, &layer, sizeof(uint));

		switch (texture->getTarget()) {
			case TextureTarget::Tex1D: {
				renderTexture1D->bind();
				texture->bind(renderTexture1D->getResources().front()->getRegister());
				render();
				renderTexture1D->unbind();
				break;
			}

			case TextureTarget::Tex2D: {
				renderTexture2D->bind();
				renderTexture2D->setUniform("channel", pChannel);
				texture->bind(renderTexture2D->getResources().front()->getRegister());
				render();
				renderTexture2D->unbind();
				break;
			}

			case TextureTarget::Tex3D: {
				renderTexture3D->bind();
				renderTexture3D->setUniform("layer", pLayer);
				texture->bind(renderTexture3D->getResources().front()->getRegister());
				render();
				renderTexture3D->unbind();
				break;
			}

			case TextureTarget::Tex2DArray: {
				renderTexture2DArray->bind();
				renderTexture2DArray->setUniform("layer", pLayer);
				texture->bind(renderTexture2DArray->getResources().front()->getRegister());
				render();
				renderTexture2DArray->unbind();
				break;
			}

			case TextureTarget::TexCubeMap: {
				renderTextureCube->bind();
				texture->bind(renderTextureCube->getResources().front()->getRegister());
				renderFullQuad();
				renderTextureCube->unbind();
				break;
			}

			case TextureTarget::TexCubeMapArray: {
				renderTextureCubeArray->bind();
				renderTextureCubeArray->setUniform("layer", pLayer);
				texture->bind(renderTextureCubeArray->getResources().front()->getRegister());
				renderFullQuad();
				renderTextureCubeArray->unbind();
				break;
			}
		}
	}

}}
