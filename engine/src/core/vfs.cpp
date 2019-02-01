//
// Created by FLXR on 1/31/2019.
//

#include <xe/core/vfs.hpp>
#include <xe/utils/log.hpp>
#include <xe/core/filesystem.hpp>

namespace xe {

	VFS *VFS::instance = nullptr;

	void VFS::init() {
		instance = new VFS();
	}

	void VFS::shutdown() {
		delete instance;
	}

	void VFS::mount(const string &virtualPath, const string &physicalPath) {
		XE_ASSERT(instance);
		instance->mountPoints[virtualPath].push_back(physicalPath);
	}

	void VFS::unmount(const string &path) {
		XE_ASSERT(instance);
		instance->mountPoints[path].clear();
	}

	bool VFS::resolvePhysicalPath(const string &path, string &outPhysicalPath) {
		if (path[0] != '/') {
			outPhysicalPath = path;
			return FileSystem::exists(path);
		}

		std::vector<string> dirs = splitString(path, L'/');
		const string &virtualDir = dirs.front();

		if (instance->mountPoints.find(virtualDir) == instance->mountPoints.end() ||
		    instance->mountPoints[virtualDir].empty())
			return false;

		string remainder = path.substr(virtualDir.size() + 1, path.size() - virtualDir.size());
		for (const string &physicalPath : instance->mountPoints[virtualDir]) {
			string p = physicalPath + remainder;
			if (FileSystem::exists(p)) {
				outPhysicalPath = p;
				return true;
			}
		}
		return false;
	}

	byte *VFS::readFile(const string &path) {
		XE_ASSERT(instance);
		string physicalPath;
		return resolvePhysicalPath(path, physicalPath) ? FileSystem::read(physicalPath) : nullptr;
	}

	string VFS::readTextFile(const string &path) {
		XE_ASSERT(instance);
		string physicalPath;
		return resolvePhysicalPath(path, physicalPath) ? FileSystem::readText(physicalPath) : nullptr;
	}

	bool VFS::writeFile(const string &path, byte *buffer) {
		XE_ASSERT(instance);
		string physicalPath;
		return resolvePhysicalPath(path, physicalPath) ? FileSystem::write(physicalPath, buffer) : false;
	}

}
