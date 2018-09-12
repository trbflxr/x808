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
#include <xe/math/transform2d.hpp>

namespace xe {

	struct RenderTarget2D {
		const Sprite *sprite;
		const Transform2D *transform;

		RenderTarget2D(const Sprite *sprite,
		               const Transform2D *transform) noexcept :
				sprite(sprite), transform(transform) { }
	};

	class XE_API SpriteRenderer : public IRenderer2D {
	public:
		explicit SpriteRenderer(uint width, uint height, Camera *camera);

		void submit(const Sprite *sprite, const Transform2D *transform);

		void begin() override;
		void end() override;
		void flush() override;

		void render(const std::vector<RenderTarget2D> &targets);

	private:
		void submitInternal(const RenderTarget2D &target);

	private:
		std::vector<RenderTarget2D> targets;
		std::vector<RenderTarget2D> transparentTargets;
	};
}


#endif //X808_SPRITERENDERER_HPP
