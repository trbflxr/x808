//
// Created by FLXR on 8/7/2018.
//


#include <xe/gfx/fx/quad.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/shadermanager.hpp>

namespace xe { namespace fx {

	Quad::Quad(uint width, uint height) :
			RenderEffect(width, height) {

		//buffers
		vec3 positions[] = {{-1.0f, 1.0f,  0.0f},
		                    {1.0f,  1.0f,  0.0f},
		                    {1.0f,  -1.0f, 0.0f},
		                    {-1.0f, -1.0f, 0.0f}};

		uint indices[] = {0, 1, 2, 0, 2, 3};

		vao = new VertexArray();

		VertexBuffer *buffer = new VertexBuffer();
		BufferLayout layout;
		layout.push<vec3>("POSITION");

		buffer->setLayout(layout);
		buffer->setData(4 * sizeof(vec3), positions);

		vao->pushBuffer(buffer);

		ibo = new IndexBuffer(indices, 6);


		//texture shaders
		renderTexture1D = GETSHADER("dRenderTexture1D");
		renderTexture2D = GETSHADER("dRenderTexture2D");
		renderTexture2DArray = GETSHADER("dRenderTexture2DArray");
		renderTexture3D = GETSHADER("dRenderTexture3D");

		if (Context::getRenderAPIVersion() >= 420) {
			renderTextureCube = GETSHADER("dRenderTextureCube");
			renderTextureCubeArray = GETSHADER("dRenderTextureCubeArray");
		}
	}

	Quad::~Quad() {
		delete vao;
		delete ibo;
	}

	void Quad::render() const {
		vao->bind();
		ibo->bind();

		vao->drawArrays(3, BeginMode::Triangles);

		ibo->unbind();
		vao->unbind();

		Renderer::incDC();
	}

	void Quad::renderBlend() const {
		Renderer::enableBlend(true);
		Renderer::setBlendEquation(BlendEquation::Add);
		Renderer::setBlendFunction(BlendFunction::One, BlendFunction::One);

		render();

		Renderer::enableBlend(false);
	}

	void Quad::renderFullQuad() const {
		vao->bind();
		ibo->bind();

		vao->drawArrays(6, BeginMode::Triangles);

		ibo->unbind();
		vao->unbind();

		Renderer::incDC();
	}

	void Quad::renderFullQuadBlend() const {
		Renderer::enableBlend(true);
		Renderer::setBlendEquation(BlendEquation::Add);
		Renderer::setBlendFunction(BlendFunction::One, BlendFunction::One);

		renderFullQuad();

		Renderer::enableBlend(false);
	}

	void Quad::render3D(uint depth) const {
		vao->bind();
		ibo->bind();

		vao->drawArraysInstanced(3, depth, BeginMode::Triangles);

		ibo->unbind();
		vao->unbind();

		Renderer::incDC();
	}

	void Quad::renderTexture(const Texture *texture, float size, int32 pos, int32 layer, int32 channel) {
		const float sizeX = width * size;
		const float sizeY = height * size;

		const float posX = width - sizeX;
		const float posY = sizeY * pos;

		const int32 l = static_cast<const int32>(math::clampf(layer, 0, texture->getDepth()));
		const int32 c = static_cast<const int32>(math::clampf(channel, -1, 3));

		Renderer::setViewport((uint) posX, (uint) posY, (uint) sizeX, (uint) sizeY);

		switch (texture->getTarget()) {
			case TextureTarget::Tex1D: {
				renderTexture(renderTexture1D, texture, 0, "", false);
				break;
			}

			case TextureTarget::Tex2D: {
				renderTexture(renderTexture2D, texture, c, "channel", false);
				break;
			}

			case TextureTarget::Tex3D: {
				renderTexture(renderTexture3D, texture, l, "layer", false);
				break;
			}

			case TextureTarget::Tex2DArray: {
				renderTexture(renderTexture2DArray, texture, l, "layer", false);
				break;
			}

			case TextureTarget::TexCubeMap: {
				renderTexture(renderTextureCube, texture, 0, "", true);
				break;
			}

			case TextureTarget::TexCubeMapArray: {
				renderTexture(renderTextureCubeArray, texture, l, "layer", true);
				break;
			}
		}
	}

	void Quad::renderTexture(const Shader *shader, const Texture *texture, int32 data, const char *uniform, bool fullQuad) {
		shader->bind();

		if (strlen(uniform) > 0) {
			shader->setUniform(uniform, &data, sizeof(int32));
			shader->updateUniforms();
		}

		const uint slot = shader->getSampler("sampler0");

		texture->bind(slot);

		fullQuad ? renderFullQuad() : render();

		texture->unbind(slot);

		shader->unbind();
	}

}}
