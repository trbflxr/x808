//
// Created by FLXR on 2/25/2019.
//

#include <xetools/spak.hpp>
#include <libgen.h>
#include <cstring>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace xe {

  std::string spak::getFileName(const std::string &str, bool includeExt) {
    std::string temp = str;
    char *s = basename(temp.data());

    size_t size = strlen(s);

    if (!includeExt) {
      int lastDot = -1;

      for (size_t i = 0; i < size; ++i) {
        if (s[i] == '.') {
          lastDot = static_cast<int>(i);
        }
      }

      if (lastDot != -1) {
        s[lastDot] = '\0';
      }
    }

    return s;
  }

  std::unordered_map<string, string> spak::unpackShaders(const string &path) {
    std::unordered_map<string, string> shaders;

    //file
    std::ifstream fin(path, std::ios::in | std::ios::binary);
    if (!fin.is_open()) {
      fprintf(stderr, "Bad input file: %s\n", path.c_str());
      return shaders;
    }


    //read stamp
    Stamp s;
    memset(&s, 0, sizeof(Stamp));
    fin.read((char *) &s, sizeof(Stamp));

    if (!checkStamp(s)) {
      fprintf(stderr, "Bad file format\n");
      fin.close();
      return shaders;
    }

    for (size_t i = 0; i < s.count; ++i) {
      ShaderEntry entry{ };
      memset(&entry, 0, sizeof(ShaderEntry));
      fin.read((char *) &entry, sizeof(ShaderEntry));

      size_t nameSize = entry.nameSize;
      size_t dataSize = entry.dataSize;

      char *nameBuff = new char[nameSize + 1];
      nameBuff[nameSize] = '\0';

      char *dataBuff = new char[dataSize + 1];
      dataBuff[dataSize] = '\0';

      fin.read(nameBuff, nameSize);
      fin.read(dataBuff, dataSize);

      shaders.emplace(nameBuff, dataBuff);

      delete[] nameBuff;
      delete[] dataBuff;
    }

    fin.close();

    return shaders;
  }

  void spak::packShaders(const string &srcPath, const string &destPath) {
    std::vector<string> files;

    for (auto &&item : fs::recursive_directory_iterator(srcPath)) {
      if (item.is_directory()) continue;
      files.push_back(item.path().u8string());
    }

    //create stamp
    Stamp stamp;
    stamp.x = 0xDE;
    stamp.y = 0xAD;
    stamp.z = 0x22;
    stamp.count = files.size();

    //create package
    std::ofstream outFile(destPath, std::ios::out | std::ios::binary);
    if (!outFile.is_open()) {
      fprintf(stderr, "Bad output file: %s\n", destPath.c_str());
      return;
    }

    //write stamp
    outFile.write((const char *) &stamp, sizeof(Stamp));

    for (auto &&file : files) {
      //get filename
      string fileName = getFileName(file, true);
      std::replace(fileName.begin(), fileName.end(), '.', '_');

      //open and get size
      std::ifstream fin(file, std::ios::in | std::ios::binary);
      fin.seekg(0, std::ifstream::end);
      int64_t length = fin.tellg();
      fin.seekg(0, std::ifstream::beg);

      //get data
      char *buff = new char[length + 1];
      buff[length] = '\0';

      fin.read(buff, length);
      fin.close();

      //create entry
      ShaderEntry shaderEntry{ };
      shaderEntry.nameSize = fileName.size();
      shaderEntry.dataSize = static_cast<size_t>(length);

      //write data
      outFile.write((const char *) &shaderEntry, sizeof(ShaderEntry));
      outFile << fileName;
      outFile << buff;

      delete[] buff;
    }

    outFile.close();
  }

}