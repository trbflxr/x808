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
		explicit Text(const std::wstring_view &string, float size, const vec2& position, const Font &font);

		inline void setFont(const Font &font) { Text::font = &font; }
		inline const Font *getFont() const { return font; }

		inline void setString(const std::wstring_view &string) { Text::string = string; }
		inline const std::wstring &getString() const { return string; }

		inline void setCharacterSize(uint size) { Text::size = size; }
		inline float getSize() const { return size; }

		inline void setColor(uint color) { Text::textColor = color; }
		inline uint getColor() const { return textColor; }

		inline void setOutlineColor(uint color) { Text::outlineColor = color; }
		inline uint getOutlineColor() const { return outlineColor; }

		void setOutlineThickness(float thickness);
		float getOutlineThickness() const;

		inline const vec2 &getPosition() const { return position; }
		inline void setPosition(const vec2 &position) { Text::position = position; }

	private:
		const Font *font;
		std::wstring string;
		uint textColor;
		uint outlineColor;
		float size;

		vec2 position;
	};

}}


#endif //X808_TEXT_HPP
