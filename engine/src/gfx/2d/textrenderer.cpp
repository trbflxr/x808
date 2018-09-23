//
// Created by FLXR on 9/6/2018.
//

#include <xe/gfx/renderer.hpp>
#include <xe/gfx/2d/textrenderer.hpp>

namespace xe {

#define TEXT_RENDERER_VERTEX_SIZE sizeof(TextVertexData)

#define TEXT_RENDERER_SPRITE_SIZE     (TEXT_RENDERER_VERTEX_SIZE * 4)
#define TEXT_RENDERER_BUFFER_SIZE     (TEXT_RENDERER_SPRITE_SIZE * XE_RENDERER2D_MAX_SPRITES)

	TextRenderer::TextRenderer(uint width, uint height, Camera *camera) :
			IRenderer2D(width, height, camera) {

		VertexBuffer *buffer = vertexArray->popBuffer();
		delete buffer;

		buffer = new VertexBuffer(BufferUsage::DynamicDraw);
		buffer->resize(TEXT_RENDERER_BUFFER_SIZE);

		BufferLayout layout;
		layout.push<vec4>("posTid");
		layout.push<vec2>("uv");
		layout.push<byte>("color", 4, true);
		layout.push<byte>("outlineColor", 4, true);
		layout.push<vec2>("offset");
		layout.push<vec4>("widthEdge");

		buffer->setLayout(layout);

		vertexArray->pushBuffer(buffer);


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
		buffer = static_cast<TextVertexData *>(vertexArray->getBuffer(0)->getPointer());
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
		const Font &font = *t->getFont();
		const Texture *atlas = font.getAtlas();
		const float tid = submitTexture(atlas);

		const float size = t->getSize() / 10.0f;
		const wstring &string = t->getString();
		const vec2 &offset = t->getOutlineOffset();
		const uint color = t->getTextColor();
		const uint outlineColor = t->getOutlineColor();

		//edge and outline
		const vec2 &outline = t->getOutline();
		vec2 edge = t->getEdge();

		if (t->useAutoEdge()) {
			//todo: formula?
			edge.x = 0.50f;
			edge.y = 0.1f;
		}

		const vec4 widthEdge = vec4(edge.x, edge.y, outline.x, outline.y);

		//transform
		const mat4 transform = *transformationBack * t->toMatrix();

		float x = 0.0f;
		for (uint i = 0; i < string.length(); ++i) {
			const Glyph &glyph = font.get((uint) string[i]);

			if (i > 0) {
				const float kerning = Font::getKerning(glyph, (uint) string[i - 1]);
				x += kerning * size;
			}

			const float x0 = x + glyph.offset.x * size;
			const float y0 = glyph.offset.y * size;
			const float x1 = x0 + glyph.size.x * size;
			const float y1 = y0 + glyph.size.y * size;

			const float u0 = glyph.uv.x;
			const float v0 = glyph.uv.y;
			const float u1 = u0 + glyph.texSize.x;
			const float v1 = v0 + glyph.texSize.y;

			buffer->vertexTid = vec4(mat4::translateXY(transform, x0, -y0), tid);
			buffer->uv.x = u0;
			buffer->uv.y = v0;
			buffer->color = color;
			buffer->outlineColor = outlineColor;
			buffer->offset = offset;
			buffer->widthEdge = widthEdge;
			++buffer;

			buffer->vertexTid = vec4(mat4::translateXY(transform, x0, -y1), tid);
			buffer->uv.x = u0;
			buffer->uv.y = v1;
			buffer->color = color;
			buffer->outlineColor = outlineColor;
			buffer->offset = offset;
			buffer->widthEdge = widthEdge;
			++buffer;

			buffer->vertexTid = vec4(mat4::translateXY(transform, x1, -y1), tid);
			buffer->uv.x = u1;
			buffer->uv.y = v1;
			buffer->color = color;
			buffer->outlineColor = outlineColor;
			buffer->offset = offset;
			buffer->widthEdge = widthEdge;
			++buffer;

			buffer->vertexTid = vec4(mat4::translateXY(transform, x1, -y0), tid);
			buffer->uv.x = u1;
			buffer->uv.y = v0;
			buffer->color = color;
			buffer->outlineColor = outlineColor;
			buffer->offset = offset;
			buffer->widthEdge = widthEdge;
			++buffer;

			x += glyph.xAdvance * size;

			indicesSize += 6;
		}
	}

}