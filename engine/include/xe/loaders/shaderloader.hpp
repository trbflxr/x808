//
// Created by FLXR on 9/29/2018.
//

#ifndef X808_SHADERLOADER_HPP
#define X808_SHADERLOADER_HPP


#include <xe/common.hpp>
#include <xe/string.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

  class XE_API ShaderLoader : NonCopyable {
  public:
    static string load(const string &file);
    static string load(const char *file);

  private:
    static constexpr const char *basePath = u8"/shaders/";
  };

}

#endif //X808_SHADERLOADER_HPP
