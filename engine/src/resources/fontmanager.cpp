//
// Created by FLXR on 7/3/2018.
//

#include <new>
#include <xe/resources/fontmanager.hpp>
#include <xe/utils/log.hpp>
#include <embedded/embedded.hpp>

namespace xe {

	FontManager::FontManager() {
		//todo:
//		fonts.emplace("default", new Font("default", internal::DEFAULT_FONT, internal::DEFAULT_FONT_SIZE, 100));
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
			XE_ERROR("[FontManager]: font '", font->getName(), "' already exist and be deleted");

			delete font;
			return false;
		}

		instance().fonts.emplace(font->getName(), font);
		return true;
	}

	const Font *FontManager::get(const string &name) {
		auto &&it = instance().fonts.find(name);
		if (it == instance().fonts.end()) {
			XE_ERROR("[FontManager]: font '", name, "' not found! Default font loaded instead.");

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