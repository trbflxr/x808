//
// Created by FLXR on 8/18/2018.
//

#ifndef X808_TEXT_HPP
#define X808_TEXT_HPP


#include <xe/gfx/color.hpp>
#include <xe/resources/fontmanager.hpp>
#include <xe/gfx/2d/itransformable2d.hpp>

namespace xe {

	class Text : public ITransformable2D {
	public:
		explicit Text(const wstring &string, const Font *font = GETFONT("default"), float scale = 1.0f) noexcept :
				font(font),
				string(string),
				textColor(color::WHITE),
				outlineColor(color::TRANSPARENT),
				outlineThickness(0.0f),
				scale(scale) { }

		inline const Font *getFont() const { return font; }
		inline void setFont(const Font *font) { Text::font = font; }

		inline wstring &getString() { return string; }
		inline const wstring &getString() const { return string; }
		inline void setString(const wstring &string) { Text::string = string; }

		inline uint getTextColor() const { return textColor; }
		inline void setTextColor(uint textColor) { Text::textColor = textColor; }

		inline uint getOutlineColor() const { return outlineColor; }
		inline void setOutlineColor(uint outlineColor) { Text::outlineColor = outlineColor; }

		inline float getFontScale() const { return scale; }
		inline void setFontScale(float scale) { Text::scale = scale; }

		inline float getOutlineThickness() const { return outlineThickness; }
		inline void setOutlineThickness(float thickness) { Text::outlineThickness = thickness; }

	private:
		const Font *font;
		wstring string;
		uint textColor;
		uint outlineColor;
		float outlineThickness;
		float scale;
	};

}


#endif //X808_TEXT_HPP
