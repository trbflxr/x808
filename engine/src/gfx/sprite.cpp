//
// Created by FLXR on 9/12/2018.
//

#include <xe/gfx/sprite.hpp>

namespace xe {

	Sprite::Sprite(const Texture *texture, bool hasTransparency, uint color, bool flipUVs, bool visible) noexcept :
			texture(texture),
			hasTransparency_(hasTransparency),
			color(color),
			visible(visible) {

		UVs = flipUVs ? getFlippedUVs() : getDefaultUVs();
	}

	const std::array<vec2, 4> &Sprite::getDefaultUVs()  {
		static std::array<vec2, 4> UVs{
				vec2(0, 1),
				vec2(1, 1),
				vec2(1, 0),
				vec2(0, 0)
		};
		return UVs;
	}

	const std::array<vec2, 4> &Sprite::getFlippedUVs() {
		static std::array<vec2, 4> UVs{
				vec2(0, 0),
				vec2(1, 0),
				vec2(1, 1),
				vec2(0, 1)
		};
		return UVs;
	}
}