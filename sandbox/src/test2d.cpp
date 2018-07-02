//
// Created by FLXR on 6/29/2018.
//

#include <application/application.hpp>
#include <gfx/api/texture2d.hpp>
#include <objects/sprite.hpp>
#include "test2d.hpp"

using namespace xe;
using namespace gfx;
using namespace gfx::api;

Test2D::Test2D() :
		Layer2D(math::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f), new api::BasicShader()) {

	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	TextureParameters params(TextureFilter::NEAREST);

	root->addObject(new Sprite(renderer, {5, 5}, color::RED));

	Sprite *s = new Sprite(renderer, {4, 4},
	                                         new Texture2D("test1", "assets/textures/test3.png", params));
	s->getTransform().setPosition({-8, 3, 0});


	Sprite *s2 = new Sprite(renderer, {3, 3},
	                                          new Texture2D("test5", "assets/textures/test5.png", params));
	s2->getTransform().setPosition({-2, 1, 0});

	s->addObject(s2);

	root->addObject(s);
}

Test2D::~Test2D() {
	delete shader;
}


void Test2D::update(const xe::TimeStep &ts) {

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
