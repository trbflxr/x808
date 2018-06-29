//
// Created by FLXR on 6/29/2018.
//

#include <application/application.hpp>
#include "test2d.hpp"

Test2D::Test2D() :
		Layer2D(xe::mat4(1.0f)) {

}

Test2D::~Test2D() {

}

void Test2D::render() {

}

void Test2D::tick() {
	xe::Application &app = xe::Application::getApplication();

	char buff[1024];
	sprintf(buff, "fps: %u | ups: %u | frame time: %f ms", app.getFPS(), app.getUPS(), app.getFrameTime());
	app.getWindow().setTitle(buff);
}

void Test2D::onEvent(xe::Event &event) {
	xe::EventDispatcher dispatcher(event);
	dispatcher.dispatch<xe::KeyPressEvent>(METHOD(&Test2D::onKeyPressedEvent));
	dispatcher.dispatch<xe::MousePressEvent>(METHOD(&Test2D::onMousePressedEvent));
	dispatcher.dispatch<xe::MouseMoveEvent>(METHOD(&Test2D::onMouseMovedEvent));
}

bool Test2D::onKeyPressedEvent(xe::KeyPressEvent &event) {
	return false;
}

bool Test2D::onMousePressedEvent(xe::MousePressEvent &event) {
	return false;
}

bool Test2D::onMouseMovedEvent(xe::MouseMoveEvent &event) {
	return false;
}
