//
// Created by FLXR on 2/12/2019.
//

#ifndef X808_ALCOMMON_HPP
#define X808_ALCOMMON_HPP


#include <xe/xeint.hpp>

namespace xe::internal {

  int32 alCheckError();

  bool alLogCall(const char *function, const char *file, uint line);

}

#ifdef XE_DEBUG
  #define alCall(x) ::xe::internal::alCheckError();\
        x; \
        if (!::xe::internal::alLogCall(#x, __FILE__, __LINE__)) __debugbreak();
#else
  #define alCall(x) x
#endif //XE_DEBUG


#endif //X808_ALCOMMON_HPP
