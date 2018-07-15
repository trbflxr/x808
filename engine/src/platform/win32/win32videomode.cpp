//
// Created by FLXR on 7/14/2018.
//
#undef NOGDI
#include <windows.h>
#define NOGDI

#include <functional>
#include <algorithm>
#include "window/videomode.hpp"

namespace xe {

	const std::vector<VideoMode> &VideoMode::getFullscreenModes() {
		static std::vector<VideoMode> modes;

		DEVMODE win32Mode;
		win32Mode.dmSize = sizeof(win32Mode);
		win32Mode.dmDriverExtra = 0;

		for (DWORD count = 0; EnumDisplaySettings(nullptr, count, &win32Mode); ++count) {
			VideoMode mode(win32Mode.dmPelsWidth, win32Mode.dmPelsHeight, win32Mode.dmBitsPerPel);

			if (std::find(modes.begin(), modes.end(), mode) == modes.end()) {
				modes.push_back(mode);
			}
		}

		if (!modes.empty()) {
			std::sort(modes.begin(), modes.end(), std::greater<>());
		}

		return modes;
	}

	VideoMode VideoMode::getDesktopMode() {
		DEVMODE win32Mode;
		win32Mode.dmSize = sizeof(DEVMODE);
		win32Mode.dmDriverExtra = 0;

		EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &win32Mode);

		return VideoMode(win32Mode.dmPelsWidth, win32Mode.dmPelsHeight, win32Mode.dmBitsPerPel);
	}

}