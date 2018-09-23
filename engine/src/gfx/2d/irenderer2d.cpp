//
// Created by FLXR on 9/6/2018.
//

#include <xe/gfx/2d/irenderer2d.hpp>

namespace xe {

#define RENDERER2D_VERTEX_SIZE sizeof(VertexData)

#define RENDERER2D_SPRITE_SIZE     (RENDERER2D_VERTEX_SIZE * 4)
#define RENDERER2D_BUFFER_SIZE     (RENDERER2D_SPRITE_SIZE * XE_RENDERER2D_MAX_SPRITES)
#define RENDERER2D_INDICES_SIZE    (XE_RENDERER2D_MAX_SPRITES * 6)

	IRenderer2D::IRenderer2D(uint width, uint height, Camera *camera) :
			maxTextureUnits(Context::getMaxTextureUnits()),
			width(width),
			height(height),
			camera(camera),
			indicesOffset(0),
			indicesSize(0) {

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

		indices = new uint[RENDERER2D_INDICES_SIZE];
		indexBuffer = new IndexBuffer();
	}

	IRenderer2D::~IRenderer2D() {
		delete shader;
		delete indexBuffer;
		delete vertexArray;

		delete[] indices;
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
			if (textures.size() >= maxTextureUnits) {
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

	void IRenderer2D::appendIndices(const uint *indices, uint size, uint offset) {
		if (indicesSize + size >= RENDERER2D_INDICES_SIZE) {
			releaseBuffer();
			flush();
			begin();
		}

		for (uint i = 0; i < size; ++i) {
			IRenderer2D::indices[i + indicesSize] = indices[i] + indicesOffset;
		}

		indicesSize += size;
		indicesOffset += offset;
	}

	void IRenderer2D::updateIndexBuffer() {
		indexBuffer->setData(indices, indicesSize);
	}

}
