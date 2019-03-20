//
// Created by FLXR on 8/7/2018.
//


#include <xe/gfx/quad.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/shadermanager.hpp>

namespace xe {

	Quad::Quad(uint width, uint height) :
			RenderEffect(width, height) {

		//buffers
		vec2 positions[] = {{-1.0f, 1.0f},
		                    {1.0f,  1.0f},
		                    {1.0f,  -1.0f},
		                    {-1.0f, -1.0f}};

		uint indices[] = {0, 1, 2, 0, 2, 3};

		VertexBuffer *buffer = new VertexBuffer();
		BufferLayout layout;
		layout.push<vec2>("pos");

		buffer->setLayout(layout);
		buffer->setData(4 * sizeof(vec2), positions);

		vao = new VertexArray();
		vao->pushBuffer(buffer);

		ibo = new IndexBuffer(indices, 6);

		renderTexture2D = GETSHADER("dRenderTexture2D");
		renderTexture2DArray = GETSHADER("dRenderTexture2DArray");
	}

	Quad::~Quad() {
		delete vao;
		delete ibo;
	}

	void Quad::render() const {
		vao->bind();
		ibo->bind();

		vao->drawElements(3, BeginMode::Triangles);

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

		vao->drawElements(6, BeginMode::Triangles);

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

	void Quad::renderTexture(const Texture *tex, float size, int32 pos, int32 data) {
		const float sizeX = width * size;
		const float sizeY = height * size;

		const float posX = width - sizeX;
		const float posY = sizeY * pos;

		Renderer::setViewport((uint) posX, (uint) posY, (uint) sizeX, (uint) sizeY);

		if (tex->getTarget() == TextureTarget::Tex2D) {
			const int32 c = static_cast<const int32>(math::clampf(data, -1, 3));
			renderTexture(renderTexture2D, tex, c, false);
		} else if (tex->getTarget() == TextureTarget::Tex2DArray) {
			const uint l = static_cast<uint>(math::clampf(data, 0, tex->getDepth()));
			renderTexture(renderTexture2DArray, tex, l, false);
		}
	}

	void Quad::renderTexture(const Shader *shader, const Texture *texture, int32 data, bool fullQuad) {
		shader->bind();

		shader->setUniform("data", &data, sizeof(int32));
		shader->updateUniforms();

		const uint slot = shader->getSampler("sampler0");

		texture->bind(slot);

		fullQuad ? renderFullQuad() : render();

		texture->unbind(slot);

		shader->unbind();
	}

}
