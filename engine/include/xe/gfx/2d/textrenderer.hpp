//
// Created by FLXR on 9/6/2018.
//

#ifndef X808_TEXTRENDERER_HPP
#define X808_TEXTRENDERER_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/gfx/text.hpp>
#include <xe/gfx/2d/irenderer2d.hpp>

namespace xe {

	class XE_API TextRenderer : public IRenderer2D {
	private:
		struct TextVertexData {
			vec4 vertexTid;
			vec2 uv;
			uint color;
			uint outlineColor;
			vec2 offset;
			vec4 widthEdge;
		};

	public:
		explicit TextRenderer(uint width, uint height, Camera *camera);

		void submit(const Text *text);

		void render(std::vector<const Text *> &targets);

		void begin() override;
		void end() override;
		void flush() override;

	private:
		void submitInternal(const Text *t);

	private:
		std::vector<const Text *> text;

		TextVertexData *buffer;
	};

}


#endif //X808_TEXTRENDERER_HPP
