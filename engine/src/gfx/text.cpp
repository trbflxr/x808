//
// Created by FLXR on 7/2/2018.
//

#include <freetype-gl/freetype-gl.h>
#include "text.hpp"
#include "color.hpp"

xe::gfx::Text::Text(const std::string_view &string, float size, const vec2 &position, const xe::Font &font) :
		font(&font),
		string(string.data()),
		textColor(color::BLACK),
		outlineColor(color::TRANSPARENT),
		size(size),
		position(position) { }

void xe::gfx::Text::setOutlineThickness(float thickness) {
	font->getFTFont()->outline_thickness = thickness;
}

float xe::gfx::Text::getOutlineThickness() const {
	return font->getFTFont()->outline_thickness;
}
