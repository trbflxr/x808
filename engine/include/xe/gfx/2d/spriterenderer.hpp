//
// Created by FLXR on 9/6/2018.
//

#ifndef X808_SPRITERENDERER_HPP
#define X808_SPRITERENDERER_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/gfx/2d/irenderer2d.hpp>
#include <xe/gfx/uniformbuffer.hpp>
#include <xe/gfx/sprite.hpp>

namespace xe {

	class XE_API SpriteRenderer : public IRenderer2D {
	public:
		explicit SpriteRenderer(uint width, uint height, Camera *camera);

		void submit(const Sprite *sprite);

		void begin() override;
		void end() override;
		void flush() override;

		void render(const std::vector<const Sprite *> &sprites);

	private:
		void submitInternal(const Sprite *sprite);

	private:
		std::vector<const Sprite *> targets;
		std::vector<const Sprite *> transparentTargets;
	};
}


#endif //X808_SPRITERENDERER_HPP
