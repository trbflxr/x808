//
// Created by FLXR on 7/2/2018.
//

#ifndef X808_FONT_HPP
#define X808_FONT_HPP


#include <string>
#include <xe/xeint.hpp>
#include <xe/common.hpp>
#include <xe/gfx/texture.hpp>
#include <xe/math/vec2.hpp>

namespace ftgl {
	struct texture_font_t;
	struct texture_atlas_t;
}


namespace xe {

	class XE_API Font {
	public:
		explicit Font(const string &name, const string &path, float size);
		explicit Font(const string &name, const byte *data, uint dataSize, float size);
		~Font();

		inline const string &getName() const { return name; }
		inline ftgl::texture_font_t *getFTFont() const { return ftFont; }
		inline float getSize() const { return size; }

		Texture *getTexture() const;

		vec2 getTextSize(const std::wstring_view &text, float fontSize, vec2 *position = nullptr) const;

	private:
		void updateAtlas() const;

	private:
		ftgl::texture_font_t *ftFont;
		ftgl::texture_atlas_t *ftAtlas;
		mutable Texture *texture;

		float size;
		string name;
	};

}


#endif //X808_FONT_HPP
