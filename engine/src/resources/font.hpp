//
// Created by FLXR on 7/2/2018.
//

#ifndef X808_FONT_HPP
#define X808_FONT_HPP


#include <string>
#include "xeint.hpp"
#include "common.hpp"
#include "math/vec2.hpp"
#include "gfx/api/texture2d.hpp"

namespace ftgl {
	struct texture_font_t;
	struct texture_atlas_t;
}


namespace xe {

	class XE_API Font {
	public:
		explicit Font(const std::string_view &name, const std::string_view &path, float size);
		explicit Font(const std::string_view &name, const byte *data, uint dataSize, float size);
		virtual ~Font();

		inline const std::string &getName() const { return name; }
		inline ftgl::texture_font_t *getFTFont() const { return ftFont; }
		inline float getSize() const { return size; }

		gfx::api::Texture2D *getTexture() const;

		vec2 getTextSize(const std::wstring_view &text, float fontSize, vec2 *position = nullptr) const;

	private:
		void updateAtlas() const;

	private:
		ftgl::texture_font_t *ftFont;
		ftgl::texture_atlas_t *ftAtlas;
		mutable gfx::api::Texture2D *texture;

		float size;
		std::string name;
	};

}


#endif //X808_FONT_HPP
