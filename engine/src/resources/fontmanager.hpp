//
// Created by FLXR on 7/3/2018.
//

#ifndef X808_FONTMANAGER_HPP
#define X808_FONTMANAGER_HPP


#include <unordered_map>
#include "common.hpp"
#include "utils/noncopyable.hpp"
#include "resources/font.hpp"

namespace xe {

	class XE_API FontManager : NonCopyable {
	public:
		~FontManager() override;

		static void add(Font *font);
		static const Font *get(const std::string_view &name);

		static void clean();

	private:
		FontManager();

		static FontManager &instance();

	private:
		std::unordered_map<std::string, Font *> fonts;
	};

}

#define GETFONT(name) xe::FontManager::get(name)


#endif //X808_FONTMANAGER_HPP
