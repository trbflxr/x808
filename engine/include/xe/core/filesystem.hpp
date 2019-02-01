//
// Created by FLXR on 1/31/2019.
//

#ifndef X808_FILESYSTEM_HPP
#define X808_FILESYSTEM_HPP


#include <xe/string.hpp>
#include <xe/utils/noncopyable.hpp>
#include <xe/xeint.hpp>

namespace xe {

	class FileSystem : NonCopyable {
	public:
		static bool exists(const string &file);
		static int64 size(const string &file);

		static byte *read(const string &file);
		static bool read(const string &file, void *buff, int64 size = -1);
		static string readText(const string &file);

		static bool write(const string &file, void *buff);
	};

}


#endif //X808_FILESYSTEM_HPP
