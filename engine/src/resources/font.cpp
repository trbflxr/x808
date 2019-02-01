//
// Created by FLXR on 9/26/2018.
//


#include <freetype-gl/freetype-gl.h>
#include <xe/utils/log.hpp>
#include <xe/loaders/fontloader.hpp>
#include <xe/resources/font.hpp>

namespace xe {

	Font::Font(const string &name, const string &path, float size) :
			name(name),
			path(path),
			size(size * 1.3f),
			texture(nullptr),
			deleteFontData(true),
			fontData(nullptr) {

		const uint atlasSize = computeAtlasSize(size);

		if (!FontLoader::load(this, path, Font::size, atlasSize)) {
			XE_ASSERT(false);
		}

		createAtlas(atlasSize);
	}

	Font::Font(const string &name, const byte *data, uint dataSize, float size, bool deleteData) :
			name(name),
			path("NULL"),
			size(size * 1.3f),
			texture(nullptr),
			deleteFontData(deleteData),
			fontData(nullptr) {

		const uint atlasSize = computeAtlasSize(size);

		if (!FontLoader::load(this, data, dataSize, Font::size, atlasSize)) {
			XE_ASSERT(false);
		}

		createAtlas(atlasSize);
	}

	Font::~Font() {
		texture_atlas_delete(static_cast<ftgl::texture_atlas_t *>(atlas));
		texture_font_delete(static_cast<ftgl::texture_font_t *>(font));

		delete texture;

		if (deleteFontData) delete[] fontData;
	}

	void Font::createAtlas(uint size) {
		//create texture
		static TextureParameters params(TextureTarget::Tex2D,
		                                PixelInternalFormat::LuminanceAlpha,
		                                PixelFormat::LuminanceAlpha,
		                                PixelType::UnsignedByte);

		texture = new Texture(name + "_FontTexture", size, size, 0, params);
		texture->setData2D(static_cast<ftgl::texture_atlas_t *>(atlas)->data);
	}

	const Texture *Font::getTexture() const {
		updateAtlas();
		return texture;
	}

	void Font::updateAtlas() const {
		ftgl::texture_atlas_t *a = static_cast<ftgl::texture_atlas_t *>(atlas);

		if (a->dirty) {
			texture->setData2D(a->data);
			a->dirty = false;
		}
	}

	void *Font::getGlyph(int32 code) const {
		return texture_font_get_glyph(static_cast<ftgl::texture_font_t *>(font), code);
	}

	float Font::getKerning(void *glyph, int32 c) const {
		return texture_glyph_get_kerning(static_cast<ftgl::texture_glyph_t *>(glyph), c);
	}

	void Font::setOutlineThickness(float thickness) const {
		static_cast<ftgl::texture_font_t *>(font)->outline_thickness = thickness;
	}

	void Font::setOutlineType(int32 type) const {
		static_cast<ftgl::texture_font_t *>(font)->outline_type = type;
	}

	uint Font::computeAtlasSize(float fontSize) {
		if (fontSize <= 50) return 1024;
		if (fontSize <= 100) return 2048;
		if (fontSize <= 150) return 4096;
		if (fontSize <= 200) return 8192;
		return 8192;
	}

}