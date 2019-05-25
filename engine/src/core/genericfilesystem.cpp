//
// Created by FLXR on 5/25/2019.
//

//
// Created by FLXR on 1/31/2019.
//


#include <algorithm>
#include <xe/core/filesystem.hpp>

namespace xe {

#ifdef XE_USE_GENERIC_FS
  static FILE *openFileForReading(const string &path) {
    return _wfopen(toWstring(path).c_str(), L"rb");
  }

  static int64 getFileSizeInternal(FILE *file) {
    int64 size;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
  }

  static bool readFileInternal(FILE *file, void *buffer, int64 size) {
    fread(buffer, size, 1, file);
    return true;
  }

  FileSystem::FileSystem() :
      shouldUpdateVolumes(true) { }

  FileSystem &FileSystem::get() {
    static FileSystem fs;
    return fs;
  }

  bool FileSystem::exists(const string &file) {
    FILE *f = openFileForReading(file);
    if (f) {
      fclose(f);
      return true;
    }

    return false;
  }

  int64 FileSystem::size(const string &file) {
    FILE *f = openFileForReading(file);
    if (!f) return -1;

    int64 size = getFileSizeInternal(f);

    fclose(f);
    return size;
  }

  byte *FileSystem::read(const string &file, int64 *outSize) {
    FILE *handle = openFileForReading(file);
    int64 size = getFileSizeInternal(handle);
    byte *buffer = new byte[size];

    bool success = readFileInternal(handle, buffer, size);
    fclose(handle);

    if (!success) {
      delete[] buffer;
      return nullptr;
    }

    if (outSize) {
      *outSize = size;
    }

    return buffer;
  }

  bool FileSystem::read(const string &file, void *buff, int64 size) {
    FILE *handle = openFileForReading(file);
    if (!handle) return false;

    if (size < 0) {
      size = getFileSizeInternal(handle);
    }

    bool success = readFileInternal(handle, buff, size);
    fclose(handle);

    return success;
  }

  bool FileSystem::readText(const string &file, string &outString) {
    FILE* handle = openFileForReading(file);
    int64 size = getFileSizeInternal(handle);
    string buffer(static_cast<uint64>(size), '\0');

    bool success = readFileInternal(handle, &buffer[0], size);
    fclose(handle);

    if (success) {
      buffer.erase(std::remove(buffer.begin(), buffer.end(), '\r'), buffer.end());
      outString = buffer;
      return true;
    } else {
      return false;
    }
  }

  bool FileSystem::write(const string &file, void *buff, uint64 size) {
    FILE *f = _wfopen(toWstring(file).c_str(), L"wb");
    if (!f) return false;

    fwrite(buff, size, 1, f);
    fclose(f);

    return true;
  }
#endif //XE_USE_GENERIC_FS

}