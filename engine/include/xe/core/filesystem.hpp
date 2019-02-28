//
// Created by FLXR on 1/31/2019.
//

#ifndef X808_FILESYSTEM_HPP
#define X808_FILESYSTEM_HPP


#include <xe/string.hpp>
#include <xe/utils/noncopyable.hpp>
#include <xe/xeint.hpp>

namespace xe {

	class XE_API FileSystem : NonCopyable {
	public:
		static bool exists(const string &file);
		static int64 size(const string &file);

		static byte *read(const string &file, int64 *outSize = nullptr);
		static bool read(const string &file, void *buff, int64 size = -1);
		static bool readText(const string &file, string &outString);

		static bool write(const string &file, void *buff, uint64 size);

		static string getWorkingDirectory();

		static std::vector<string> getLogicalDrives();

		static void updateVolumes() { get().shouldUpdateVolumes = true; }

	private:
		explicit FileSystem();

		static FileSystem &get();

	private:
		bool shouldUpdateVolumes;
	};

}


#endif //X808_FILESYSTEM_HPP
