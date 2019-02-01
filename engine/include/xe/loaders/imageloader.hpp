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

	class XE_API ImageLoader : NonCopyable {
	public:
		static byte *load(const char *file, uint *width = nullptr, uint *height = nullptr, uint *bits = nullptr);
		static byte *load(const string &file, uint *width = nullptr, uint *height = nullptr, uint *bits = nullptr);

	private:
		static constexpr const char *basePath = u8"/textures/";
	};

}


#endif //X808_IMAGELOADER_HPP
