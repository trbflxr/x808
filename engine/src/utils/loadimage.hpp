//
// Created by FLXR on 6/30/2018.
//

#ifndef X808_LOADIMAGE_HPP
#define X808_LOADIMAGE_HPP


#include <string>
#include "xeint.hpp"
#include "common.hpp"

namespace xe { namespace utils {

	XE_API byte *loadImage(const char *path, uint *width = nullptr, uint *height = nullptr,
	                       uint *bits = nullptr, bool flipY = false);

	XE_API byte *loadImage(const std::string_view &path, uint *width = nullptr, uint *height = nullptr,
	                       uint *bits = nullptr, bool flipY = false);

}}


#endif //X808_LOADIMAGE_HPP
