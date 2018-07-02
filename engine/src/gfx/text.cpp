//
// Created by FLXR on 7/2/2018.
//

#include <freetype-gl/freetype-gl.h>
#include "text.hpp"
#include "color.hpp"

xe::gfx::Text::Text(const std::string_view &text, float size, const xe::Font &font) :
		font(&font),
		text(text.data()),
		textColor(color::BLACK),
		outlineColor(color::TRANSPARENT),
		size(size) {


}

void xe::gfx::Text::setOutlineThickness(float thickness) {
	font->getFTFont()->outline_thickness = thickness;
}

float xe::gfx::Text::getOutlineThickness() const {
	return font->getFTFont()->outline_thickness;
}
