//
// Created by FLXR on 8/7/2018.
//

#include <gfx/api/texture.hpp>
#include <gfx/api/indexbuffer.hpp>
#include "quad.hpp"
#include "gfx/renderer.hpp"
#include "resources/shadermanager.hpp"

namespace xe { namespace fx {

	Quad::Quad(uint width, uint height) :
			RenderEffect(width, height) {

		vec3 positions[] = {{-1.0f, 1.0f,  0.0f},
		                    {1.0f,  1.0f,  0.0f},
		                    {1.0f,  -1.0f, 0.0f},
		                    {-1.0f, -1.0f, 0.0f}};

		uint indices[] = {0, 1, 2, 0, 2, 3};
		indicesCount = 6;

		vao = api::VertexArray::create();

		api::VertexBuffer *buffer = api::VertexBuffer::create();
		api::BufferLayout layout;
		layout.push<vec3>("POSITION");

		buffer->setLayout(layout);
		buffer->setData(4 * sizeof(vec3), positions);

		vao->pushBuffer(buffer);

		ibo = api::IndexBuffer::create(indices, indicesCount);
	}

	Quad::~Quad() {
		delete vao;
		delete ibo;
	}

	void Quad::render() const {
		vao->bind();
		ibo->bind();

		vao->drawElements(indicesCount, BeginMode::Triangles);

		ibo->unbind();
		vao->unbind();

		Renderer::incDC();
	}

	void Quad::render(BlendFunction src, BlendFunction dest, BlendEquation eq) const {
		Renderer::enableBlend(true);
		Renderer::setBlendEquation(eq);
		Renderer::setBlendFunction(src, dest);

		render();

		Renderer::enableBlend(false);
	}

}}
