//
// Created by FLXR on 6/29/2018.
//

#include <freetype-gl/freetype-gl.h>
#include <algorithm>

#include "renderer2d.hpp"
#include "renderer.hpp"
#include "resources/shadermanager.hpp"

namespace xe { namespace gfx {

#define RENDERER_MAX_SPRITES     60000
#define RENDERER_SPRITE_SIZE     (RENDERER_VERTEX_SIZE * 4)
#define RENDERER_BUFFER_SIZE     (RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES)
#define RENDERER_INDICES_SIZE    (RENDERER_MAX_SPRITES * 6)
#define RENDERER_MAX_TEXTURES    (32 - 1)


	const uint requiredSystemUniformsCount = 2;
	const char *requiredSystemUniforms[requiredSystemUniformsCount] = {
			"sys_ProjectionMatrix",
			"sys_ViewMatrix"};

	const uint sys_ProjectionMatrixIndex = 0;
	const uint sys_ViewMatrixIndex = 1;


	Renderer2D::Renderer2D(uint width, uint height) :
			indexCount(0),
			screenSize(width, height),
			viewportSize(width, height) {

		init();
	}

	Renderer2D::Renderer2D(const vec2u &screenSize) :
			indexCount(0),
			screenSize(screenSize),
			viewportSize(screenSize) {

		init();
	}

	Renderer2D::~Renderer2D() {
		delete indexBuffer;
		delete vertexArray;

		systemUniforms.clear();
		systemUniformBuffers.clear();
	}

	void Renderer2D::init() {
		transformationStack.emplace_back(1.0f);
		transformationBack = &transformationStack.back();

		systemUniforms.resize(requiredSystemUniformsCount);

		shader = GETSHADER("batchRenderer");

		const api::ShaderUniformBufferVec &vssu = shader->getVSUniforms();

		XE_ASSERT(vssu.size());

		for (auto &&ub : vssu) {
			api::UniformBuffer buffer(new byte[ub->getSize()], ub->getSize());
			systemUniformBuffers.push_back(buffer);

			for (auto &&uniform: ub->getUniforms()) {
				for (uint j = 0; j < requiredSystemUniformsCount; j++) {
					if (strcmp(uniform->getName().c_str(), requiredSystemUniforms[j]) == 0) {
						systemUniforms[j] = api::Uniform(uniform->getName().c_str(), buffer, uniform->getOffset());
					}
				}
			}
		}

		//default camera
		setCamera(new Camera(mat4::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1, 1000)));

		shader->bind();

		api::VertexBuffer *buffer = api::VertexBuffer::create(api::VertexBuffer::Type::DYNAMIC);
		buffer->resize(RENDERER_BUFFER_SIZE);

		api::BufferLayout layout;
		layout.push<vec3>("POSITION"); // Position
		layout.push<vec2>("TEXCOORD"); // UV
		layout.push<float>("ID"); // Texture Index
		layout.push<byte>("COLOR", 4, true); // Color
		buffer->setLayout(layout);

		vertexArray = api::VertexArray::create();
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

		indexBuffer = api::IndexBuffer::create(indices, RENDERER_INDICES_SIZE);
		vertexArray->unbind();
	}

	void Renderer2D::push(const mat4 &matrix, bool override) {
		transformationStack.push_back(override ? matrix : transformationStack.back() * matrix);
		transformationBack = &transformationStack.back();
	}

	void Renderer2D::pop() {
		if (transformationStack.size() > 1) {
			transformationStack.pop_back();
		}
		transformationBack = &transformationStack.back();
	}

	void Renderer2D::setCamera(Camera *camera) {
		Renderer2D::camera = camera;

		memcpy(systemUniforms[sys_ProjectionMatrixIndex].buffer.buffer +
		       systemUniforms[sys_ProjectionMatrixIndex].offset,
		       &camera->getProjection().elements, sizeof(mat4));

		memcpy(systemUniforms[sys_ViewMatrixIndex].buffer.buffer + systemUniforms[sys_ViewMatrixIndex].offset,
		       &camera->getViewMatrix().elements, sizeof(mat4));
	}

	void Renderer2D::begin() {
		Renderer::enableBlend(true);
		Renderer::setBlendFunction(BlendFunction::SOURCE_ALPHA, BlendFunction::ONE_MINUS_SOURCE_ALPHA);

		Renderer::setViewport(0, 0, screenSize.x, screenSize.y);

		vertexArray->bind();
		buffer = vertexArray->getBuffer(0)->getPointer<VertexData>();
	}

	void
	Renderer2D::submit(const SpriteComponent *sprite, const Transform2DComponent *transform) {
		targets.emplace_back(sprite, transform);
	}

	void Renderer2D::submitInternal(RenderTarget target) {
		const std::array<vec2, 4> &vertices = target.transform->bounds.getVertices();
		const uint color = target.sprite->color;
		const std::vector<vec2> &uv = target.sprite->UVs;
		const api::Texture *texture = target.sprite->texture;

		float textureSlot = 0.0f;
		if (texture) {
			textureSlot = submitTexture(target.sprite->texture);
		}

		buffer->vertex = mat4::translateVec(*transformationBack, vertices[0], target.transform->zIndex);
		buffer->uv = uv[0];
		buffer->tid = textureSlot;
		buffer->color = color;
		buffer++;

		buffer->vertex = mat4::translateVec(*transformationBack, vertices[3], target.transform->zIndex);
		buffer->uv = uv[1];
		buffer->tid = textureSlot;
		buffer->color = color;
		buffer++;

		buffer->vertex = mat4::translateVec(*transformationBack, vertices[2], target.transform->zIndex);
		buffer->uv = uv[2];
		buffer->tid = textureSlot;
		buffer->color = color;
		buffer++;

		buffer->vertex = mat4::translateVec(*transformationBack, vertices[1], target.transform->zIndex);
		buffer->uv = uv[3];
		buffer->tid = textureSlot;
		buffer->color = color;
		buffer++;

		indexCount += 6;
	}

	void Renderer2D::submitText(const TextComponent *text) {
		Renderer2D::text.push_back(text);
	}

	void Renderer2D::submitTextInternal(const TextComponent *text) {
		using namespace ftgl;

		const Font &font = *text->font;
		ftgl::texture_font_t *ftFont = font.getFTFont();
		const std::wstring &string = text->string;
		const uint color = text->textColor;
		const uint outlineColor = text->outlineColor;
		const float outlineThickness = text->outlineThickness;

		const api::Texture2D *texture = font.getTexture();
		XE_ASSERT(texture);

		const float tid = submitTexture(texture);
		const float scale = font.getSize() / text->size;

		float x = text->position.x;
		const float y = -text->position.y;


		if (outlineThickness > 0) {
			ftFont->outline_thickness = outlineThickness;

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

					buffer->vertex = mat4::translateVec(*transformationBack, xe::vec2(x0, -y0));
					buffer->uv = xe::vec2(s0, t0);
					buffer->tid = tid;
					buffer->color = outlineColor;
					++buffer;

					buffer->vertex = mat4::translateVec(*transformationBack, xe::vec2(x0, -y1));
					buffer->uv = xe::vec2(s0, t1);
					buffer->tid = tid;
					buffer->color = outlineColor;
					++buffer;

					buffer->vertex = mat4::translateVec(*transformationBack, xe::vec2(x1, -y1));
					buffer->uv = xe::vec2(s1, t1);
					buffer->tid = tid;
					buffer->color = outlineColor;
					++buffer;

					buffer->vertex = mat4::translateVec(*transformationBack, xe::vec2(x1, -y0));
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
			ftFont->outline_thickness = 0;
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


				buffer->vertex = mat4::translateVec(*transformationBack, xe::vec2(x0, -y0));
				buffer->uv = xe::vec2(s0, t0);
				buffer->tid = tid;
				buffer->color = color;
				++buffer;

				buffer->vertex = mat4::translateVec(*transformationBack, xe::vec2(x0, -y1));
				buffer->uv = xe::vec2(s0, t1);
				buffer->tid = tid;
				buffer->color = color;
				++buffer;

				buffer->vertex = mat4::translateVec(*transformationBack, xe::vec2(x1, -y1));
				buffer->uv = xe::vec2(s1, t1);
				buffer->tid = tid;
				buffer->color = color;
				++buffer;

				buffer->vertex = mat4::translateVec(*transformationBack, xe::vec2(x1, -y0));
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

	void Renderer2D::end() {
		vertexArray->getBuffer(0)->releasePointer();
		vertexArray->unbind();
	}

	void Renderer2D::flush() {
		//enable for correct z-index work
		Renderer::enableDepthTesting(true);

		std::sort(targets.begin(), targets.end(),
		          [](const RenderTarget a, const RenderTarget b) {
			          return a.sprite->texture > b.sprite->texture;
		          });

		for (auto &&target : targets) {
			submitInternal(target);
		}
		end();

		flushInternal();
		targets.clear();

		//draw text
		if (!text.empty()) {
			//disable for text drawing
			Renderer::enableDepthTesting(false);

			begin();
			for (auto &&txt : text) {
				submitTextInternal(txt);
			}
			end();

			flushInternal();
			text.clear();
		}

		Renderer::enableBlend(false);
	}

	void Renderer2D::flushInternal() {
		shader->bind();
		for (uint i = 0; i < systemUniformBuffers.size(); i++) {
			shader->setVSUniformBuffer(systemUniformBuffers[i].buffer, systemUniformBuffers[i].size, i);
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
		Renderer::incDC();
	}

	void
	Renderer2D::drawLine(float x0, float y0, float x1, float y1, float z, uint color, float thickness) {
		const std::vector<vec2> &uv = SpriteComponent::getDefaultUVs();
		const float ts = 0.0f;

		const vec2 normal = vec2::normalize(vec2(y1 - y0, -(x1 - x0))) * thickness;

		buffer->vertex = mat4::translateVec(*transformationBack, vec3(x0 + normal.x, y0 + normal.y, z));
		buffer->uv = uv[0];
		buffer->tid = ts;
		buffer->color = color;
		buffer++;

		buffer->vertex = mat4::translateVec(*transformationBack, vec3(x1 + normal.x, y1 + normal.y, z));
		buffer->uv = uv[1];
		buffer->tid = ts;
		buffer->color = color;
		buffer++;

		buffer->vertex = mat4::translateVec(*transformationBack, vec3(x1 - normal.x, y1 - normal.y, z));
		buffer->uv = uv[2];
		buffer->tid = ts;
		buffer->color = color;
		buffer++;

		buffer->vertex = mat4::translateVec(*transformationBack, vec3(x0 - normal.x, y0 - normal.y, z));
		buffer->uv = uv[3];
		buffer->tid = ts;
		buffer->color = color;
		buffer++;

		indexCount += 6;
	}

	void Renderer2D::drawLine(const vec2 &start, const vec2 &end, float z, uint color, float thickness) {
		drawLine(start.x, start.y, end.x, end.y, z, color, thickness);
	}

	void Renderer2D::drawRect(float x, float y, float width, float height, float z, uint color) {
		drawLine(x, y, x + width, y, z, color);
		drawLine(x + width, y, x + width, y + height, z, color);
		drawLine(x + width, y + height, x, y + height, z, color);
		drawLine(x, y + height, x, y, z, color);
	}

	void Renderer2D::drawRect(const vec2 &position, const vec2 &size, float z, uint color) {
		drawRect(position.x, position.y, size.x, size.y, z, color);
	}

	void Renderer2D::drawRect(const rect &rectangle, float z, uint color) {
		drawRect(rectangle.getMinBound(), rectangle.size * 2.0f, z, color);
	}

	void Renderer2D::fillRect(float x, float y, float width, float height, float z, uint color) {
		vec3 position(x, y, z);
		vec2 size(width, height);
		const std::vector<vec2> &uv = SpriteComponent::getDefaultUVs();

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

	void Renderer2D::fillRect(const vec2 &position, const vec2 &size, float z, uint color) {
		fillRect(position.x, position.y, size.x, size.y, z, color);
	}

	void Renderer2D::fillRect(const rect &rectangle, float z, uint color) {
		fillRect(rectangle.getMinBound(), rectangle.size * 2.0f, z, color);
	}

	float Renderer2D::submitTexture(const api::Texture *texture) {
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


}}