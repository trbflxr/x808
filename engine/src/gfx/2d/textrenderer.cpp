//
// Created by FLXR on 9/6/2018.
//

#include <freetype-gl/freetype-gl.h>
#include <xe/gfx/renderer.hpp>
#include <xe/gfx/2d/textrenderer.hpp>

namespace xe {

	TextRenderer::TextRenderer(uint width, uint height, Camera *camera) :
			IRenderer2D(width, height, camera) {

		shader = new Shader("dTextRenderer");
	}

	void TextRenderer::begin() {
		Renderer::enableBlend(true);
		Renderer::setBlendFunction(BlendFunction::SourceAlpha, BlendFunction::OneMinusSourceAlpha);
		Renderer::setViewport(0, 0, width, height);

		vertexArray->bind();
		buffer = static_cast<VertexData *>(vertexArray->getBuffer(0)->getPointer());
	}

	void TextRenderer::end() {
		updateCamera();

		Renderer::enableDepthTesting(false);

		if (!text.empty()) {
			for (auto &&txt : text) {
				submitInternal(txt);
			}

			text.clear();
		}

		releaseBuffer();
	}

	void TextRenderer::flush() {
		updateIndexBuffer();

		shader->bind();
		shader->updateUniforms();

		for (uint i = 0; i < textures.size(); i++) {
			textures[i]->bind(i);
		}

		vertexArray->bind();
		indexBuffer->bind();

		vertexArray->drawElements(indicesSize, BeginMode::Triangles);

		indexBuffer->unbind();
		vertexArray->unbind();

		for (uint i = 0; i < textures.size(); i++) {
			textures[i]->unbind(i);
		}

		shader->unbind();

		indicesSize = 0;
		indicesOffset = 0;

		textures.clear();

		//increment draw calls
		Renderer::incDC();
	}

	void TextRenderer::submit(const Text *text) {
		TextRenderer::text.push_back(text);
	}

	void TextRenderer::render(std::vector<const Text *> &targets) {
		begin();

		for (const auto &t : targets) {
			submitInternal(t);
		}

		releaseBuffer();
		flush();
	}

	void TextRenderer::submitInternal(const Text *t) {
		using namespace ftgl;

		static constexpr uint is = 6;
		static constexpr uint io = 4;
		static constexpr uint indices[is] = {0, 1, 2, 2, 3, 0};

		const Font &font = *t->font;
		ftgl::texture_font_t *ftFont = font.getFTFont();
		const wstring &string = t->string;
		const uint color = t->textColor;
		const uint outlineColor = t->outlineColor;
		const float outlineThickness = t->outlineThickness;
		const vec2 &position = t->position;
		const float size = t->size;

		const Texture *texture = font.getTexture();
		XE_ASSERT(texture);

		const float tid = submitTexture(texture);
		const float scale = font.getSize() / size;

		float x = position.x;
		const float y = -position.y;


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

					appendIndices(indices, is, io);

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

					x += glyph->advance_x / scale;
				}
			}
			x = position.x;
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

				appendIndices(indices, is, io);

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

				x += glyph->advance_x / scale;
			}
		}
		ftFont->outline_type = 2;
	}

}