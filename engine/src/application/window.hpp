//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_WINDOW_HPP
#define X808_WINDOW_HPP


#include <map>
#include <functional>
#include "events/event.hpp"
#include "input.hpp"

namespace xe {

	typedef std::function<void(Event &event)> WindowEventCallback;

	struct XE_API WindowProperties {
		uint width;
		uint height;
		std::string title;
		bool fullScreen;
		bool vSync;
	};

	class XE_API Window {
	public:
		explicit Window(const WindowProperties &props);
		~Window();

		void clear() const;
		void update();

		inline bool shouldClose() const { return closed; };

		void setTitle(const std::string_view &title);

		inline uint getWidth() const { return props.width; }
		inline uint getHeight() const { return props.height; }

		inline InputManager *getInputManager() { return inputManager; }

		void setEventCallback(const WindowEventCallback &callback);

		static void registerWindowClass(void *handle, Window *window);
		static Window *getWindowClass(void *handle);

	private:
		bool init();
		bool platformInit();

		void platformUpdate();

		friend void resizeCallback(Window *window, uint width, uint height);
		friend void focusCallback(Window *window, bool focused);

	private:
		static std::map<void *, Window *> handles;
		bool closed;
		WindowProperties props;

		InputManager *inputManager;
		WindowEventCallback eventCallback;
	};

	void resizeCallback(Window *window, uint width, uint height);
	void focusCallback(Window *window, bool focused);
}


#endif //X808_WINDOW_HPP
