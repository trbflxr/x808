//
// Created by FLXR on 1/31/2019.
//

#ifndef X808_VFS_HPP
#define X808_VFS_HPP


#include <unordered_map>
#include <xe/utils/string.hpp>
#include <xe/common.hpp>

namespace xe {

	class XE_API VFS {
	public:
		static void mount(const wstring &virtualPath, const wstring &physicalPath);
		static void unmount(const wstring &path);

		static bool resolvePhysicalPath(const wstring &path, wstring &outPhysicalPath);

		static byte *readFile(const wstring &path);

		static bool writeFile(const wstring &path, byte *buffer);

		static void init();
		static void shutdown();

	private:
		std::unordered_map<wstring, std::vector<wstring>> mountPoints;

		static VFS *instance;
	};

}


#endif //X808_VFS_HPP
