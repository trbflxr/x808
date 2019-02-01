//
// Created by FLXR on 1/31/2019.
//

#ifndef X808_VFS_HPP
#define X808_VFS_HPP


#include <unordered_map>
#include <xe/string.hpp>
#include <xe/common.hpp>

namespace xe {

	class XE_API VFS {
	public:
		static void mount(const string &virtualPath, const string &physicalPath);
		static void unmount(const string &path);

		static bool resolvePhysicalPath(const string &path, string &outPhysicalPath);

		static byte *readFile(const string &path);
		static string readTextFile(const string &path);

		static bool writeFile(const string &path, byte *buffer);

		static void init();
		static void shutdown();

	private:
		std::unordered_map<string, std::vector<string>> mountPoints;

		static VFS *instance;
	};

}


#endif //X808_VFS_HPP
