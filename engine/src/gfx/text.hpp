//
// Created by FLXR on 7/2/2018.
//

#ifndef X808_TEXT_HPP
#define X808_TEXT_HPP


#include "common.hpp"
#include "resources/font.hpp"

namespace xe { namespace gfx {

	class XE_API Text {
	private:
		friend class Renderer2D;

	public:
		explicit Text(const std::string_view &text, float size, const Font &font);

		inline void setFont(const Font &font) { Text::font = &font; }
		inline void setString(const std::string_view &string) { Text::text = string; }
		inline void setCharacterSize(uint size) { Text::size = size; }
		inline void setColor(uint color) { Text::textColor = color; }
		inline void setOutlineColor(uint color) { Text::outlineColor = color; }
		void setOutlineThickness(float thickness);

		inline const Font *getFont() const { return font; }
		inline const std::string &getString() const { return text; }
		inline float getSize() const { return size; }
		inline uint getColor() const { return textColor; }
		inline uint getOutlineColor() const { return outlineColor; }
		float getOutlineThickness() const;

	private:
		const Font *font;
		std::string text;
		uint textColor;
		uint outlineColor;
		float size;
	};

}}


#endif //X808_TEXT_HPP
