//
// Created by FLXR on 9/22/2018.
//

#ifndef X808_FONTLOADER_HPP
#define X808_FONTLOADER_HPP


#include <array>
#include <unordered_map>
#include <xe/utils/string.hpp>
#include <xe/utils/noncopyable.hpp>
#include <xe/resources/font.hpp>

namespace xe {

	class XE_API FontLoader : NonCopyable {
	public:
		explicit FontLoader(Font *font);
		explicit FontLoader(const string &name);

		bool load(bool fromFile = true);

		Font *getFont() const { return font; }

	private:
		int32 get(const string &key);

		void parseLine(const string &line);
		void parsePadding(const string &line);
		Glyph parseGlyph();

		bool loadAtlas(const string &line);
		void loadEmbedAtlas();

		bool readFile();
		void loadEmbed();

	private:
		Font *font;

		std::vector<string> lines;
		std::unordered_map<string, string> values;

		std::array<int32, 4> padding;
		int32 paddingWidth;
		int32 paddingHeight;

		uint atlasSize;
		uint charsCount;
	};

}


#endif //X808_FONTLOADER_HPP
