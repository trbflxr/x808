//
// Created by FLXR on 1/31/2019.
//

#ifndef X808_FILESYSTEM_HPP
#define X808_FILESYSTEM_HPP


#include <xe/utils/string.hpp>
#include <xe/utils/noncopyable.hpp>
#include <xe/xeint.hpp>

namespace xe {

	class FileSystem : NonCopyable {
	public:
		static bool exists(const wstring &file);
		static int64 size(const wstring &file);

		static byte *read(const wstring &file);
		static bool read(const wstring &file, void *buff, int64 size = -1);

		static bool write(const wstring &file, void *buff);
	};

}


#endif //X808_FILESYSTEM_HPP
