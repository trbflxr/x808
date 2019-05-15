//
// Created by FLXR on 9/22/2018.
//

#include <freetype-gl/freetype-gl.h>
#include <xe/utils/logger.hpp>
#include <xe/core/vfs.hpp>
#include <xe/loaders/fontloader.hpp>
#include <embedded/embedded.hpp>

namespace xe {

  using namespace ftgl;

  bool FontLoader::load(Font *font, const char *file, float size, uint atlasSize) {
    string path(basePath);
    path += file;

    int64 fileSize;
    byte *data = VFS::readFile(path, &fileSize);

    if (!data) {
      XE_CORE_ERROR("[FontLoader]: unable to load font: '", path, "'");
      return false;
    }

    font->fontData = data;

    font->atlas = texture_atlas_new(atlasSize, atlasSize, 1);
    font->font = texture_font_new_from_memory(static_cast<texture_atlas_t *>(font->atlas),
                                              size, font->fontData, fileSize);

    return true;
  }

  bool FontLoader::load(Font *font, const string &file, float size, uint atlasSize) {
    return load(font, file.c_str(), size, atlasSize);
  }

  bool FontLoader::load(Font *font, const byte *data, size_t dataSize, float size, uint atlasSize) {
    font->fontData = new byte[dataSize];
    memcpy(font->fontData, data, dataSize);

    font->atlas = texture_atlas_new(atlasSize, atlasSize, 1);
    font->font = texture_font_new_from_memory(static_cast<texture_atlas_t *>(font->atlas),
                                              size, font->fontData, dataSize);

    return true;
  }

}
