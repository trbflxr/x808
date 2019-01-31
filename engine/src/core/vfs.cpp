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

	void VFS::mount(const wstring &virtualPath, const wstring &physicalPath) {
		XE_ASSERT(instance);
		instance->mountPoints[virtualPath].push_back(physicalPath);
	}

	void VFS::unmount(const wstring &path) {
		XE_ASSERT(instance);
		instance->mountPoints[path].clear();
	}

	bool VFS::resolvePhysicalPath(const wstring &path, wstring &outPhysicalPath) {
		if (path[0] != '/') {
			outPhysicalPath = path;
			return FileSystem::exists(path);
		}

		std::vector<wstring> dirs = utils::splitString(path, L'/');
		const wstring &virtualDir = dirs.front();

		if (instance->mountPoints.find(virtualDir) == instance->mountPoints.end() ||
		    instance->mountPoints[virtualDir].empty())
			return false;

		wstring remainder = path.substr(virtualDir.size() + 1, path.size() - virtualDir.size());
		for (const wstring &physicalPath : instance->mountPoints[virtualDir]) {
			wstring p = physicalPath + remainder;
			if (FileSystem::exists(p)) {
				outPhysicalPath = p;
				return true;
			}
		}
		return false;
	}

	byte *VFS::readFile(const wstring &path) {
		XE_ASSERT(instance);
		wstring physicalPath;
		return resolvePhysicalPath(path, physicalPath) ? FileSystem::read(physicalPath) : nullptr;
	}

	bool VFS::writeFile(const wstring &path, byte *buffer) {
		XE_ASSERT(instance);
		wstring physicalPath;
		return resolvePhysicalPath(path, physicalPath) ? FileSystem::write(physicalPath, buffer) : false;
	}

}
