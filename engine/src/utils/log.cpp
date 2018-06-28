//
// Created by FLXR on 6/28/2018.
//

#include <windows.h>
#include "log.hpp"

void xe::internal::platformLogMessage(uint level, const char *message) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (level) {
		case XE_LOG_LEVEL_FATAL: SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED |
		                                                           FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		case XE_LOG_LEVEL_ERROR: SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		case XE_LOG_LEVEL_WARN: SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		default:break;
	}

	printf("%s", message);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}