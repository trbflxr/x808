//
// Created by FLXR on 7/14/2018.
//


#include <xe/window/window.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/gfx/context.hpp>
#include <xe/utils/sleep.hpp>
#include <xe/utils/logger.hpp>
#include <window/platformwindow.hpp>

namespace {
	const xe::Window *fullscreenWindow = nullptr;
}

namespace xe {

	Window::Window() :
			window(nullptr),
			size(0, 0),
			frameTimeLimit(0.0f) { }

	Window::Window(VideoMode mode, const string &title, uint style) :
			window(nullptr),
			size(0, 0),
			frameTimeLimit(0.0f) {

		create(mode, title, style);
	}

	Window::~Window() {
		close();
	}

	void Window::create(VideoMode mode, const string &title, uint style) {
		close();

		if (style & WindowStyle::Fullscreen) {
			if (fullscreenWindow) {
				XE_CORE_ERROR("[Window]: Creating two fullscreen windows is not allowed, switching to windowed mode");
				style &= ~WindowStyle::Fullscreen;
			} else {
				if (!mode.isValid()) {
					XE_CORE_ERROR("[Window]: The requested video mode is not available, switching to a valid mode");
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

	vec2 Window::getPosition() const {
		return window ? window->getPosition() : vec2();
	}

	void Window::setPosition(const vec2 &position) const {
		if (window) {
			window->setPosition(position);
		}
	}

	void Window::setSize(const vec2 &size) {
		if (window) {
			window->setSize(size);

			Window::size.x = size.x;
			Window::size.y = size.y;

			onResize();
		}
	}

	void Window::setTitle(const string &title) const {
		if (window) {
			window->setTitle(title);
		}
	}

	string Window::getTitle() const {
		if (window) {
			return window->getTitle();
		}
		return "NULL";
	}

	void Window::setIcon(uint width, uint height, const byte *pixels) const {
		if (window) {
			window->setIcon(width, height, pixels);
		}
	}

	void Window::setVisible(bool visible) const {
		if (window) {
			window->setVisible(visible);
		}
	}

	void Window::setMouseCursorVisible(bool visible) const {
		if (window) {
			window->setMouseCursorVisible(visible);
		}
	}

	void Window::setMouseCursorGrabbed(bool grabbed) const {
		if (window) {
			window->setMouseCursorGrabbed(grabbed);
		}
	}

	bool Window::isMouseCursorGrabbed() const {
		if (window) {
			return window->isMouseCursorGrabbed();
		}
		return false;
	}

	void Window::setMouseCursor(const Cursor &cursor) const {
		if (window) {
			window->setMouseCursor(cursor);
		}
	}

	void Window::setKeyRepeatEnabled(bool enabled) const {
		if (window) {
			window->setKeyRepeatEnabled(enabled);
		}
	}

	void Window::requestFocus() const {
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

	void Window::setVerticalSyncEnabled(bool enabled) const {
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
		Renderer::clear(RendererBufferColor | RendererBufferDepth);
	}

	void Window::update() {
		Renderer::flush();

		//limit fps
		if (frameTimeLimit != 0) {
			sleep(static_cast<uint>(frameTimeLimit - timer.elapsed()));
			timer.reset();
		}
	}

	void Window::init() {
		Context::create(getHandle());
		Renderer::init();

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