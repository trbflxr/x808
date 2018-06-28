#include <math/math.hpp>
#include <utils/log.hpp>
#include <cstdio>
#include <application/window.hpp>

int main() {
	xe::WindowProperties props;
	props.width = 800;
	props.height = 600;
	props.title = "test window";
	props.vSync = true;
	props.fullScreen = false;

	xe::Window window(props);

	window.setTitle("aye2k");

	while(!window.shouldClose()){
		window.update();
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