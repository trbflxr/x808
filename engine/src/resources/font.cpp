//
// Created by FLXR on 7/2/2018.
//

#include <freetype-gl/freetype-gl.h>
#include "font.hpp"
#include "utils/log.hpp"
#include "embedded/embedded.hpp"

namespace xe {

	Font::Font(const std::string_view &name, const std::string_view &path, float size) :
			name(name),
			size(size),
			texture(nullptr) {

		using namespace gfx::api;

		XE_ASSERT(size <= 150, "Max font size is 150");

		ftAtlas = ftgl::texture_atlas_new(1024, 1024, 2);
		ftFont = ftgl::texture_font_new_from_file(ftAtlas, size, path.data());

		if (!ftFont) {
			XE_ERROR("Could not load font: ", path.data());
			ftFont = ftgl::texture_font_new_from_memory(ftAtlas, size,
			                                            internal::DEFAULT_FONT, internal::DEFAULT_FONT_SIZE);
		}

		ftFont->outline_thickness = 0;
		ftFont->outline_type = 2;

		TextureParameters parameters = {TextureFormat::LUMINANCE_ALPHA, TextureFilter::NEAREST,
		                                TextureWrap::CLAMP_TO_EDGE};
		texture = Texture2D::create(1024, 1024, parameters);
		texture->setData(ftAtlas->data);
	}

	Font::Font(const std::string_view &name, const byte *data, uint dataSize, float size) :
			name(name),
			size(size),
			texture(nullptr) {

		using namespace gfx::api;

		XE_ASSERT(size <= 150, "Max font size is 150");

		ftAtlas = ftgl::texture_atlas_new(1024, 1024, 2);
		ftFont = ftgl::texture_font_new_from_memory(ftAtlas, size, data, dataSize);

		TextureParameters parameters = {TextureFormat::LUMINANCE_ALPHA, TextureFilter::NEAREST,
		                                TextureWrap::CLAMP_TO_EDGE};
		texture = Texture2D::create(1024, 1024, parameters);
		texture->setData(ftAtlas->data);

		XE_ASSERT(ftFont, "Failed to load font from data!");
	}

	Font::~Font() {
		ftgl::texture_atlas_delete(ftAtlas);
		ftgl::texture_font_delete(ftFont);

		delete texture;
	}

	vec2 Font::getTextSize(const std::string_view &text, float fontSize, vec2 *position) const {
		const float scale = size / fontSize;

		float x = 0.0f;
		float y = 0.0f;

		for (unsigned i = 0; i < text.length(); i++) {
			auto *glyph = ftgl::texture_font_get_glyph(ftFont, text[i]);

			if (i > 0) {
				float kerning = ftgl::texture_glyph_get_kerning(glyph, text[i - 1]);
				x += kerning;
			}

			const float height = glyph->height - ftFont->descender;
			y = y > height ? y : height;

			x += glyph->advance_x;
		}

		if (position) {
			position->y += ftFont->descender / scale;
		}

		return {x / scale, y / scale};
	}

	gfx::api::Texture2D *Font::getTexture() const {
		updateAtlas();
		return texture;
	}

	void Font::updateAtlas() const {
		if (ftAtlas->dirty) {
			texture->setData(ftAtlas->data);
			ftAtlas->dirty = false;
		}
	}

}