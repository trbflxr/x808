//
// Created by FLXR on 7/3/2018.
//

#include <xe/utils/logger.hpp>
#include <embedded/embedded.hpp>
#include <xe/resources/fontmanager.hpp>

namespace xe {

  FontManager::FontManager() {
    fonts.emplace("default", new Font("default", internal::DEFAULT_FONT_DATA,
                                      internal::DEFAULT_FONT_DATA_SIZE, 50, false));
  }

  FontManager::~FontManager() {
    clean();
  }

  void FontManager::init() {
    instance();
  }

  FontManager &FontManager::instance() {
    static FontManager fm;
    return fm;
  }

  bool FontManager::add(Font *font) {
    auto &&it = instance().fonts.find(font->getName());

    if (it != instance().fonts.end()) {
      XE_CORE_ERROR("[FontManager]: font '", font->getName(), "' already exist and be deleted");

      delete font;
      return false;
    }

    instance().fonts.emplace(font->getName(), font);
    return true;
  }

  const Font *FontManager::get(const string &name) {
    auto &&it = instance().fonts.find(name);
    if (it == instance().fonts.end()) {
      XE_CORE_ERROR("[FontManager]: font '", name, "' not found! Default font loaded instead.");

      return get("default");
    }

    return it->second;
  }

  void FontManager::clean() {
    for (auto &&font : instance().fonts) {
      delete font.second;
    }
  }

}