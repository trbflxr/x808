//
// Created by FLXR on 8/16/2018.
//

#ifndef X808_IMAGELOADER_HPP
#define X808_IMAGELOADER_HPP


#include <string>
#include "xeint.hpp"
#include "common.hpp"
#include "utils/noncopyable.hpp"

namespace xe {

	struct XE_API ImageLoader : NonCopyable {
		static byte *load(const char *path, uint *width = nullptr, uint *height = nullptr,
		                  uint *bits = nullptr, bool flipY = false);

		static byte *load(const std::string_view &path, uint *width = nullptr, uint *height = nullptr,
		                  uint *bits = nullptr, bool flipY = false);
	};

}


#endif //X808_IMAGELOADER_HPP
