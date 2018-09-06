//
// Created by FLXR on 9/6/2018.
//

#ifndef X808_TEXTRENDERER_HPP
#define X808_TEXTRENDERER_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/gfx/2d/irenderer2d.hpp>
#include <xe/ecs/components/textcomponent.hpp>

namespace xe {


	class XE_API TextRenderer : public IRenderer2D {
	public:
		explicit TextRenderer(uint width, uint height);
		~TextRenderer() override = default;

		void submit(const TextComponent *text);

		void begin() override;
		void end() override;
		void flush() override;

	private:
		void submitInternal(const TextComponent *component);

	private:
		std::vector<const TextComponent *> text;
	};

}


#endif //X808_TEXTRENDERER_HPP
