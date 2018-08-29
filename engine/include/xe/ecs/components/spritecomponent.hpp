//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_SPRITECOMPONENT_HPP
#define X808_SPRITECOMPONENT_HPP


#include <xe/ecs/ecscomponent.hpp>
#include <xe/gfx/texture.hpp>
#include <xe/gfx/color.hpp>
#include <xe/math/vec2.hpp>

namespace xe {

	struct SpriteComponent : public ECSComponent<SpriteComponent> {
		const Texture *texture;
		uint color;
		std::array<vec2, 4> UVs;
		bool visible;

		explicit SpriteComponent(const Texture *texture,
		                         uint color = color::WHITE,
		                         bool flipUVs = false,
		                         bool visible = true) noexcept :
				texture(texture),
				color(color),
				visible(visible) {

			UVs = flipUVs ? getFlippedUVs() : getDefaultUVs();
		}

		static inline const std::array<vec2, 4> &getDefaultUVs() {
			static std::array<vec2, 4> UVs{
					vec2(0, 1),
					vec2(1, 1),
					vec2(1, 0),
					vec2(0, 0)
			};
			return UVs;
		}

		static inline const std::array<vec2, 4> &getFlippedUVs() {
			static std::array<vec2, 4> UVs{
					vec2(0, 0),
					vec2(1, 0),
					vec2(1, 1),
					vec2(0, 1)
			};
			return UVs;
		}
	};

}


#endif //X808_SPRITECOMPONENT_HPP
