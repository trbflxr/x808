//
// Created by FLXR on 9/6/2018.
//

#ifndef X808_SPRITERENDERER_HPP
#define X808_SPRITERENDERER_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/gfx/2d/irenderer2d.hpp>
#include <xe/ecs/components/spritecomponent.hpp>
#include <xe/ecs/components/transform2dcomponent.hpp>

namespace xe {

	class XE_API SpriteRenderer : public IRenderer2D {
	private:
		struct RenderTarget {
			const SpriteComponent *sprite;
			const Transform2DComponent *transform;

			RenderTarget(const SpriteComponent *sprite,
			             const Transform2DComponent *transform) noexcept :
					sprite(sprite), transform(transform) { }
		};

	public:
		explicit SpriteRenderer(uint width, uint height);
		~SpriteRenderer() override = default;

		void submit(const SpriteComponent *sprite, const Transform2DComponent *transform);

		void begin() override;
		void end() override;
		void flush() override;

	private:
		void submitInternal(const RenderTarget &target);

	private:
		std::vector<RenderTarget> targets;
		std::vector<RenderTarget> transparentTargets;
	};
}


#endif //X808_SPRITERENDERER_HPP
