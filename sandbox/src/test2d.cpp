//
// Created by FLXR on 6/29/2018.
//

#include <ctime>
#include <application/application.hpp>
#include <gfx/api/texture2d.hpp>
#include <gfx/sprite.hpp>
#include <resources/fontmanager.hpp>
#include <resources/texturemanager.hpp>
#include <resources/soundmanager.hpp>
#include <gfx/renderer.hpp>
#include "test2d.hpp"

using namespace xe;
using namespace gfx;
using namespace gfx::api;

Test2D::Test2D() :
		Layer2D(math::ortho(-80.0f, 80.0f, -60.0f, 60.0f, -1, 1000)) {

	srand((uint) time(nullptr));

	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	TextureParameters params(TextureFilter::NEAREST);

	TextureManager::add(Texture2D::create("0", "assets/textures/test1.png", params));
	TextureManager::add(Texture2D::create("1", "assets/textures/test2.png", params));
	TextureManager::add(Texture2D::create("2", "assets/textures/test3.png", params));
	TextureManager::add(Texture2D::create("3", "assets/textures/test4.png", params));
	TextureManager::add(Texture2D::create("4", "assets/textures/test5.png", params));
	TextureManager::add(Texture2D::create("5", "assets/textures/test6.png", params));
	TextureManager::add(Texture2D::create("6", "assets/textures/test7.png", params));
	TextureManager::add(Texture2D::create("7", "assets/textures/test8.png", params));

	TextureManager::add(Texture2D::create("8", "assets/textures/test1.png", params));
	TextureManager::add(Texture2D::create("9", "assets/textures/test2.png", params));
	TextureManager::add(Texture2D::create("10", "assets/textures/test3.png", params));
	TextureManager::add(Texture2D::create("11", "assets/textures/test4.png", params));
	TextureManager::add(Texture2D::create("12", "assets/textures/test5.png", params));
	TextureManager::add(Texture2D::create("13", "assets/textures/test6.png", params));
	TextureManager::add(Texture2D::create("14", "assets/textures/test7.png", params));
	TextureManager::add(Texture2D::create("15", "assets/textures/test8.png", params));

	TextureManager::add(Texture2D::create("16", "assets/textures/test1.png", params));
	TextureManager::add(Texture2D::create("17", "assets/textures/test2.png", params));
	TextureManager::add(Texture2D::create("18", "assets/textures/test3.png", params));
	TextureManager::add(Texture2D::create("19", "assets/textures/test4.png", params));
	TextureManager::add(Texture2D::create("20", "assets/textures/test5.png", params));
	TextureManager::add(Texture2D::create("21", "assets/textures/test6.png", params));
	TextureManager::add(Texture2D::create("22", "assets/textures/test7.png", params));
	TextureManager::add(Texture2D::create("23", "assets/textures/test8.png", params));

	TextureManager::add(Texture2D::create("24", "assets/textures/test1.png", params));
	TextureManager::add(Texture2D::create("25", "assets/textures/test2.png", params));
	TextureManager::add(Texture2D::create("26", "assets/textures/test3.png", params));
	TextureManager::add(Texture2D::create("27", "assets/textures/test4.png", params));
	TextureManager::add(Texture2D::create("28", "assets/textures/test5.png", params));
	TextureManager::add(Texture2D::create("29", "assets/textures/test6.png", params));
	TextureManager::add(Texture2D::create("30", "assets/textures/test7.png", params));
	TextureManager::add(Texture2D::create("31", "assets/textures/test8.png", params));

	TextureManager::add(Texture2D::create("32", "assets/textures/enemyspotted.png", params));
	TextureManager::add(Texture2D::create("33", "assets/textures/enemyspotted.png", params));
	TextureManager::add(Texture2D::create("34", "assets/textures/enemyspotted.png", params));
	TextureManager::add(Texture2D::create("35", "assets/textures/test4.png", params));
	TextureManager::add(Texture2D::create("36", "assets/textures/test5.png", params));
	TextureManager::add(Texture2D::create("37", "assets/textures/test6.png", params));
	TextureManager::add(Texture2D::create("38", "assets/textures/test7.png", params));
	TextureManager::add(Texture2D::create("39", "assets/textures/test8.png", params));

	/// 1 - 1.2k
	/// 2 - 11k
	/// 3 - 59k
//	uint texCount = 40;
	uint texCount = 31;

#define sp_size  3

	//59k
#if sp_size == 3
	for (float x = -80; x < 80; x += 0.57f) {
		for (float y = -60; y < 60; y += 0.57f) {
			add(new Sprite({x, y}, 0, {0.49f, 0.49f}, 0, &GETTEXTURE(std::to_string(rand() % texCount))));
		}
	}
#elif sp_size == 2
	for (float x = -80; x < 80; x += 1.3f) {
		for (float y = -60; y < 60; y += 1.3f) {
			add(new Sprite({x, y}, 0, {0.9f, 0.9f}, 0, &GETTEXTURE(std::to_string(rand() % texCount))));
		}
	}
#elif sp_size == 1
	for (int32 x = -80; x < 80; x += 4) {
		for (int32 y = -60; y < 60; y += 4) {
			add(new Sprite({(float) x, (float) y}, 0, {3, 3}, 0,
						   &GETTEXTURE(std::to_string(rand() % texCount))));
		}
	}
#endif

	XE_INFO("size: ", renderables.size());


	FontManager::add(new Font("sourceSans", "assets/fonts/sourcesanspro-regular.ttf", 100));
	FontManager::add(new Font("consolata", "assets/fonts/consolata.otf", 100));

	text = new Text("slava ukraine", 20, {-70, 30}, GETFONT("sourceSans"));
	text->setColor(color::WHITE);
	text->setOutlineColor(color::BLACK);
	text->setOutlineThickness(3);

	text2 = new Text("another one", 20, {-70, -10}, GETFONT("consolata"));
	text2->setColor(color::BLUE);
	text2->setOutlineColor(color::BLACK);
	text2->setOutlineThickness(3);

	text3 = new Text("and another one", 20, {-70, -40}, GETFONT("default"));
	text3->setColor(color::YELLOW);
	text3->setOutlineColor(color::BLACK);
	text3->setOutlineThickness(3);

	TextureManager::add(Texture2D::create("2k", "assets/textures/enemyspotted.jpg", params));


	add(new Sprite({0, 0}, 1, {20, 20}, 0, &GETTEXTURE("dick")));
	add(new Sprite({-20, -20}, 1, {20, 20}, 0, &GETTEXTURE("0")));
	add(new Sprite({20, 20}, 1, {20, 20}, 0, &GETTEXTURE("default")));
	add(new Sprite({-64, -36}, 1, {128, 72}, 0, &GETTEXTURE("2k")));

	SoundManager::add(new Sound("test", "assets/sounds/test.wav"));
	SoundManager::add(new Sound("orunec", "assets/sounds/orunec.wav"));
}

Test2D::~Test2D() {
	delete text;
	delete text2;
	delete text3;
}


void Test2D::render() {
//	Layer2D::render();

	renderer->begin();

	for (auto &&r : renderables) {
//		r->rotate(1);
		renderer->submit(r);
	}

	renderer->submitText(text);
	renderer->submitText(text2);
	renderer->submitText(text3);

//	renderer->drawLine(-20, -20, 200, 200, 1, color::GREEN, 2);

	renderer->flush();
}

void Test2D::update(const xe::TimeStep &ts) {
	camera->update();
	renderer->setCamera(camera);

	///input
	if(Input::isKeyPressed(XE_KEY_M)){
		Input::setMousePosition({0,0});
	}

	vec3 pos = camera->getPosition();

	if (Input::isKeyPressed(XE_KEY_A)) {
		pos.x += 1;
	} else if (Input::isKeyPressed(XE_KEY_D)) {
		pos.x -= 1;
	}
	if (Input::isKeyPressed(XE_KEY_W)) {
		pos.y -= 1;
	} else if (Input::isKeyPressed(XE_KEY_S)) {
		pos.y += 1;
	}

	camera->setPosition(pos);
}

void Test2D::tick() {
	xe::Application &app = xe::Application::getApplication();

	char buff[1024];
	sprintf(buff, "fps: %u | ups: %u | frame time: %f ms | DC: %u",
	        app.getFPS(), app.getUPS(), app.getFrameTime(), Renderer::getDC());

	app.getWindow().setTitle(buff);
}

void Test2D::onEvent(xe::Event &event) {
	xe::EventDispatcher dispatcher(event);
	dispatcher.dispatch<xe::KeyPressEvent>(METHOD(&Test2D::onKeyPressedEvent));
	dispatcher.dispatch<xe::MousePressEvent>(METHOD(&Test2D::onMousePressedEvent));
	dispatcher.dispatch<xe::MouseMoveEvent>(METHOD(&Test2D::onMouseMovedEvent));
}

bool Test2D::onKeyPressedEvent(xe::KeyPressEvent &event) {
	if(event.getRepeat()) return false;

	if (event.getKey() == XE_KEY_1) {
		GETSOUND("orunec")->play();
		GETSOUND("orunec")->setGain(0.2f);
	}
	if (event.getKey() == XE_KEY_2) {
		GETSOUND("test")->play();
		GETSOUND("test")->setGain(0.2f);
	}

	return false;
}

bool Test2D::onMousePressedEvent(xe::MousePressEvent &event) {
	return false;
}

bool Test2D::onMouseMovedEvent(xe::MouseMoveEvent &event) {
	return false;
}
