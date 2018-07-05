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
#include "test2d.hpp"

using namespace xe;
using namespace gfx;
using namespace gfx::api;

Test2D::Test2D() :
		Layer2D(math::ortho(-80.0f, 80.0f, -60.0f, 60.0f, -1, 1000)) {

	srand((uint) time(nullptr));

	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	TextureParameters params(TextureFilter::NEAREST);

	TextureManager::add(new Texture2D("0", "assets/textures/test1.png", params));
	TextureManager::add(new Texture2D("1", "assets/textures/test2.png", params));
	TextureManager::add(new Texture2D("2", "assets/textures/test3.png", params));
	TextureManager::add(new Texture2D("3", "assets/textures/test4.png", params));
	TextureManager::add(new Texture2D("4", "assets/textures/test5.png", params));
	TextureManager::add(new Texture2D("5", "assets/textures/test6.png", params));
	TextureManager::add(new Texture2D("6", "assets/textures/test7.png", params));
	TextureManager::add(new Texture2D("7", "assets/textures/test8.png", params));

	TextureManager::add(new Texture2D("8", "assets/textures/test1.png", params));
	TextureManager::add(new Texture2D("9", "assets/textures/test2.png", params));
	TextureManager::add(new Texture2D("10", "assets/textures/test3.png", params));
	TextureManager::add(new Texture2D("11", "assets/textures/test4.png", params));
	TextureManager::add(new Texture2D("12", "assets/textures/test5.png", params));
	TextureManager::add(new Texture2D("13", "assets/textures/test6.png", params));
	TextureManager::add(new Texture2D("14", "assets/textures/test7.png", params));
	TextureManager::add(new Texture2D("15", "assets/textures/test8.png", params));

	TextureManager::add(new Texture2D("16", "assets/textures/test1.png", params));
	TextureManager::add(new Texture2D("17", "assets/textures/test2.png", params));
	TextureManager::add(new Texture2D("18", "assets/textures/test3.png", params));
	TextureManager::add(new Texture2D("19", "assets/textures/test4.png", params));
	TextureManager::add(new Texture2D("20", "assets/textures/test5.png", params));
	TextureManager::add(new Texture2D("21", "assets/textures/test6.png", params));
	TextureManager::add(new Texture2D("22", "assets/textures/test7.png", params));
	TextureManager::add(new Texture2D("23", "assets/textures/test8.png", params));

	TextureManager::add(new Texture2D("24", "assets/textures/test1.png", params));
	TextureManager::add(new Texture2D("25", "assets/textures/test2.png", params));
	TextureManager::add(new Texture2D("26", "assets/textures/test3.png", params));
	TextureManager::add(new Texture2D("27", "assets/textures/test4.png", params));
	TextureManager::add(new Texture2D("28", "assets/textures/test5.png", params));
	TextureManager::add(new Texture2D("29", "assets/textures/test6.png", params));
	TextureManager::add(new Texture2D("30", "assets/textures/test7.png", params));
	TextureManager::add(new Texture2D("31", "assets/textures/test8.png", params));

	TextureManager::add(new Texture2D("32", "assets/textures/enemyspotted.png", params));
	TextureManager::add(new Texture2D("33", "assets/textures/enemyspotted.png", params));
	TextureManager::add(new Texture2D("34", "assets/textures/enemyspotted.png", params));
	TextureManager::add(new Texture2D("35", "assets/textures/test4.png", params));
	TextureManager::add(new Texture2D("36", "assets/textures/test5.png", params));
	TextureManager::add(new Texture2D("37", "assets/textures/test6.png", params));
	TextureManager::add(new Texture2D("38", "assets/textures/test7.png", params));
	TextureManager::add(new Texture2D("39", "assets/textures/test8.png", params));

	/// 1 - 1.2k
	/// 2 - 11k
	/// 3 - 59k
	uint texCount = 40;
//	uint texCount = 31;

#define sp_size  2

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

	TextureManager::add(new Texture2D("2k", "assets/textures/enemyspotted.jpg", params));


	add(new Sprite({0, 0}, 1, {20, 20}, 0, &GETTEXTURE("dick")));
	add(new Sprite({-20, -20}, 1, {20, 20}, 0, &GETTEXTURE("0")));
	add(new Sprite({20, 20}, 1, {20, 20}, 0, &GETTEXTURE("default")));
	add(new Sprite({-64, -36}, 1, {128, 72}, 0, &GETTEXTURE("2k")));

	SoundManager::add(new Sound("test", "assets/sounds/test.wav"));
	SoundManager::add(new Sound("orunec", "assets/sounds/orunec.wav"));

//	GETSOUND("orunec")->loop();
//	GETSOUND("orunec")->setGain(0.2f);
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
}

void Test2D::tick() {
	xe::Application &app = xe::Application::getApplication();

	char buff[1024];
	sprintf(buff, "fps: %u | ups: %u | frame time: %f ms | DC: %u",
	        app.getFPS(), app.getUPS(), app.getFrameTime(), Renderer2D::getDC());

	app.getWindow().setTitle(buff);
}

void Test2D::onEvent(xe::Event &event) {
	xe::EventDispatcher dispatcher(event);
	dispatcher.dispatch<xe::KeyPressEvent>(METHOD(&Test2D::onKeyPressedEvent));
	dispatcher.dispatch<xe::MousePressEvent>(METHOD(&Test2D::onMousePressedEvent));
	dispatcher.dispatch<xe::MouseMoveEvent>(METHOD(&Test2D::onMouseMovedEvent));
}

bool Test2D::onKeyPressedEvent(xe::KeyPressEvent &event) {
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



	if (Input::isKeyPressed(XE_KEY_1)) {
		GETSOUND("orunec")->play();
		GETSOUND("orunec")->setGain(2);
	}
	if (Input::isKeyPressed(XE_KEY_2)) {
		GETSOUND("test")->play();
		GETSOUND("test")->setGain(0.2f);
	}

}

bool Test2D::onMousePressedEvent(xe::MousePressEvent &event) {
	return false;
}

bool Test2D::onMouseMovedEvent(xe::MouseMoveEvent &event) {
	return false;
}
