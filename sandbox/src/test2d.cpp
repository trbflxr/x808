//
// Created by FLXR on 6/29/2018.
//

#include <application/application.hpp>
#include <gfx/api/texture2d.hpp>
#include "test2d.hpp"

using namespace xe;
using namespace gfx;
using namespace gfx::api;

Test2D::Test2D() : Layer2D(new Scene2D(math::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))) { }

Test2D::~Test2D() {
	delete entity;
}

void Test2D::init(xe::gfx::Renderer2D &renderer) {
	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	TextureParameters params(TextureFilter::NEAREST);

//	add(new Sprite(0, 0, 5, 5, new Texture2D("test1", "assets/textures/test1.png", params)));
//	add(new Sprite(-5.0f, -5.0f, 3, 3, color::PINK));


	Sprite *sprite = new Sprite(2, 2, 1, 1, new Texture2D("test1", "assets/textures/test3.png", params));
	entity = new Entity(sprite, math::translate(vec3(sprite->getPosition())));
//	entity->addComponent(new SpriteComponent(
//			new Sprite(0, 0, 2, 2, new Texture2D("test1", "assets/textures/test6.png", params))));

	scene->add(entity);
}

void Test2D::tick() {
	xe::Application &app = xe::Application::getApplication();

	char buff[1024];
	sprintf(buff, "fps: %u | ups: %u | frame time: %f ms", app.getFPS(), app.getUPS(), app.getFrameTime());
	app.getWindow().setTitle(buff);


//	mat4 m = math::translate({sinf(rand() % 2), 1, 0});
//	entity->getComponent<TransformComponent>()->transform = m;
}

void Test2D::render(xe::gfx::Renderer2D &renderer) {
	renderer.drawLine(0, 0, 100, 100, xe::color::CYAN, 0.1f);
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