//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_SPRITECOMPONENT_HPP
#define X808_SPRITECOMPONENT_HPP


#include <xe/ecs/ecscomponent.hpp>
#include <xe/gfx/sprite.hpp>

namespace xe {

	struct SpriteComponent : public ECSComponent<SpriteComponent> {
		Sprite sprite;

		explicit SpriteComponent(const Texture *texture,
		                         bool hasTransparency = false,
		                         uint color = color::WHITE,
		                         bool flipUVs = false,
		                         bool visible = true) noexcept :
				sprite(texture, hasTransparency, color, flipUVs, visible) { }

	};

}


#endif //X808_SPRITECOMPONENT_HPP
