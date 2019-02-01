//
// Created by FLXR on 8/16/2018.
//

#ifndef X808_IMAGELOADER_HPP
#define X808_IMAGELOADER_HPP


#include <xe/xeint.hpp>
#include <xe/common.hpp>
#include <xe/utils/noncopyable.hpp>
#include <xe/string.hpp>

namespace xe {

	struct XE_API ImageLoader : NonCopyable {
		static byte *load(const char *path, uint *width = nullptr, uint *height = nullptr, uint *bits = nullptr);
		static byte *load(const string &path, uint *width = nullptr, uint *height = nullptr, uint *bits = nullptr);
	};

}


#endif //X808_IMAGELOADER_HPP
