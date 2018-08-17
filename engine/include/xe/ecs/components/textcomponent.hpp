//
// Created by FLXR on 7/29/2018.
//

#ifndef X808_TEXTCOMPONENT_HPP
#define X808_TEXTCOMPONENT_HPP

#include <xe/ecs/ecscomponent.hpp>
#include <xe/gfx/color.hpp>
#include <xe/resources/fontmanager.hpp>
#include <xe/math/vec2.hpp>

namespace xe {

	struct TextComponent : public ECSComponent<TextComponent> {
		const Font *font;
		const wchar_t *string;
		uint textColor;
		uint outlineColor;
		float outlineThickness;
		float size;
		vec2 position;

		TextComponent() :
				string(L""),
				size(0),
				position(0.0f, 0.0f),
				font(GETFONT("default")),
				textColor(color::WHITE),
				outlineColor(color::TRANSPARENT),
				outlineThickness(0.0f) { }

		explicit TextComponent(const wchar_t *string, float size, const vec2 &position,
		                       const Font *font = GETFONT("default"),
		                       uint textColor = color::WHITE,
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
