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
		explicit Text(const wstring &string, float size, const Font *font = GETFONT("default")) noexcept :
				string(string),
				size(size),
				font(font),
				textColor(color::WHITE),
				outlineColor(color::TRANSPARENT),
				outline(0.0f, 0.001f),
				outlineOffset(0.0f, 0.0f),
				edge(0.0f, 0.001f),
				useAutoEdge_(true) { }

		inline const Font *getFont() const { return font; }
		inline void setFont(const Font *font) { Text::font = font; }

		inline wstring &getString() { return string; }
		inline const wstring &getString() const { return string; }
		inline void setString(const wstring &string) { Text::string = string; }

		inline uint getTextColor() const { return textColor; }
		inline void setTextColor(uint textColor) { Text::textColor = textColor; }

		inline uint getOutlineColor() const { return outlineColor; }
		inline void setOutlineColor(uint outlineColor) { Text::outlineColor = outlineColor; }

		inline const vec2 &getOutline() const { return outline; }
		inline void setOutline(const vec2 &outline) { Text::outline = outline; }
		inline void setOutline(float width, float edgeAboveZero) { Text::outline = {width, edgeAboveZero}; }

		inline const vec2 &getOutlineOffset() const { return outlineOffset; }
		inline void setOutlineOffset(const vec2 &offset) { Text::outlineOffset = offset; }

		inline float getSize() const { return size; }
		inline void setSize(float size) { Text::size = size; }

		inline void useAutoEdge(bool use) { Text::useAutoEdge_ = use; }
		inline bool useAutoEdge() const { return useAutoEdge_; }

		inline const vec2 &getEdge() const { return edge; }

		inline void setEdge(const vec2 &edge) {
			useAutoEdge_ = false;
			Text::edge = edge;
		}

		inline void setEdge(float width, float edgeAboveZero) {
			useAutoEdge_ = false;
			Text::edge = {width, edgeAboveZero};
		}

	private:
		const Font *font;
		wstring string;
		uint textColor;
		uint outlineColor;
		vec2 outline;
		vec2 outlineOffset;
		float size;

		bool useAutoEdge_;
		vec2 edge;
	};

}


#endif //X808_TEXT_HPP
