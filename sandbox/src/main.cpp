#include <math/math.hpp>
#include <utils/log.hpp>
#include <cstdio>
#include <application/window.hpp>
#include <events/events.hpp>

struct Dummy {
	xe::Window window;

	Dummy(xe::WindowProperties props) : window(props) {
		window.setEventCallback(METHOD(&Dummy::eventCallback));
	}

	void eventCallback(xe::Event &event) {
		xe::EventDispatcher dispatcher(event);
		dispatcher.dispatch<xe::KeyPressEvent>(METHOD(&Dummy::onKeyPressedEvent));
		dispatcher.dispatch<xe::MousePressEvent>(METHOD(&Dummy::onMousePressedEvent));
		dispatcher.dispatch<xe::MouseMoveEvent>(METHOD(&Dummy::onMouseMovedEvent));
		dispatcher.dispatch<xe::MouseWheelEvent>(METHOD(&Dummy::onMouseWheelEvent));
	}

	bool onKeyPressedEvent(xe::KeyPressEvent &event) {
		if (event.getRepeat()) return false;

		if (event.getKey() == XE_KEY_A) {
			printf("A pressed\n");
			printf("mods %i\n", event.getModifiers());
			return true;
		}
		return false;
	}

	bool onMousePressedEvent(xe::MousePressEvent &event) {
		if (event.getButton() == XE_MOUSE_MIDDLE) {
			printf("mmb pressed\n");
			return true;
		}
		return false;
	}

	bool onMouseMovedEvent(xe::MouseMoveEvent &event) {
//		xe::vec2 pos = event.getPosition();
//		printf("x: %.2f, y: %.2f\n", pos.x, pos.y);
		return true;
	}

	bool onMouseWheelEvent(xe::MouseWheelEvent &event) {
		printf("%i\n", event.getDelta());
		return true;
	}
};

int main() {
	xe::WindowProperties props;
	props.width = 800;
	props.height = 600;
	props.title = "test window";
	props.vSync = true;
	props.fullScreen = false;

	Dummy dummy(props);

	while (!dummy.window.shouldClose()) {
		dummy.window.update();
	}

	xe::vec2u v1(2, 2);
	xe::vec2u v2(1, 1);
	xe::vec2u v3 = v1 + v2;

	xe::vec2 v = {4.5f, 7.5f};

	printf("x: %u, y: %u\n", v1.x, v1.y);
	printf("x: %u, y: %u\n", v2.x, v2.y);
	printf("x: %u, y: %u\n", v3.x, v3.y);


	uint64 a = 10;
	std::string_view s = "asdad";

	XE_ERROR("test: ", 330.0f, v1);
	XE_ERROR("test: ", 330.0f, v);
	XE_WARN("test: ", 330.0f, a);
	XE_INFO("test: ", 330.0f, false);
	XE_FATAL("test: ", 330.0f, s);


	return 0;
}