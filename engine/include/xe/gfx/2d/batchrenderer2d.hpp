//
// Created by FLXR on 9/10/2018.
//

#ifndef X808_BATCHRENDERER2D_HPP
#define X808_BATCHRENDERER2D_HPP


#include <xe/gfx/2d/spriterenderer.hpp>
#include <xe/gfx/2d/textrenderer.hpp>

namespace xe {

	class XE_API BatchRenderer2D {
	public:
		explicit BatchRenderer2D(uint width, uint height, Camera *camera);
		~BatchRenderer2D();

		void submit(const SpriteComponent *sprite, const Transform2DComponent *transform);
		void submit(const Text *text);

		void renderSprites();
		void renderText();

		void clear();

	private:
		Camera *camera;

		SpriteRenderer *spriteRenderer;
		TextRenderer *textRenderer;

		std::vector<RenderTarget2D> sprites;
		std::vector<RenderTarget2D> transparentSprites;

		std::vector<const Text *> text;
	};

}


#endif //X808_BATCHRENDERER2D_HPP
