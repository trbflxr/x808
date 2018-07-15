//
// Created by FLXR on 7/2/2018.
//

#include <freetype-gl/freetype-gl.h>
#include "text.hpp"
#include "color.hpp"

namespace xe { namespace gfx {

	Text::Text(const std::string_view &string, float size, const vec2 &position, const Font &font) :
			font(&font),
			string(string.data()),
			textColor(color::BLACK),
			outlineColor(color::TRANSPARENT),
			size(size),
			position(position) { }

	void Text::setOutlineThickness(float thickness) {
		font->getFTFont()->outline_thickness = thickness;
	}

	float Text::getOutlineThickness() const {
		return font->getFTFont()->outline_thickness;
	}

}}