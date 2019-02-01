//
// Created by FLXR on 9/22/2018.
//

#ifndef X808_FONTLOADER_HPP
#define X808_FONTLOADER_HPP


#include <xe/resources/font.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

	class XE_API FontLoader : NonCopyable {
	public:
		static bool load(Font *font, const char *file, float size, uint atlasSize);
		static bool load(Font *font, const string &file, float size, uint atlasSize);

		static bool load(Font *font, const byte *data, size_t dataSize, float size, uint atlasSize);

	private:
		static constexpr const char *basePath = u8"/fonts/";
	};

}


#endif //X808_FONTLOADER_HPP
