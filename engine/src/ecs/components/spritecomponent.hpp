//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_SPRITECOMPONENT_HPP
#define X808_SPRITECOMPONENT_HPP


#include "gfx/api/texture.hpp"
#include "gfx/color.hpp"
#include "ecs/ecscomponent.hpp"
#include "math/vec2.hpp"

namespace xe {

	struct SpriteComponent : public ECSComponent<SpriteComponent> {
		const gfx::api::Texture *texture;
		uint color;
		std::vector<vec2> UVs;
		bool visible;

		SpriteComponent() noexcept :
				texture(nullptr),
				color(color::WHITE),
				visible(true) {

			UVs = getDefaultUVs();
		}

		explicit SpriteComponent(const gfx::api::Texture *texture, uint color, bool visible = true) noexcept :
				texture(texture),
				color(color),
				visible(visible) {

			UVs = getDefaultUVs();
		}

		static const std::vector<vec2> &getDefaultUVs() {
			static std::vector<vec2> UVs;
			if (UVs.empty()) {
				UVs.emplace_back(0, 1);
				UVs.emplace_back(1, 1);
				UVs.emplace_back(1, 0);
				UVs.emplace_back(0, 0);
			}
			return UVs;
		}
	};

}


#endif //X808_SPRITECOMPONENT_HPP
