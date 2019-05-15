//
// Created by FLXR on 7/15/2018.
//

#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif
#ifndef WIN32_EXTRA_LEAN
  #define WIN32_EXTRA_LEAN
#endif
#include <windows.h>
#include <sapi.h>
#include <xe/utils/sleep.hpp>

namespace xe {

  void sleep(uint time) {
    TIMECAPS tc;
    timeGetDevCaps(&tc, sizeof(TIMECAPS));

    timeBeginPeriod(tc.wPeriodMin);

    ::Sleep(time);

    timeEndPeriod(tc.wPeriodMin);
  }

}