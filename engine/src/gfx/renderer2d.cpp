//
// Created by FLXR on 6/29/2018.
//

#include "renderer2d.hpp"
#include "renderer.hpp"
#include "api/basicshader.hpp"
#include "glcommon.hpp"

#define RENDERER_MAX_SPRITES    60000
#define RENDERER_SPRITE_SIZE    (RENDERER_VERTEX_SIZE * 4)
#define RENDERER_BUFFER_SIZE    RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE    (RENDERER_MAX_SPRITES * 6)
#define RENDERER_MAX_TEXTURES    (32 - 1)


xe::gfx::Renderer2D::Renderer2D(uint width, uint height) :
		indexCount(0),
		screenSize(width, height),
		viewportSize(width, height) {

	init();
}

xe::gfx::Renderer2D::Renderer2D(const xe::vec2u &screenSize) :
		indexCount(0),
		screenSize(screenSize),
		viewportSize(screenSize) {

	init();
}

xe::gfx::Renderer2D::~Renderer2D() {
	delete indexBuffer;
	delete vertexArray;
	delete screenQuad;
}

void xe::gfx::Renderer2D::init() {
	transformationStack.emplace_back(1.0f);
	transformationBack = &transformationStack.back();

	shader = new api::BasicShader();

//	todo: set system uniforms

	setCamera(new Camera(math::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f)));

	shader->bind();

	api::VertexBuffer *buffer = new api::VertexBuffer(api::BufferType::DYNAMIC);
	buffer->resize(RENDERER_BUFFER_SIZE);

	api::BufferLayout layout;
	layout.push<vec3>("POSITION"); // Position
	layout.push<vec2>("TEXCOORD"); // UV
	layout.push<float>("ID"); // Texture Index
	layout.push<byte>("COLOR", 4, true); // Color
	buffer->setLayout(layout);

	vertexArray = new api::VertexArray();
	vertexArray->pushBuffer(buffer);

	uint *indices = new uint[RENDERER_INDICES_SIZE];

	uint offset = 0;
	for (uint i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
		indices[i] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	indexBuffer = new api::IndexBuffer(indices, RENDERER_INDICES_SIZE);
	vertexArray->unbind();
}

void xe::gfx::Renderer2D::push(const xe::mat4 &matrix, bool override) {
	transformationStack.push_back(override ? matrix : transformationStack.back() * matrix);
	transformationBack = &transformationStack.back();
}

void xe::gfx::Renderer2D::pop() {
	if (transformationStack.size() > 1) {
		transformationStack.pop_back();
	}
	transformationBack = &transformationStack.back();
}

void xe::gfx::Renderer2D::setCamera(xe::gfx::Camera *camera) {
	Renderer2D::camera = camera;

	//todo: copy matrices to uniforms
}

void xe::gfx::Renderer2D::begin() {
	Renderer::get().setViewport(0, 0, screenSize.x, screenSize.y);

	vertexArray->bind();
	buffer = vertexArray->getBuffer()->getPointer<VertexData>();
}

void xe::gfx::Renderer2D::submit(xe::gfx::Renderable2D *renderable) {
	if (!renderable->isVisible()) return;

	const vec3 size = vec3(renderable->getSize());

	const vec3 min = renderable->getTransform().getPosition();
	const vec3 max = min+size;

	const uint color = renderable->getColor();
	const std::vector<vec2> &uv = renderable->getUVs();
	const api::Texture *texture = renderable->getTexture();

	float textureSlot = 0.0f;
	if (texture) {
		textureSlot = submitTexture(renderable->getTexture());
	}

	vec3 vertex = *transformationBack * min;
	buffer->vertex = vertex;
	buffer->uv = uv[0];
	buffer->tid = textureSlot;
	buffer->color = color;
	buffer++;

	vertex = *transformationBack * vec3(max.x, min.y);
	buffer->vertex = vertex;
	buffer->uv = uv[1];
	buffer->tid = textureSlot;
	buffer->color = color;
	buffer++;

	vertex = *transformationBack * vec3(max);
	buffer->vertex = vertex;
	buffer->uv = uv[2];
	buffer->tid = textureSlot;
	buffer->color = color;
	buffer++;

	vertex = *transformationBack * vec3(min.x, max.y);
	buffer->vertex = vertex;
	buffer->uv = uv[3];
	buffer->tid = textureSlot;
	buffer->color = color;
	buffer++;

	indexCount += 6;
}

void xe::gfx::Renderer2D::end() {
	vertexArray->getBuffer()->releasePointer();
	vertexArray->unbind();
}

void xe::gfx::Renderer2D::flush() {

	Renderer::get().setDepthTesting(false);

	shader->bind();

	//todo: set system uniforms
	shader->updateUniforms(*camera);

	for (uint i = 0; i < textures.size(); i++) {
		textures[i]->bind(i);
	}

	vertexArray->bind();
	indexBuffer->bind();

	vertexArray->draw(indexCount);

	indexBuffer->unbind();
	vertexArray->unbind();

	for (uint i = 0; i < textures.size(); i++) {
		textures[i]->unbind(i);
	}

	indexCount = 0;
}

void xe::gfx::Renderer2D::drawLine(float x0, float y0, float x1, float y1, uint color, float thickness) {
	const std::vector<vec2> &uv = Renderable2D::getDefaultUVs();
	float ts = 0.0f;

	vec2 normal = math::normalize(vec2(y1 - y0, -(x1 - x0))) * thickness;

	vec3 vertex = *transformationBack * vec3(x0 + normal.x, y0 + normal.y, 0.0f);
	buffer->vertex = vertex;
	buffer->uv = uv[0];
	buffer->tid = ts;
	buffer->color = color;
	buffer++;

	vertex = *transformationBack * vec3(x1 + normal.x, y1 + normal.y, 0.0f);
	buffer->vertex = vertex;
	buffer->uv = uv[1];
	buffer->tid = ts;
	buffer->color = color;
	buffer++;

	vertex = *transformationBack * vec3(x1 - normal.x, y1 - normal.y, 0.0f);
	buffer->vertex = vertex;
	buffer->uv = uv[2];
	buffer->tid = ts;
	buffer->color = color;
	buffer++;

	vertex = *transformationBack * vec3(x0 - normal.x, y0 - normal.y, 0.0f);
	buffer->vertex = vertex;
	buffer->uv = uv[3];
	buffer->tid = ts;
	buffer->color = color;
	buffer++;

	indexCount += 6;
}

void xe::gfx::Renderer2D::drawLine(const xe::vec2 &start, const xe::vec2 &end, uint color, float thickness) {
	drawLine(start.x, start.y, end.x, end.y, color, thickness);
}

void xe::gfx::Renderer2D::drawRect(float x, float y, float width, float height, uint color) {
	drawLine(x, y, x + width, y, color);
	drawLine(x + width, y, x + width, y + height, color);
	drawLine(x + width, y + height, x, y + height, color);
	drawLine(x, y + height, x, y, color);
}

void xe::gfx::Renderer2D::drawRect(const xe::vec2 &position, const xe::vec2 &size, uint color) {
	drawRect(position.x, position.y, size.x, size.y, color);
}

void xe::gfx::Renderer2D::drawRect(const xe::rect &rectangle, uint color) {
	drawRect(rectangle.getMinBound(), rectangle.size * 2.0f, color);
}

void xe::gfx::Renderer2D::fillRect(float x, float y, float width, float height, uint color) {
	vec3 position(x, y, 0.0f);
	vec2 size(width, height);
	const std::vector<vec2> &uv = Renderable2D::getDefaultUVs();

	float ts = 0.0f;

	vec3 vertex = *transformationBack * position;
	buffer->vertex = vertex;
	buffer->uv = uv[0];
	buffer->tid = ts;
	buffer->color = color;
	buffer++;

	vertex = *transformationBack * vec3(position.x + size.x, position.y, position.z);
	buffer->vertex = vertex;
	buffer->uv = uv[1];
	buffer->tid = ts;
	buffer->color = color;
	buffer++;

	vertex = *transformationBack * vec3(position.x + size.x, position.y + size.y, position.z);
	buffer->vertex = vertex;
	buffer->uv = uv[2];
	buffer->tid = ts;
	buffer->color = color;
	buffer++;

	vertex = *transformationBack * vec3(position.x, position.y + size.y, position.z);
	buffer->vertex = vertex;
	buffer->uv = uv[3];
	buffer->tid = ts;
	buffer->color = color;
	buffer++;

	indexCount += 6;
}

void xe::gfx::Renderer2D::fillRect(const xe::vec2 &position, const xe::vec2 &size, uint color) {
	fillRect(position.x, position.y, size.x, size.y, color);
}

void xe::gfx::Renderer2D::fillRect(const xe::rect &rectangle, uint color) {
	fillRect(rectangle.getMinBound(), rectangle.size * 2.0f, color);
}

float xe::gfx::Renderer2D::submitTexture(const xe::gfx::api::Texture *texture) {
	float result = 0.0f;
	bool found = false;

	for (uint i = 0; i < textures.size(); i++) {
		if (textures[i] == texture) {
			result = (float) (i + 1);
			found = true;
			break;
		}
	}

	if (!found) {
		if (textures.size() >= RENDERER_MAX_TEXTURES) {
			end();
			flush();
			begin();
		}
		textures.push_back(texture);
		result = (float) (textures.size());
	}
	return result;
}

