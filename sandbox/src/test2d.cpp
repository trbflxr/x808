//
// Created by FLXR on 6/29/2018.
//

#include <ctime>
#include <application/application.hpp>
#include <gfx/api/texture2d.hpp>
#include <gfx/sprite.hpp>
#include "test2d.hpp"

using namespace xe;
using namespace gfx;
using namespace gfx::api;

Test2D::Test2D() :
		Layer2D(math::ortho(-80.0f, 80.0f, -60.0f, 60.0f, -1.0f, 1.0f), new api::BasicShader()) {

	srand((uint) time(nullptr));

	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	TextureParameters params(TextureFilter::NEAREST);

	textures.push_back(new Texture2D("test1", "assets/textures/test1.png", params));
	textures.push_back(new Texture2D("test2", "assets/textures/test2.png", params));
	textures.push_back(new Texture2D("test3", "assets/textures/test3.png", params));
	textures.push_back(new Texture2D("test4", "assets/textures/test4.png", params));
	textures.push_back(new Texture2D("test5", "assets/textures/test5.png", params));
	textures.push_back(new Texture2D("test6", "assets/textures/test6.png", params));
	textures.push_back(new Texture2D("test7", "assets/textures/test7.png", params));
	textures.push_back(new Texture2D("test8", "assets/textures/test8.png", params));

	textures.push_back(new Texture2D("test1", "assets/textures/test1.png", params));
	textures.push_back(new Texture2D("test2", "assets/textures/test2.png", params));
	textures.push_back(new Texture2D("test3", "assets/textures/test3.png", params));
	textures.push_back(new Texture2D("test4", "assets/textures/test4.png", params));
	textures.push_back(new Texture2D("test5", "assets/textures/test5.png", params));
	textures.push_back(new Texture2D("test6", "assets/textures/test6.png", params));
	textures.push_back(new Texture2D("test7", "assets/textures/test7.png", params));
	textures.push_back(new Texture2D("test8", "assets/textures/test8.png", params));

	textures.push_back(new Texture2D("test1", "assets/textures/test1.png", params));
	textures.push_back(new Texture2D("test2", "assets/textures/test2.png", params));
	textures.push_back(new Texture2D("test3", "assets/textures/test3.png", params));
	textures.push_back(new Texture2D("test4", "assets/textures/test4.png", params));
	textures.push_back(new Texture2D("test5", "assets/textures/test5.png", params));
	textures.push_back(new Texture2D("test6", "assets/textures/test6.png", params));
	textures.push_back(new Texture2D("test7", "assets/textures/test7.png", params));
	textures.push_back(new Texture2D("test8", "assets/textures/test8.png", params));

	textures.push_back(new Texture2D("test1", "assets/textures/test1.png", params));
	textures.push_back(new Texture2D("test2", "assets/textures/test2.png", params));
	textures.push_back(new Texture2D("test3", "assets/textures/test3.png", params));
	textures.push_back(new Texture2D("test4", "assets/textures/test4.png", params));
	textures.push_back(new Texture2D("test5", "assets/textures/test5.png", params));
	textures.push_back(new Texture2D("test6", "assets/textures/test6.png", params));
	textures.push_back(new Texture2D("test7", "assets/textures/test7.png", params));
	textures.push_back(new Texture2D("test8", "assets/textures/test8.png", params));

	textures.push_back(new Texture2D("test1", "assets/textures/test1.png", params));
	textures.push_back(new Texture2D("test2", "assets/textures/test2.png", params));
	textures.push_back(new Texture2D("test3", "assets/textures/test3.png", params));
	textures.push_back(new Texture2D("test4", "assets/textures/test4.png", params));
	textures.push_back(new Texture2D("test5", "assets/textures/test5.png", params));
	textures.push_back(new Texture2D("test6", "assets/textures/test6.png", params));
	textures.push_back(new Texture2D("test7", "assets/textures/test7.png", params));
	textures.push_back(new Texture2D("test8", "assets/textures/test8.png", params));

	/// 1 - 1.2k
	/// 2 - 11k
	/// 3 - 59k
	uint texCount = 31;x

#define sp_size  1

	//59k
#if sp_size == 3
	for (float x = -80; x < 80; x += 0.57f) {
		for (float y = -60; y < 60; y += 0.57f) {
			add(new Sprite({x, y}, {0.49f, 0.49f}, 0, textures[rand() % texCount]));
		}
	}
#elif sp_size == 2
	for (float x = -80; x < 80; x += 1.3f) {
		for (float y = -60; y < 60; y += 1.3f) {
			add(new Sprite({x, y}, {0.9f, 0.9f}, 0, textures[rand() % texCount]));
		}
	}
#elif sp_size == 1
	for (int32 x = -80; x < 80; x += 4) {
		for (int32 y = -60; y < 60; y += 4) {
			add(new Sprite({(float) x, (float) y}, {3, 3}, 0, textures[rand() % texCount]));
		}
	}
#endif

	XE_INFO("size: ", renderables.size());

}

Test2D::~Test2D() {
	delete shader;

	for (auto &&texture : textures) {
		delete texture;
	}
	textures.clear();
}


void Test2D::render() {
//	Layer2D::render();

	renderer->begin();

	for (auto &&r : renderables) {
//		r->rotate(1);
		renderer->submit(r);
	}

	renderer->end();
	renderer->flush();
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
