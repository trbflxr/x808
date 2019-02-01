//
// Created by FLXR on 7/15/2018.
//

#include <xe/common.hpp>
#include <xe/utils/sleep.hpp>

#ifdef XE_PLATFORM_WINDOWS
#include "window/platform/win32/win32window.hpp"
typedef xe::internal::PlatformWindowWin32 PlatformWindowType;
#endif

#include "platformwindow.hpp"

namespace xe { namespace internal {

	PlatformWindow *PlatformWindow::create(VideoMode mode, const string &title, uint style) {
		return new PlatformWindowType(mode, title, style);
	}

	bool PlatformWindow::popEvent(Event &event, bool block) {
		if (events.empty()) {
			processEvents();

			if (block) {
				while (events.empty()) {
					sleep(10);
					processEvents();
				}
			}
		}

		if (!events.empty()) {
			event = events.front();
			events.pop();

			return true;
		}

		return false;
	}

	void PlatformWindow::pushEvent(const Event &event) {
		events.push(event);
	}

}}