//
// Created by FLXR on 9/6/2018.
//

#include <xe/gfx/2d/irenderer2d.hpp>

namespace xe {

#define RENDERER2D_VERTEX_SIZE sizeof(VertexData)

#define RENDERER2D_MAX_SPRITES     60000
#define RENDERER2D_SPRITE_SIZE     (RENDERER2D_VERTEX_SIZE * 4)
#define RENDERER2D_BUFFER_SIZE     (RENDERER2D_SPRITE_SIZE * RENDERER2D_MAX_SPRITES)
#define RENDERER2D_INDICES_SIZE    (RENDERER2D_MAX_SPRITES * 6)
#define RENDERER2D_MAX_TEXTURES    32

	IRenderer2D::IRenderer2D(uint width, uint height, Camera *camera) :
			width(width),
			height(height),
			camera(camera),
			indexCount(0) {

		transformationStack.emplace_back(1.0f);
		transformationBack = &transformationStack.back();

		VertexBuffer *buffer = new VertexBuffer(BufferUsage::DynamicDraw);
		buffer->resize(RENDERER2D_BUFFER_SIZE);

		BufferLayout layout;
		layout.push<vec3>("pos");
		layout.push<vec2>("uv");
		layout.push<float>("texId");
		layout.push<byte>("color", 4, true);

		buffer->setLayout(layout);

		vertexArray = new VertexArray();
		vertexArray->pushBuffer(buffer);

		uint *indices = new uint[RENDERER2D_INDICES_SIZE];

		uint offset = 0;
		for (uint i = 0; i < RENDERER2D_INDICES_SIZE; i += 6) {
			indices[i] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		indexBuffer = new IndexBuffer(indices, RENDERER2D_INDICES_SIZE);
		vertexArray->unbind();
	}

	IRenderer2D::~IRenderer2D() {
		delete shader;
		delete indexBuffer;
		delete vertexArray;
	}

	void IRenderer2D::updateCamera() {
		shader->setUniform("projection", camera->getProjection().elements, sizeof(mat4));
		shader->setUniform("view", camera->getView().elements, sizeof(mat4));
	}

	void IRenderer2D::push(const mat4 &matrix, bool override) {
		transformationStack.push_back(override ? matrix : transformationStack.back() * matrix);
		transformationBack = &transformationStack.back();
	}

	void IRenderer2D::pop() {
		if (transformationStack.size() > 1) {
			transformationStack.pop_back();
		}
		transformationBack = &transformationStack.back();
	}

	float IRenderer2D::submitTexture(const Texture *texture) {
		float result = 0.0f;
		bool found = false;

		for (uint i = 0; i < textures.size(); i++) {
			if (textures[i] == texture) {
				result = i + 1;
				found = true;
				break;
			}
		}

		if (!found) {
			if (textures.size() >= RENDERER2D_MAX_TEXTURES) {
				releaseBuffer();
				flush();
				begin();
			}
			textures.push_back(texture);
			result = textures.size();
		}

		return result;
	}

	void IRenderer2D::releaseBuffer() {
		vertexArray->getBuffer(0)->releasePointer();
		vertexArray->unbind();
	}

}
