//
// Created by FLXR on 7/3/2018.
//

#ifndef X808_FONTMANAGER_HPP
#define X808_FONTMANAGER_HPP


#include <unordered_map>
#include "common.hpp"
#include "resources/font.hpp"

namespace xe {

	class XE_API FontManager {
	public:
		~FontManager();

		static void add(Font *font);
		static const Font &get(const std::string_view &name);

		static void clean();

		NULL_COPY_AND_ASSIGN(FontManager);

	private:
		FontManager();

		static FontManager &instance();

	private:
		std::unordered_map<std::string, Font *> fonts;
	};

}

#define GETFONT(name) xe::FontManager::get(name)


#endif //X808_FONTMANAGER_HPP
