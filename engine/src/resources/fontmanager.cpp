//
// Created by FLXR on 7/3/2018.
//

#include "fontmanager.hpp"
#include "utils/log.hpp"
#include "../../embedded/embedded.hpp"

xe::FontManager::FontManager() {
	fonts.emplace("default", new Font("default", internal::DEFAULT_FONT, internal::DEFAULT_FONT_SIZE, 100));
}

xe::FontManager::~FontManager() {
	clear();
}

xe::FontManager &xe::FontManager::instance() {
	static FontManager fm;
	return fm;
}

void xe::FontManager::add(xe::Font *font) {
	auto &&it = instance().fonts.find(font->getName());

	if (it != instance().fonts.end()) {
		XE_ERROR(font->getName(), " already exist!");
		return;
	}

	instance().fonts.emplace(font->getName(), font);
}

const xe::Font &xe::FontManager::get(const std::string_view &name) {
	auto &&it = instance().fonts.find(name.data());
	if (it == instance().fonts.end()) {
		XE_ERROR("Font '", name, "' not found! Default font loaded instead.");

		return get("default");
	}

	return *it->second;
}

void xe::FontManager::clear() {
	instance().fonts.clear();
}