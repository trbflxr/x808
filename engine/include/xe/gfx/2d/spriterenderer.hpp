//
// Created by FLXR on 9/6/2018.
//

#ifndef X808_SPRITERENDERER_HPP
#define X808_SPRITERENDERER_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/gfx/2d/irenderer2d.hpp>
#include <xe/gfx/2d/light2d.hpp>
#include <xe/ecs/components/spritecomponent.hpp>
#include <xe/ecs/components/transform2dcomponent.hpp>
#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/fx/quad.hpp>
#include <xe/gfx/fx/final.hpp>
#include <xe/gfx/uniformbuffer.hpp>

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
		explicit SpriteRenderer(uint width, uint height, bool useLights = false);
		~SpriteRenderer() override ;

		void submit(const SpriteComponent *sprite, const Transform2DComponent *transform);

		void begin() override;
		void end() override;
		void flush() override;

		void addLight(Light2D *light);

	private:
		void submitInternal(const RenderTarget &target);

		void updateLightsUBO();

	private:
		std::vector<RenderTarget> targets;
		std::vector<RenderTarget> transparentTargets;

		static constexpr uint MAX_LIGHTS = 64;
		bool useLights;
		std::vector<Light2D *> lights;
		UniformBuffer* lightBuffer;
	};
}


#endif //X808_SPRITERENDERER_HPP
