//
// Created by FLXR on 7/15/2018.
//

#include "platformwindow.hpp"
#include "utils/sleep.hpp"
#include "common.hpp"

#ifdef XE_PLATFORM_WINDOWS
#include "platform/win32/window/win32window.hpp"
typedef xe::internal::PlatformWindowWin32 PlatformWindowType;
#endif

namespace xe { namespace internal {

	PlatformWindow *PlatformWindow::create(VideoMode mode, const std::string_view &title, uint style) {
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