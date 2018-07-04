//
// Created by FLXR on 6/29/2018.
//

#include <freetype-gl/freetype-gl.h>
#include <algorithm>

#include "renderer2d.hpp"
#include "renderer.hpp"
#include "glcommon.hpp"
#include "resources/shaderfactory.hpp"

#define RENDERER_MAX_SPRITES    60000
#define RENDERER_SPRITE_SIZE    (RENDERER_VERTEX_SIZE * 4)
#define RENDERER_BUFFER_SIZE    RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE    (RENDERER_MAX_SPRITES * 6)
#define RENDERER_MAX_TEXTURES    (32 - 1)


const uint requiredSystemUniformsCount = 2;
const std::string requiredSystemUniforms[requiredSystemUniformsCount] = {
		"sys_ProjectionMatrix",
		"sys_ViewMatrix"};

const uint sys_ProjectionMatrixIndex = 0;
const uint sys_ViewMatrixIndex = 1;


uint xe::gfx::Renderer2D::dc = 0;

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

	systemUniforms.clear();
	systemUniformBuffers.clear();
}

void xe::gfx::Renderer2D::init() {
	transformationStack.emplace_back(1.0f);
	transformationBack = &transformationStack.back();

	systemUniforms.resize(requiredSystemUniformsCount);

	shader = sf::batchRendererShader();
	const api::ShaderUniformBufferVec &vssu = shader->getVSSystemUniforms();

	XE_ASSERT(vssu.size());

	for (auto &&ub : vssu) {
		UniformBuffer buffer(new byte[ub->getSize()], ub->getSize());
		systemUniformBuffers.push_back(buffer);

		for (auto &&uniform: ub->getUniforms()) {
			for (uint j = 0; j < requiredSystemUniformsCount; j++) {
				if (uniform->getName() == requiredSystemUniforms[j]) {
					systemUniforms[j] = R2DSysUniform(buffer, uniform->getOffset());
				}
			}
		}
	}

	//default camera
	setCamera(new Camera(math::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1, 1000)));

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

	memcpy(systemUniforms[sys_ProjectionMatrixIndex].buffer.buffer +
	       systemUniforms[sys_ProjectionMatrixIndex].offset,
	       &camera->getProjectionMatrix().elements, sizeof(mat4));

	memcpy(systemUniforms[sys_ViewMatrixIndex].buffer.buffer + systemUniforms[sys_ViewMatrixIndex].offset,
	       &camera->getViewMatrix().elements, sizeof(mat4));
}

void xe::gfx::Renderer2D::begin() {
	Renderer::get().setViewport(0, 0, screenSize.x, screenSize.y);

	vertexArray->bind();
	buffer = vertexArray->getBuffer()->getPointer<VertexData>();
}

void xe::gfx::Renderer2D::submit(const xe::gfx::Renderable2D *renderable) {
	if (!renderable->isVisible()) return;

	targets.push_back(renderable);
}

void xe::gfx::Renderer2D::submitInternal(const Renderable2D *renderable) {
	const std::array<vec2, 4> &vertices = renderable->bounds.getVertices();
	const uint color = renderable->color;
	const std::vector<vec2> &uv = renderable->UVs;
	const api::Texture *texture = renderable->texture;

	float textureSlot = 0.0f;
	if (texture) {
		textureSlot = submitTexture(renderable->texture);
	}

	buffer->vertex = math::translateVec(*transformationBack, vertices[0], renderable->getZIndex());
	buffer->uv = uv[0];
	buffer->tid = textureSlot;
	buffer->color = color;
	buffer++;

	buffer->vertex = math::translateVec(*transformationBack, vertices[3], renderable->getZIndex());
	buffer->uv = uv[1];
	buffer->tid = textureSlot;
	buffer->color = color;
	buffer++;

	buffer->vertex = math::translateVec(*transformationBack, vertices[2], renderable->getZIndex());
	buffer->uv = uv[2];
	buffer->tid = textureSlot;
	buffer->color = color;
	buffer++;

	buffer->vertex = math::translateVec(*transformationBack, vertices[1], renderable->getZIndex());
	buffer->uv = uv[3];
	buffer->tid = textureSlot;
	buffer->color = color;
	buffer++;

	indexCount += 6;
}

void xe::gfx::Renderer2D::submitText(const xe::gfx::Text *text) {
	Renderer2D::text.push_back(text);
}

void xe::gfx::Renderer2D::submitTextInternal(const xe::gfx::Text *text) {
	using namespace ftgl;

	const Font &font = *text->getFont();
	ftgl::texture_font_t *ftFont = font.getFTFont();
	const std::string &string = text->string;
	const uint color = text->textColor;
	const uint outlineColor = text->outlineColor;

	const api::Texture2D *texture = font.getTexture();
	XE_ASSERT(texture);

	const float tid = submitTexture(texture);
	const float scale = font.getSize() / text->size;

	float x = text->position.x;
	const float y = -text->position.y;

	if (ftFont->outline_thickness > 0) {
		for (uint i = 0; i < string.length(); i++) {
			auto *glyph = ftgl::texture_font_get_glyph(ftFont, string[i]);
			if (glyph) {

				if (i > 0) {
					float kerning = ftgl::texture_glyph_get_kerning(glyph, string[i - 1]);
					x += kerning / scale;
				}

				float x0 = x + glyph->offset_x / scale;
				float y0 = y - glyph->offset_y / scale;
				float x1 = x0 + glyph->width / scale;
				float y1 = y0 + glyph->height / scale;

				float s0 = glyph->s0;
				float t0 = glyph->t0;
				float s1 = glyph->s1;
				float t1 = glyph->t1;

				buffer->vertex = math::translateVec(*transformationBack, xe::vec2(x0, -y0));
				buffer->uv = xe::vec2(s0, t0);
				buffer->tid = tid;
				buffer->color = outlineColor;
				++buffer;

				buffer->vertex = math::translateVec(*transformationBack, xe::vec2(x0, -y1));
				buffer->uv = xe::vec2(s0, t1);
				buffer->tid = tid;
				buffer->color = outlineColor;
				++buffer;

				buffer->vertex = math::translateVec(*transformationBack, xe::vec2(x1, -y1));
				buffer->uv = xe::vec2(s1, t1);
				buffer->tid = tid;
				buffer->color = outlineColor;
				++buffer;

				buffer->vertex = math::translateVec(*transformationBack, xe::vec2(x1, -y0));
				buffer->uv = xe::vec2(s1, t0);
				buffer->tid = tid;
				buffer->color = outlineColor;
				++buffer;

				indexCount += 6;

				x += glyph->advance_x / scale;
			}
		}
		x = text->position.x;
		ftFont->outline_type = 0;
	}

	for (uint i = 0; i < string.length(); i++) {
		auto *glyph = ftgl::texture_font_get_glyph(ftFont, string[i]);
		if (glyph) {

			if (i > 0) {
				float kerning = ftgl::texture_glyph_get_kerning(glyph, string[i - 1]);
				x += kerning / scale;
			}

			float x0 = x + glyph->offset_x / scale;
			float y0 = y - glyph->offset_y / scale;
			float x1 = x0 + glyph->width / scale;
			float y1 = y0 + glyph->height / scale;

			float s0 = glyph->s0;
			float t0 = glyph->t0;
			float s1 = glyph->s1;
			float t1 = glyph->t1;


			buffer->vertex = math::translateVec(*transformationBack, xe::vec2(x0, -y0));
			buffer->uv = xe::vec2(s0, t0);
			buffer->tid = tid;
			buffer->color = color;
			++buffer;

			buffer->vertex = math::translateVec(*transformationBack, xe::vec2(x0, -y1));
			buffer->uv = xe::vec2(s0, t1);
			buffer->tid = tid;
			buffer->color = color;
			++buffer;

			buffer->vertex = math::translateVec(*transformationBack, xe::vec2(x1, -y1));
			buffer->uv = xe::vec2(s1, t1);
			buffer->tid = tid;
			buffer->color = color;
			++buffer;

			buffer->vertex = math::translateVec(*transformationBack, xe::vec2(x1, -y0));
			buffer->uv = xe::vec2(s1, t0);
			buffer->tid = tid;
			buffer->color = color;
			++buffer;

			indexCount += 6;

			x += glyph->advance_x / scale;
		}
	}
	ftFont->outline_type = 2;
}

void xe::gfx::Renderer2D::end() {
	vertexArray->getBuffer()->releasePointer();
	vertexArray->unbind();
}

void xe::gfx::Renderer2D::flush() {
	Renderer::get().setDepthTesting(true);

	std::sort(targets.begin(), targets.end(), [](const Renderable2D *a, const Renderable2D *b) {
		return a->texture > b->texture;
	});

	for (auto &&target : targets) {
		submitInternal(target);
	}
	end();

	flushInternal();
	targets.clear();

	if (!text.empty()) {
		Renderer::get().setDepthTesting(false);

		begin();
		for (auto &&txt : text) {
			submitTextInternal(txt);
		}
		end();

		flushInternal();
		text.clear();
	}
}

void xe::gfx::Renderer2D::flushInternal() {
	shader->bind();
	for (uint i = 0; i < systemUniformBuffers.size(); i++) {
		shader->setVSSystemUniformBuffer(systemUniformBuffers[i].buffer, systemUniformBuffers[i].size, i);
	}

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
	textures.clear();

	//increment draw calls
	++dc;
}

void xe::gfx::Renderer2D::drawLine(float x0, float y0, float x1, float y1, float z, uint color, float thickness) {
	const std::vector<vec2> &uv = Renderable2D::getDefaultUVs();
	const float ts = 0.0f;

	const vec2 normal = math::normalize(vec2(y1 - y0, -(x1 - x0))) * thickness;

	buffer->vertex = math::translateVec(*transformationBack, vec3(x0 + normal.x, y0 + normal.y, z));
	buffer->uv = uv[0];
	buffer->tid = ts;
	buffer->color = color;
	buffer++;

	buffer->vertex = math::translateVec(*transformationBack, vec3(x1 + normal.x, y1 + normal.y, z));
	buffer->uv = uv[1];
	buffer->tid = ts;
	buffer->color = color;
	buffer++;

	buffer->vertex = math::translateVec(*transformationBack, vec3(x1 - normal.x, y1 - normal.y, z));
	buffer->uv = uv[2];
	buffer->tid = ts;
	buffer->color = color;
	buffer++;

	buffer->vertex = math::translateVec(*transformationBack, vec3(x0 - normal.x, y0 - normal.y, z));
	buffer->uv = uv[3];
	buffer->tid = ts;
	buffer->color = color;
	buffer++;

	indexCount += 6;
}

void xe::gfx::Renderer2D::drawLine(const vec2 &start, const vec2 &end, float z, uint color, float thickness) {
	drawLine(start.x, start.y, end.x, end.y, z, color, thickness);
}

void xe::gfx::Renderer2D::drawRect(float x, float y, float width, float height, float z, uint color) {
	drawLine(x, y, x + width, y, z, color);
	drawLine(x + width, y, x + width, y + height, z, color);
	drawLine(x + width, y + height, x, y + height, z, color);
	drawLine(x, y + height, x, y, z, color);
}

void xe::gfx::Renderer2D::drawRect(const xe::vec2 &position, const xe::vec2 &size, float z, uint color) {
	drawRect(position.x, position.y, size.x, size.y, z, color);
}

void xe::gfx::Renderer2D::drawRect(const xe::rect &rectangle, float z, uint color) {
	drawRect(rectangle.getMinBound(), rectangle.size * 2.0f, z, color);
}

void xe::gfx::Renderer2D::fillRect(float x, float y, float width, float height, float z, uint color) {
	vec3 position(x, y, z);
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

void xe::gfx::Renderer2D::fillRect(const xe::vec2 &position, const xe::vec2 &size, float z, uint color) {
	fillRect(position.x, position.y, size.x, size.y, z, color);
}

void xe::gfx::Renderer2D::fillRect(const xe::rect &rectangle, float z, uint color) {
	fillRect(rectangle.getMinBound(), rectangle.size * 2.0f, z, color);
}

float xe::gfx::Renderer2D::submitTexture(const xe::gfx::api::Texture *texture) {
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
		if (textures.size() >= RENDERER_MAX_TEXTURES) {
			end();
			flushInternal();
			begin();
		}
		textures.push_back(texture);
		result = textures.size();
	}

	return result;
}

