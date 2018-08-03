//
// Created by FLXR on 7/14/2018.
//

#include <Freeimage/FreeImage.h>

#include "window.hpp"
#include "utils/log.hpp"
#include "utils/sleep.hpp"
#include "platformwindow.hpp"
#include "gfx/renderer.hpp"
#include "gfx/api/context.hpp"
#include "resources/soundmanager.hpp"

namespace {
	const xe::Window *fullscreenWindow = nullptr;
}

namespace xe {

	Window::Window() :
          window(nullptr),
			frameTimeLimit(0.0f),
			size(0, 0) { }

	Window::Window(VideoMode mode, const std::string_view &title, uint style) :
			window(nullptr),
			frameTimeLimit(0.0f),
			size(0, 0) {

		create(mode, title, style);
	}

	Window::~Window() {
		close();
	}

	void Window::create(VideoMode mode, const std::string_view &title, uint style) {
		close();

		if (style & WindowStyle::Fullscreen) {
			if (fullscreenWindow) {
				XE_ERROR("[Window]: Creating two fullscreen windows is not allowed, switching to windowed mode");
				style &= ~WindowStyle::Fullscreen;
			} else {
				if (!mode.isValid()) {
					XE_ERROR("[Window]: The requested video mode is not available, switching to a valid mode");
					mode = VideoMode::getFullscreenModes()[0];
				}
				fullscreenWindow = this;
			}
		}

		window = internal::PlatformWindow::create(mode, title, style);

		init();
	}

	void Window::close() {
		delete window;
		window = nullptr;

		if (this == fullscreenWindow) {
			fullscreenWindow = nullptr;
		}
	}

	vec2i Window::getPosition() const {
		return window ? window->getPosition() : vec2i();
	}

	void Window::setPosition(const vec2i &position) {
		if (window) {
			window->setPosition(position);
		}
	}

	void Window::setSize(const vec2u &size) {
		if (window) {
			window->setSize(size);

			Window::size.x = size.x;
			Window::size.y = size.y;

			onResize();
		}
	}

	void Window::setTitle(const std::string_view &title) {
		if (window) {
			window->setTitle(title);
		}
	}

	void Window::setIcon(uint width, uint height, const byte *pixels) {
		if (window) {
			window->setIcon(width, height, pixels);
		}
	}

	void Window::setVisible(bool visible) {
		if (window) {
			window->setVisible(visible);
		}
	}

	void Window::setMouseCursorVisible(bool visible) {
		if (window) {
			window->setMouseCursorVisible(visible);
		}
	}

	void Window::setMouseCursorGrabbed(bool grabbed) {
		if (window) {
			window->setMouseCursorGrabbed(grabbed);
		}
	}

	bool Window::isMouseCursorGrabbed() {
		if (window) {
			return window->isMouseCursorGrabbed();
		}
	}

	void Window::setMouseCursor(const Cursor &cursor) {
		if (window) {
			window->setMouseCursor(cursor);
		}
	}

	void Window::setKeyRepeatEnabled(bool enabled) {
		if (window) {
			window->setKeyRepeatEnabled(enabled);
		}
	}

	void Window::requestFocus() {
		if (window) {
			window->requestFocus();
		}
	}

	bool Window::hasFocus() const {
		return window && window->hasFocus();
	}


	void *Window::getHandle() const {
		return window ? window->getHandle() : nullptr;
	}


	bool Window::isOpen() const {
		return window != nullptr;
	}

	bool Window::pollEvent(Event &event) {
		if (window && window->popEvent(event, false)) {
			return filterEvent(event);
		} else {
			return false;
		}
	}

	void Window::setVerticalSyncEnabled(bool enabled) {
		Renderer::enableVsync(enabled);
	}

	void Window::setFramerateLimit(uint limit) {
		if (limit > 0) {
			frameTimeLimit = 1000.0f / limit;
		} else {
			frameTimeLimit = 0;
		}
	}

	void Window::clear() const {
		Renderer::clear(RENDERER_BUFFER_COLOR | RENDERER_BUFFER_DEPTH);
	}

	void Window::update() {
		Renderer::flush();

		//limit fps
		if (frameTimeLimit != 0) {
			sleep(static_cast<uint>(frameTimeLimit - timer.elapsed()));
			timer.reset();
		}

		SoundManager::update();
	}

	void Window::init() {
		FreeImage_Initialise();

		api::Context::create(getHandle());
		Renderer::init();

		SoundManager::init();

		setVisible(true);
		setMouseCursorVisible(true);
		setVerticalSyncEnabled(false);
		setKeyRepeatEnabled(true);
		setFramerateLimit(0);

		size = window->getSize();

		timer.reset();

		onCreate();
	}

	bool Window::filterEvent(const Event &event) {
		if (event.type == Event::Resized) {
			size.x = event.size.width;
			size.y = event.size.height;

			onResize();
		}

		return true;
	}

}