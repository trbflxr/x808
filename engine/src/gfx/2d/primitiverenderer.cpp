//
// Created by FLXR on 9/6/2018.
//

#include <xe/gfx/sprite.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/gfx/2d/primitiverenderer.hpp>

namespace xe {

	PrimitiveRenderer::PrimitiveRenderer(uint width, uint height, Camera *camera) :
			IRenderer2D(width, height, camera) {

		shader = new Shader("dPrimitiveRenderer");
	}

	void PrimitiveRenderer::begin() {
		Renderer::enableBlend(true);
		Renderer::setBlendFunction(BlendFunction::SourceAlpha, BlendFunction::OneMinusSourceAlpha);
		Renderer::setViewport(0, 0, width, height);

		vertexArray->bind();
		buffer = static_cast<VertexData *>(vertexArray->getBuffer(0)->getPointer());
	}

	void PrimitiveRenderer::end() {
		updateCamera();
		releaseBuffer();
	}

	void PrimitiveRenderer::flush() {
		shader->bind();
		shader->updateUniforms();

		for (uint i = 0; i < textures.size(); i++) {
			textures[i]->bind(i);
		}

		vertexArray->bind();
		indexBuffer->bind();

		vertexArray->drawElements(indexCount, BeginMode::Triangles);

		indexBuffer->unbind();
		vertexArray->unbind();

		for (uint i = 0; i < textures.size(); i++) {
			textures[i]->unbind(i);
		}

		shader->unbind();

		indexCount = 0;
		textures.clear();

		//increment draw calls
		Renderer::incDC();
	}

	void PrimitiveRenderer::drawLine(float x0, float y0, float x1, float y1, float z, uint color, float thickness) {
		static const std::vector<vec2> &uv = Sprite::getDefaultUVs();

		const vec2 normal = vec2::normalize(vec2(y1 - y0, -(x1 - x0))) * thickness;

		buffer->vertex = mat4::translateVec(*transformationBack, vec3(x0 + normal.x, y0 + normal.y, z));
		buffer->uv = uv[0];
		buffer->color = color;
		buffer++;

		buffer->vertex = mat4::translateVec(*transformationBack, vec3(x1 + normal.x, y1 + normal.y, z));
		buffer->uv = uv[1];
		buffer->color = color;
		buffer++;

		buffer->vertex = mat4::translateVec(*transformationBack, vec3(x1 - normal.x, y1 - normal.y, z));
		buffer->uv = uv[2];
		buffer->color = color;
		buffer++;

		buffer->vertex = mat4::translateVec(*transformationBack, vec3(x0 - normal.x, y0 - normal.y, z));
		buffer->uv = uv[3];
		buffer->color = color;
		buffer++;

		indexCount += 6;
	}

	void PrimitiveRenderer::drawLine(const vec2 &start, const vec2 &end, float z, uint color, float thickness) {
		drawLine(start.x, start.y, end.x, end.y, z, color, thickness);
	}

	void PrimitiveRenderer::drawRect(float x, float y, float width, float height, float z, uint color) {
		drawLine(x, y, x + width, y, z, color);
		drawLine(x + width, y, x + width, y + height, z, color);
		drawLine(x + width, y + height, x, y + height, z, color);
		drawLine(x, y + height, x, y, z, color);
	}

	void PrimitiveRenderer::drawRect(const vec2 &position, const vec2 &size, float z, uint color) {
		drawRect(position.x, position.y, size.x, size.y, z, color);
	}

	void PrimitiveRenderer::drawRect(const rect &rectangle, float z, uint color) {
		drawRect(rectangle.getMinBound(), rectangle.size * 2.0f, z, color);
	}

	void PrimitiveRenderer::fillRect(float x, float y, float width, float height, float z, uint color) {
		static const std::vector<vec2> &uv = Sprite::getDefaultUVs();

		const vec3 position(x, y, z);
		const vec2 size(width, height);

		vec3 vertex = *transformationBack * position;
		buffer->vertex = vertex;
		buffer->uv = uv[0];
		buffer->color = color;
		buffer++;

		vertex = *transformationBack * vec3(position.x + size.x, position.y, position.z);
		buffer->vertex = vertex;
		buffer->uv = uv[1];
		buffer->color = color;
		buffer++;

		vertex = *transformationBack * vec3(position.x + size.x, position.y + size.y, position.z);
		buffer->vertex = vertex;
		buffer->uv = uv[2];
		buffer->color = color;
		buffer++;

		vertex = *transformationBack * vec3(position.x, position.y + size.y, position.z);
		buffer->vertex = vertex;
		buffer->uv = uv[3];
		buffer->color = color;
		buffer++;

		indexCount += 6;
	}

	void PrimitiveRenderer::fillRect(const vec2 &position, const vec2 &size, float z, uint color) {
		fillRect(position.x, position.y, size.x, size.y, z, color);
	}

	void PrimitiveRenderer::fillRect(const rect &rectangle, float z, uint color) {
		fillRect(rectangle.getMinBound(), rectangle.size * 2.0f, z, color);
	}

}