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
#include <xe/app/application.hpp>
#include <xe/systems/shell.hpp>

namespace xe {

  void Logger::platformLogMessage(uint level, const char *message) {
    Application *app = Application::get();
    ShellItemType type = ShellItemType::Info;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (level) {
      case XE_LOG_LEVEL_FATAL: {
        SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED |
                                          FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        type = ShellItemType::Fatal;
        break;
      }

      case XE_LOG_LEVEL_ERROR: {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        type = ShellItemType::Error;
        break;
      }

      case XE_LOG_LEVEL_WARN: {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        type = ShellItemType::Warn;
        break;
      }

      case XE_LOG_LEVEL_INFO: {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        type = ShellItemType::Info;
        break;
      }

      default:break;
    }

    if (app) app->getShell().printString(message, type, false);

    printf("%s", message);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
  }

}