//
// Created by FLXR on 9/6/2018.
//

#include <freetype-gl/freetype-gl.h>
#include <xe/gfx/renderer.hpp>
#include <xe/gfx/2d/textrenderer.hpp>

namespace xe {

	TextRenderer::TextRenderer(uint width, uint height, Camera *camera) :
			IRenderer2D(width, height, camera) {

		uint offset = 0;
		for (uint i = 0; i < XE_RENDERER2D_MAX_SPRITES * 6; i += 6) {
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		indexBuffer->setData(indices, XE_RENDERER2D_MAX_SPRITES * 6);

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
		shader->bind();
		shader->updateUniforms();

		for (uint i = 0; i < textures.size(); i++) {
			textures[i]->bind(i);
		}

		Renderer::enableDepthMask(false);

		vertexArray->bind();
		indexBuffer->bind();

		vertexArray->drawElements(indicesSize, BeginMode::Triangles);

		indexBuffer->unbind();
		vertexArray->unbind();

		Renderer::enableDepthMask(true);

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
		const Font *font = t->getFont();
		const Texture *atlas = font->getTexture();
		const float tid = submitTexture(atlas);

		const wstring &string = t->getString();
		const uint color = t->getTextColor();
		const uint outlineColor = t->getOutlineColor();
		const float scale = t->getFontScale();
		const float outlineThickness = t->getOutlineThickness();

		//transform
		const mat4 transform = *transformationBack * t->toMatrix();

		float x = 0.0f;
		float y = 0.0f;

		if (outlineThickness > 0.001f) {
			font->setOutlineType(2);
			font->setOutlineThickness(outlineThickness);

			submitString(string, font, outlineColor, tid, scale, transform, x, y);

			x = 0.0f;
		}

		font->setOutlineType(0);
		font->setOutlineThickness(0.0f);

		submitString(string, font, color, tid, scale, transform, x, y);
	}

	void TextRenderer::submitString(const wstring &str, const Font *font, uint color, float tid,
	                                float scale, const mat4 &transform, float &x, float &y) {

		using namespace ftgl;

		for (uint i = 0; i < str.length(); i++) {
			const texture_glyph_t *glyph = static_cast<texture_glyph_t *>(font->getGlyph(str[i]));

			if (!glyph) continue;

			if (i > 0) {
				const float kerning = font->getKerning((void *) glyph, str[i - 1]);
				x += kerning * scale;
			}

			float x0 = x + glyph->offset_x * scale;
			float y0 = y - glyph->offset_y * scale;
			float x1 = x0 + glyph->width * scale;
			float y1 = y0 + glyph->height * scale;

			float u0 = glyph->s0;
			float v0 = glyph->t0;
			float u1 = glyph->s1;
			float v1 = glyph->t1;

			buffer->vertex = mat4::translateXY(transform, x0, -y0);
			buffer->uv.x = u0;
			buffer->uv.y = v0;
			buffer->tid = tid;
			buffer->color = color;
			++buffer;

			buffer->vertex = mat4::translateXY(transform, x0, -y1);
			buffer->uv.x = u0;
			buffer->uv.y = v1;
			buffer->tid = tid;
			buffer->color = color;
			++buffer;

			buffer->vertex = mat4::translateXY(transform, x1, -y1);
			buffer->uv.x = u1;
			buffer->uv.y = v1;
			buffer->tid = tid;
			buffer->color = color;
			++buffer;

			buffer->vertex = mat4::translateXY(transform, x1, -y0);
			buffer->uv.x = u1;
			buffer->uv.y = v0;
			buffer->tid = tid;
			buffer->color = color;
			++buffer;

			indicesSize += 6;

			x += glyph->advance_x * scale;
		}
	}

}