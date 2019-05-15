//
// Created by FLXR on 2/26/2019.
//

#include <xe/gfx/textureatlas.hpp>
#include <xe/loaders/imageloader.hpp>
#include <xe/utils/logger.hpp>

namespace xe {

  TextureAtlas::TextureAtlas(const string &name, const string &path, const TextureParameters &params) :
      path(path),
      deleteTexture(true),
      texture(nullptr) {

    uint width;
    uint height;
    byte *data = ImageLoader::loadAtlas(path, &width, &height, areas, false);

    texture = new Texture(name, data, width, height, params);

    delete[] data;
  }

  TextureAtlas::TextureAtlas(const Texture *texture, const std::vector<std::pair<string, rect>> &areas) :
      path("NULL"),
      deleteTexture(false),
      texture(texture),
      areas(areas) { }

  TextureAtlas::~TextureAtlas() {
    delete texture;
  }

  const rect &TextureAtlas::getArea(const string &name) const {
    for (const auto &a : areas) {
      if (a.first == name) {
        return a.second;
      }
    }

    XE_CORE_ERROR("[TextureAtlas]: Area '", name, "' not found!");

    if (!areas.empty()) {
      if (areas[0].first == "error") {
        return areas[0].second;
      }
    }

    static rect zero;
    return zero;
  }

}
