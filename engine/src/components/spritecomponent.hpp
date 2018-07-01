//
// Created by FLXR on 7/1/2018.
//

#ifndef X808_SPRITECOMPONENT_HPP
#define X808_SPRITECOMPONENT_HPP


#include "component.hpp"
#include "gfx/sprite.hpp"

namespace xe {

	class SpriteComponent : public Component {
	public:
		explicit SpriteComponent(gfx::Sprite *sprite) : sprite(sprite) { }

		static const char *getStaticType() {
			static const char *type = "Sprite";
			return type;
		}

		inline const char *getType() const override { return getStaticType(); }

	public:
		gfx::Sprite *sprite;
	};

}


#endif //X808_SPRITECOMPONENT_HPP
