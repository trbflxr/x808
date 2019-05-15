//
// Created by FLXR on 1/31/2019.
//

#include <algorithm>
#include <xe/core/vfs.hpp>
#include <xe/utils/logger.hpp>
#include <xe/utils/assert.hpp>
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

  void VFS::unmount(const string &virtualPath, const string &physicalPath) {
    XE_ASSERT(instance);

    std::vector<string> &temp = instance->mountPoints[virtualPath];
    temp.erase(std::remove_if(temp.begin(), temp.end(),
                              [&](const string &pp) { return pp == physicalPath; }
               ),
               temp.end());
  }

  void VFS::unmount(const string &virtualPath) {
    XE_ASSERT(instance);
    instance->mountPoints[virtualPath].clear();
  }

  bool VFS::resolvePhysicalPath(const string &path, string &outPhysicalPath) {
    if (path[0] != '/') {
      outPhysicalPath = path;
      return FileSystem::exists(path);
    }

    std::vector<string> dirs = splitString(path, '/');
    const string &virtualDir = dirs.front();

    if (instance->mountPoints.find(virtualDir) == instance->mountPoints.end() ||
        instance->mountPoints[virtualDir].empty()) {
      return false;
    }

    string remainder = path.substr(virtualDir.size() + 2, path.size() - virtualDir.size() - 1);
    for (const string &physicalPath : instance->mountPoints[virtualDir]) {
      string p = (physicalPath != "/" ? physicalPath : "") + remainder;
      if (FileSystem::exists(p)) {
        outPhysicalPath = p;
        return true;
      }
    }
    return false;
  }

  byte *VFS::readFile(const string &path, int64 *outSize) {
    XE_ASSERT(instance);
    string physicalPath;

    if (resolvePhysicalPath(path, physicalPath)) {
      return FileSystem::read(physicalPath, outSize);
    } else {
      return nullptr;
    }
  }

  bool VFS::readTextFile(const string &path, string &outString) {
    XE_ASSERT(instance);
    string physicalPath;

    if (resolvePhysicalPath(path, physicalPath)) {
      return FileSystem::readText(physicalPath, outString);
    } else {
      outString = "";
      return false;
    }
  }

  bool VFS::writeFile(const string &path, byte *buffer, uint64 size) {
    XE_ASSERT(instance);
    string physicalPath;
    return resolvePhysicalPath(path, physicalPath) ? FileSystem::write(physicalPath, buffer, size) : false;
  }

}
