//
// Created by FLXR on 7/29/2018.
//

#ifndef X808_TEXTCOMPONENT_HPP
#define X808_TEXTCOMPONENT_HPP


#include "ecs/ecscomponent.hpp"
#include "gfx/color.hpp"
#include "resources/fontmanager.hpp"
#include "math/vec2.hpp"

namespace xe {

	struct TextComponent : public ECSComponent<TextComponent> {
		const Font *font;
		std::wstring string;
		uint textColor;
		uint outlineColor;
		float outlineThickness;
		float size;
		vec2 position;

		TextComponent() = default;

		explicit TextComponent(const std::wstring_view &string, float size, const vec2 &position,
		                       const Font *font = GETFONT("default"),
		                       uint textColor = color::BLACK,
		                       uint outlineColor = color::TRANSPARENT,
		                       float outlineThickness = 0.0f) :
				string(string),
				size(size),
				position(position),
				font(font),
				textColor(textColor),
				outlineColor(outlineColor),
				outlineThickness(outlineThickness) { }
	};

}


#endif //X808_TEXTCOMPONENT_HPP
