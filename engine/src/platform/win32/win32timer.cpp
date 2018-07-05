//
// Created by FLXR on 7/5/2018.
//

#include <new>
#include <windows.h>

#include "utils/timer.hpp"

namespace xe {

	struct TimerMembers {
		LARGE_INTEGER start;
		double frequency;
	};

}

xe::Timer::Timer() :
		members(new(reserved) TimerMembers()) {

	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	members->frequency = 1.0f / frequency.QuadPart;

	reset();
}

void xe::Timer::reset() {
	QueryPerformanceCounter(&members->start);
}

float xe::Timer::elapsed() {
	LARGE_INTEGER current;
	QueryPerformanceCounter(&current);

	LONGLONG cycles = current.QuadPart - members->start.QuadPart;
	return static_cast<float>(cycles * members->frequency);
}

float xe::Timer::elapsedMillis() {
	return elapsed() * 1000.0f;
}
