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
	public:
		explicit TextRenderer(uint width, uint height, Camera *camera);

		void submit(const Text *text);

		void render(std::vector<const Text *> &targets);

		void begin() override;
		void end() override;
		void flush() override;

	private:
		void submitInternal(const Text *t);

		void submitString(const string &str, const Font *font, uint color, float tid,
		                  float scale, const mat4 &transform, float &x, float &y);

	private:
		std::vector<const Text *> text;

		VertexData *buffer;
	};

}


#endif //X808_TEXTRENDERER_HPP
