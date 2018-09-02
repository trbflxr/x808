//
// Created by FLXR on 7/3/2018.
//

#ifndef X808_FONTMANAGER_HPP
#define X808_FONTMANAGER_HPP


#include <unordered_map>
#include <xe/common.hpp>
#include <xe/utils/noncopyable.hpp>
#include <xe/resources/font.hpp>

namespace xe {

	//todo: different default font with utf8 support

	class XE_API FontManager : NonCopyable {
	public:
		~FontManager() override;

		static bool add(Font *font);
		static const Font *get(const string &name);

		static void clean();

	private:
		FontManager();

		static FontManager &instance();

	private:
		std::unordered_map<string, const Font *> fonts;
	};

}

#define GETFONT(name) xe::FontManager::get(name)


#endif //X808_FONTMANAGER_HPP
