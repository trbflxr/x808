//
// Created by FLXR on 8/16/2018.
//

#include <xe/utils/logger.hpp>
#include <xe/core/vfs.hpp>
#include <xe/core/filesystem.hpp>
#include <xe/loaders/imageloader.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace xe {

  byte *ImageLoader::load(const char *file, uint *width, uint *height, uint *bits, bool *transparency, bool flip) {
    string path(file);

    if (!FileSystem::exists(path)) {
      path.insert(0, basePath);
    }

    XE_CORE_TRACE("Loading: ", path);

    int64 memorySize;
    byte *memory = VFS::readFile(path, &memorySize);

    if (!memory) {
      XE_CORE_ERROR("[ImageLoader]: unable to load image: '", path, "'");
      return nullptr;
    }

    int32 w;
    int32 h;
    int32 bpp;

    stbi_set_flip_vertically_on_load(flip);
    byte *data = stbi_load_from_memory(memory, memorySize, &w, &h, &bpp, STBI_rgb_alpha);

    delete[] memory;

    if (width) *width = (uint) w;
    if (height) *height = (uint) h;
    if (bits) *bits = (uint) bpp * 8;

    if (transparency) {
      *transparency = false;
      for (int32 i = 3; i < w * h; i += 4) {
        if (data[i] < 255) {
          *transparency = true;
          break;
        }
      }
    }

    return data;
  }

  byte *ImageLoader::load(const string &file, uint *width, uint *height, uint *bits, bool *transparency, bool flip) {
    return load(file.c_str(), width, height, bits, transparency, flip);
  }

  void ImageLoader::packAtlas(const string &outPath, uint width, uint height,
                              const std::vector<std::pair<string, rect>> &sprites, byte *data, bool flip) {

    Stamp stamp;
    stamp.x = 0xDE;
    stamp.y = 0xAD;
    stamp.z = 0x21;
    stamp.count = sprites.size();

    int32 dataSize = 0;
    stbi_flip_vertically_on_write(flip);
    const byte *img = stbi_write_png_to_mem(data, 0, width, height, 4, &dataSize);

    uint64 totalNamesSize = 0;
    for (const auto &s : sprites) {
      totalNamesSize += s.first.size();
    }

    uint64 index = 0;
    byte *buffer = new byte[sizeof(Stamp) + sizeof(AtlasEntry) * sprites.size()
                            + totalNamesSize + sizeof(int32) + dataSize];

    memcpy(buffer + index, &stamp, sizeof(Stamp));
    index += sizeof(Stamp);

    for (const auto &s : sprites) {
      AtlasEntry e;
      e.nameSize = s.first.size();
      e.area = s.second;

      memcpy(buffer + index, &e, sizeof(AtlasEntry));
      index += sizeof(AtlasEntry);

      memcpy(buffer + index, s.first.c_str(), e.nameSize);
      index += e.nameSize;
    }

    memcpy(buffer + index, &dataSize, sizeof(int32));
    index += sizeof(int32);

    memcpy(buffer + index, img, static_cast<uint64>(dataSize));
    index += dataSize;

    bool result = FileSystem::write(outPath, buffer, index);

    if (!result) {
      XE_CORE_ERROR("[ImageLoader]: Unable to write file '", outPath, "'");
    }

    delete[] buffer;
  }

  byte *ImageLoader::loadAtlas(const string &file, uint *outWidth, uint *outHeight,
                               std::vector<std::pair<string, rect>> &outAreas, bool flip) {

    string path(file);

    if (!FileSystem::exists(path)) {
      path.insert(0, basePath);
    }

    XE_CORE_TRACE("Loading: ", path);

    int64 memorySize;
    uint64 index = 0;
    byte *buffer = VFS::readFile(path, &memorySize);

    if (!buffer) {
      XE_CORE_ERROR("[ImageLoader]: unable to load image: '", path, "'");
      return nullptr;
    }

    Stamp s;
    memset(&s, 0, sizeof(Stamp));
    memcpy(&s, buffer + index, sizeof(Stamp));
    index += sizeof(Stamp);

    if (!checkStamp(s)) {
      XE_CORE_ERROR("[ImageLoader]: Bad file format '", file, "'");
      return nullptr;
    }

    for (uint64 i = 0; i < s.count; ++i) {
      AtlasEntry e;
      memset(&e, 0, sizeof(AtlasEntry));
      memcpy(&e, buffer + index, sizeof(AtlasEntry));
      index += sizeof(AtlasEntry);

      string name(e.nameSize, '\0');
      rect r = e.area;

      memcpy(name.data(), buffer + index, e.nameSize);
      index += e.nameSize;

      outAreas.emplace_back(name, r);
    }

    int32 size = 0;
    memcpy(&size, buffer + index, sizeof(int32));
    index += sizeof(int32);

    byte *data = new byte[size];
    memcpy(data, buffer + index, size);

    delete[] buffer;

    int32 w;
    int32 h;
    int32 bpp;

    stbi_set_flip_vertically_on_load(flip);
    byte *img = stbi_load_from_memory(data, size, &w, &h, &bpp, STBI_rgb_alpha);

    delete[] data;

    *outWidth = (uint) w;
    *outHeight = (uint) h;

    return img;
  }

}
