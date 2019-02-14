//
// Created by FLXR on 7/5/2018.
//

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <new>
#include <xe/utils/timer.hpp>

namespace xe {

	struct TimerMembers {
		LARGE_INTEGER start;
		double frequency;
	};


	Timer::Timer() :
			members(new(reserved) TimerMembers()) {

		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		members->frequency = 1.0f / frequency.QuadPart;

		reset();
	}

	void Timer::reset() {
		QueryPerformanceCounter(&members->start);
	}

	float Timer::elapsed() {
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);

		LONGLONG cycles = current.QuadPart - members->start.QuadPart;
		return static_cast<float>(cycles * members->frequency);
	}

	float Timer::elapsedMillis() {
		return elapsed() * 1000.0f;
	}

}