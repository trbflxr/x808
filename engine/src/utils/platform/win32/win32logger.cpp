//
// Created by FLXR on 2/5/2019.
//

#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif
#ifndef WIN32_EXTRA_LEAN
  #define WIN32_EXTRA_LEAN
#endif
#include <windows.h>
#include <cstdio>
#include <xe/utils/logger.hpp>

namespace xe {

  void Logger::platformLogMessage(uint level, const char *message) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (level) {
      case XE_LOG_LEVEL_FATAL: {
        SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED |
                                          FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;
      }

      case XE_LOG_LEVEL_ERROR: {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;
      }

      case XE_LOG_LEVEL_WARN: {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;
      }

      case XE_LOG_LEVEL_INFO: {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;
      }

      default:break;
    }

    printf("%s", message);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
  }

}