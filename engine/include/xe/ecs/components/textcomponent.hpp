//
// Created by FLXR on 7/29/2018.
//

#ifndef X808_TEXTCOMPONENT_HPP
#define X808_TEXTCOMPONENT_HPP

#include <xe/ecs/ecscomponent.hpp>
#include <xe/gfx/text.hpp>

namespace xe {

	struct TextComponent : public ECSComponent<TextComponent> {
		Text *text;

		explicit TextComponent(Text *text) noexcept :
				text(text) { }

		~TextComponent() {
			delete text;
		}

	};

}


#endif //X808_TEXTCOMPONENT_HPP
