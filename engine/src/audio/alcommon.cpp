//
// Created by FLXR on 2/12/2019.
//

#include <al/al.h>
#include <cstdio>
#include <xe/utils/logger.hpp>
#include "alcommon.hpp"

namespace xe::internal {

  int32 alCheckError() {
    return alGetError();
  }

  bool alLogCall(const char *function, const char *file, uint line) {
    int32 error = alGetError();
    if (error != AL_NO_ERROR) {
      char buffer[1024 * 10];
      sprintf(buffer, "[OpenAL Error] (%u): %s, %s: %u", error, function, file, line);
      XE_CORE_FATAL(buffer);
      return false;
    }
    return true;
  }

}