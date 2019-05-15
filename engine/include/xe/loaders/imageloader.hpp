//
// Created by FLXR on 8/16/2018.
//

#ifndef X808_IMAGELOADER_HPP
#define X808_IMAGELOADER_HPP


#include <xe/xeint.hpp>
#include <xe/common.hpp>
#include <xe/string.hpp>
#include <xe/math/rect.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

  class XE_API ImageLoader : NonCopyable {
  private:
    struct Stamp {
      byte x;
      byte y;
      byte z;
      uint64 count;
    };

    struct AtlasEntry {
      uint64 nameSize;
      rect area;
    };

  public:
    static byte *load(const char *file,
                      uint *width = nullptr,
                      uint *height = nullptr,
                      uint *bits = nullptr,
                      bool *transparency = nullptr,
                      bool flip = false);

    static byte *load(const string &file,
                      uint *width = nullptr,
                      uint *height = nullptr,
                      uint *bits = nullptr,
                      bool *transparency = nullptr,
                      bool flip = false);


    static byte *loadAtlas(const string &file, uint *outWidth, uint *outHeight,
                           std::vector<std::pair<string, rect>> &outAreas, bool flip);

    static void packAtlas(const string &outPath, uint width, uint height,
                          const std::vector<std::pair<string, rect>> &sprites, byte *data, bool flip);

  private:
    static bool checkStamp(const Stamp &stamp) {
      return stamp.x == 0xDE && stamp.y == 0xAD && stamp.z == 0x21;
    }

  private:
    static constexpr const char *basePath = u8"/textures/";
  };

}


#endif //X808_IMAGELOADER_HPP
