//
// Created by FLXR on 8/18/2018.
//

#ifndef X808_TEXT_HPP
#define X808_TEXT_HPP


#include <xe/resources/font.hpp>
#include <xe/xeint.hpp>
#include <xe/resources/fontmanager.hpp>
#include <xe/gfx/color.hpp>

namespace xe {

	class Text {
	private:
		friend class Renderer2D;

	public:
		explicit Text(const wstring &string, float size, const vec2 &position,
		              const Font *font = GETFONT("default"),
		              uint textColor = color::WHITE,
		              uint outlineColor = color::TRANSPARENT,
		              float outlineThickness = 0.0f) noexcept :
				string(string),
				size(size),
				position(position),
				font(font),
				textColor(textColor),
				outlineColor(outlineColor),
				outlineThickness(outlineThickness) { }

		const Font *getFont() const { return font; }
		void setFont(const Font *font) { Text::font = font; }

		wstring &getString() { return string; }
		const wstring &getString() const { return string; }
		void setString(const wstring &string) { Text::string = string; }

		uint getTextColor() const { return textColor; }
		void setTextColor(uint textColor) { Text::textColor = textColor; }

		uint getOutlineColor() const { return outlineColor; }
		void setOutlineColor(uint outlineColor) { Text::outlineColor = outlineColor; }

		float getOutlineThickness() const { return outlineThickness; }
		void setOutlineThickness(float thickness) { Text::outlineThickness = thickness; }

		float getSize() const { return size; }
		void setSize(float size) { Text::size = size; }

		const vec2 &getPosition() const { return position; }
		void setPosition(const vec2 &position) { Text::position = position; }

	private:
		const Font *font;
		wstring string;
		uint textColor;
		uint outlineColor;
		float outlineThickness;
		float size;
		vec2 position;
	};

}


#endif //X808_TEXT_HPP
