//
// Created by FLXR on 7/2/2018.
//

#include <freetype-gl/freetype-gl.h>
#include "font.hpp"
#include "utils/log.hpp"

xe::Font::Font(const std::string_view &path, float size) :
		size(size),
		texture(nullptr) {

	load(path, size);
}

xe::Font::~Font() {
	ftgl::texture_atlas_delete(ftAtlas);
	ftgl::texture_font_delete(ftFont);

	delete texture;
}

bool xe::Font::load(const std::string_view &path, float size) {
	XE_ASSERT(size <= 150, "Max font size is 150");

	Font::size = size;
	ftAtlas = ftgl::texture_atlas_new(1024, 1024, 2);
	ftFont = ftgl::texture_font_new_from_file(ftAtlas, Font::size = size, path.data());

	ftFont->outline_thickness = 0;
	ftFont->outline_type = 2;

	using namespace gfx::api;

	TextureParameters parameters = {TextureFormat::LUMINANCE_ALPHA, TextureFilter::NEAREST,
	                                TextureWrap::CLAMP_TO_EDGE};
	texture = new Texture2D(1024, 1024, parameters);
	texture->setData(ftAtlas->data);

	return static_cast<bool>(ftFont);
}

xe::vec2 xe::Font::getTextSize(const std::string_view &text, float fontSize, xe::vec2 *position) const {
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

xe::gfx::api::Texture2D *xe::Font::getTexture() const {
	updateAtlas();
	return texture;
}

void xe::Font::updateAtlas() const {
	if (ftAtlas->dirty) {
		texture->setData(ftAtlas->data);
		ftAtlas->dirty = false;
	}
}
