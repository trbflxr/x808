//
// Created by FLXR on 9/29/2018.
//

#include <xe/utils/logger.hpp>
#include <xe/core/vfs.hpp>
#include <xe/loaders/shaderloader.hpp>

namespace xe {

  string ShaderLoader::load(const string &file) {
    return load(file.c_str());
  }

  string ShaderLoader::load(const char *file) {
    string path(basePath);
    path += file;

    string source;
    if (!VFS::readTextFile(path, source)) {
      XE_CORE_ERROR("[ShaderFile]: file '", path, "' not found.");
    }

    return source;
  }

}
