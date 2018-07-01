//
// Created by FLXR on 6/29/2018.
//

#include <application/application.hpp>
#include <gfx/api/texture2d.hpp>
#include <components/spritecomponent.hpp>
#include "test2d.hpp"

using namespace xe;
using namespace gfx;
using namespace gfx::api;

Test2D::Test2D() {
	renderer = new Renderer2D(800, 600);
	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	TextureParameters params(TextureFilter::NEAREST);

	root = new GameObject();

	root->addObject(new SpriteComponent(renderer, {5, 5}, color::RED));

	SpriteComponent *s = new SpriteComponent(renderer, {3, 3},
	                                         new Texture2D("test1", "assets/textures/test3.png", params));
	s->getTransform().rotate(25, ZAXIS);
	s->getTransform().setPosition({-8, 3, 0});


	SpriteComponent *s2 = new SpriteComponent(renderer, {3, 3}, color::PINK);
//	s2->getTransform().setPosition({2, 1, 0});

	s->addObject(s2);



	root->addObject(s);


}

Test2D::~Test2D() {
	delete renderer;
	delete root;
}

void Test2D::init() {
	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	TextureParameters params(TextureFilter::NEAREST);
}

void Test2D::update(const xe::TimeStep &ts) {

}

void Test2D::render() {
	renderer->begin();

//	renderer->fillRect(1, 1, 3, 3, color::GREEN);
//	renderer->fillRect(0, 0, 3, 3, color::rgba(1,0,1,0.3f));

	root->render(shader);

	renderer->end();
	renderer->flush();
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
