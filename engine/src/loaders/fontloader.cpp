//
// Created by FLXR on 9/22/2018.
//

#include <freetype-gl/freetype-gl.h>
#include <xe/utils/log.hpp>
#include <xe/loaders/fontloader.hpp>
#include <embedded/embedded.hpp>

namespace xe {

	using namespace ftgl;

	bool FontLoader::load(Font *font, const char *path, float size, uint atlasSize) {
		size_t fileSize = 0;

		FILE *file = fopen(path, "rb");
		if (!file) {
			fclose(file);
			XE_ERROR(L"[FontLoader]: unable to load font: '", path, L"'");
			return false;
		}

		fseek(file, 0, SEEK_END);
		fileSize = static_cast<size_t>(ftell(file));
		fseek(file, 0, SEEK_SET);

		font->fontData = new byte[fileSize];

		fread(font->fontData, fileSize, 1, file);

		fclose(file);

		font->atlas = texture_atlas_new(atlasSize, atlasSize, 2);
		font->font = texture_font_new_from_memory(static_cast<texture_atlas_t *>(font->atlas),
		                                          size, font->fontData, fileSize);

		return true;
	}

	bool FontLoader::load(Font *font, const string &path, float size, uint atlasSize) {
		return load(font, path.c_str(), size, atlasSize);
	}

	bool FontLoader::load(Font *font, const byte *data, size_t dataSize, float size, uint atlasSize) {
		font->fontData = new byte[dataSize];
		memcpy(font->fontData, data, dataSize);

		font->atlas = texture_atlas_new(atlasSize, atlasSize, 2);
		font->font = texture_font_new_from_memory(static_cast<texture_atlas_t *>(font->atlas),
		                                          size, font->fontData, dataSize);

		return true;
	}

}
