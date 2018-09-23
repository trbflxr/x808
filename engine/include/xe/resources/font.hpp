//
// Created by FLXR on 9/22/2018.
//

#ifndef X808_FONT_HPP
#define X808_FONT_HPP


#include <vector>
#include <array>
#include <xe/common.hpp>
#include <xe/math/vec2.hpp>
#include <xe/gfx/texture.hpp>
#include <xe/utils/string.hpp>

namespace xe {

	struct Glyph {
		uint id;
		vec2 uv;
		vec2 texSize;
		vec2 offset;
		vec2 size;
		float xAdvance;

		std::vector<vec2> kernings;
	};

	class XE_API Font {
	public:
		explicit Font(const string &name, const wstring &path);
		virtual ~Font();

		const Glyph &get(uint id) const;

		inline const Texture *getAtlas() const { return atlas; }
		inline const string &getName() const { return name; }
		inline const wstring &getPath() const { return path; }

		static float getKerning(const Glyph &glyph, uint id);

	private:
		friend class FontLoader;

		string name;
		wstring path;

		const Texture *atlas;
		std::vector<Glyph> glyphs;
	};

}


#endif //X808_FONT_HPP
