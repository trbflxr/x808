//
// Created by FLXR on 9/22/2018.
//

#ifndef X808_FONTLOADER_HPP
#define X808_FONTLOADER_HPP


#include <xe/resources/font.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

	struct XE_API FontLoader : NonCopyable {
		static bool load(Font *font, const wchar_t *path, float size, uint atlasSize);
		static bool load(Font *font, const wstring &path, float size, uint atlasSize);

		static bool load(Font *font, const byte *data, size_t dataSize, float size, uint atlasSize);
	};

}


#endif //X808_FONTLOADER_HPP
