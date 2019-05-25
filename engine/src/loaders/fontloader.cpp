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

  static byte *readFile(const string &path, int64 *outMemorySize) {
    FILE *f = _wfopen(toWstring(path).c_str(), L"rb");
    if (!f) return nullptr;

    fseek(f, 0, SEEK_END);
    *outMemorySize = ftell(f);
    fseek(f, 0, SEEK_SET);

    byte *buff = new byte[*outMemorySize];

    fread(buff, *outMemorySize, 1, f);

    fclose(f);

    return buff;
  }

  bool FontLoader::load(Font *font, const char *file, float size, uint atlasSize) {
    string path(basePath);
    path += file;

    XE_CORE_TRACE("Loading: ", path);

    int64 memorySize;
    byte *memory = VFS::readFile(path, &memorySize);

    if (!memory) {
      XE_CORE_ERROR("[FontLoader]: unable to load font: '", path, "'");
      return false;
    }

    font->fontData = memory;

    font->atlas = texture_atlas_new(atlasSize, atlasSize, 1);
    font->font = texture_font_new_from_memory(static_cast<texture_atlas_t *>(font->atlas),
                                              size, font->fontData, memorySize);

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
