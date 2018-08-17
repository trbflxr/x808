//
// Created by FLXR on 7/15/2018.
//


#include <windows.h>
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