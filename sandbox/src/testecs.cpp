//
// Created by FLXR on 7/8/2018.
//

#include <ctime>
#include <application/application.hpp>
#include <gfx/renderer.hpp>
#include <resources/texturemanager.hpp>
#include <resources/fontmanager.hpp>
#include <resources/soundmanager.hpp>
#include "testecs.hpp"

using namespace xe;
using namespace gfx;
using namespace gfx::api;


TestECS::TestECS() {

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


	FontManager::add(new Font("sourceSans", "assets/fonts/sourcesanspro-regular.ttf", 100));
	FontManager::add(new Font("consolata", "assets/fonts/consolata.otf", 100));


	SoundManager::add(new Sound("test", "assets/sounds/test.wav"));
	SoundManager::add(new Sound("orunec", "assets/sounds/orunec.wav"));


	uint texCount = 40;

	//render system
	spriteRenderer = new SpriteRendererSystem(renderer);

	renderingPipeline.addSystem(*spriteRenderer);

	//main systems
	cameraSystem = new OrthoCameraSystem(renderer);

	mainSystems.addSystem(*cameraSystem);


	//create camera
	OrthoCameraComponent camera(math::ortho(-80.0f, 80.0f, -60.0f, 60.0f, -1, 1000));
	ecs.makeEntity(camera);

	//sprite components
	SpriteComponent sprite;
	Transform2DComponent transform;

	uint sprites = 0;

	/// 0 - 1
	/// 1 - 1.2k
	/// 2 - 11k
	/// 3 - 59k
#define sp_size 2

#if sp_size == 3
	for (float x = -80; x < 80; x += 0.57f) {
		for (float y = -60; y < 60; y += 0.57f) {
			sprite.texture = &GETTEXTURE(std::to_string(rand() % texCount));

			transform.zIndex = 0;
			transform.bounds.setPosition(x, y);
			transform.bounds.setSize(0.49f, 0.49f);

			a = ecs.makeEntity(sprite, transform);

			++sprites;
		}
	}
#elif sp_size == 2
	for (float x = -80; x < 80; x += 1.3f) {
		for (float y = -60; y < 60; y += 1.3f) {
			sprite.texture = &GETTEXTURE(std::to_string(rand() % texCount));

			transform.zIndex = 0;
			transform.bounds.setPosition(x, y);
			transform.bounds.setSize(0.9f, 0.9f);

			a = ecs.makeEntity(sprite, transform);

			++sprites;
		}
	}
#elif sp_size == 1
	for (int32 x = -80; x < 80; x += 4) {
		for (int32 y = -60; y < 60; y += 4) {
			sprite.texture = &GETTEXTURE(std::to_string(rand() % texCount));

			transform.zIndex = 0;
			transform.bounds.setPosition(x, y);
			transform.bounds.setSize(3, 3);

			a = ecs.makeEntity(sprite, transform);

			++sprites;
		}
	}
#elif sp_size == 0
	sprite.texture = &GETTEXTURE(std::to_string(rand() % texCount));

	transform.zIndex = 0;
	transform.bounds.setPosition(0, 0);
	transform.bounds.setSize(3, 3);

	a = ecs.makeEntity(sprite, transform);

	++sprites;
#endif

	XE_INFO("size: ", sprites);

	text = new Text("slava ukraine", 20, {-70, 30}, GETFONT("sourceSans"));
	text->setColor(color::WHITE);
	text->setOutlineColor(color::BLACK);
	text->setOutlineThickness(3);


	sprite.texture = &GETTEXTURE("32");

	transform.zIndex = 1;
	transform.bounds.setPosition(-10, -10);
	transform.bounds.setSize(20, 20);

	a = ecs.makeEntity(sprite, transform);
}

TestECS::~TestECS() {
	delete spriteRenderer;
	delete cameraSystem;
}

void TestECS::render() {
	renderer->begin();

	ecs.updateSystems(renderingPipeline, 0.0f);
//	renderer->drawLine(-20, -20, 200, 200, 1, color::GREEN, 2);

	renderer->submitText(text);

	renderer->flush();
}

void TestECS::update(const xe::TimeStep &ts) {
	Transform2DComponent *t = ecs.getComponent<Transform2DComponent>(a);

	vec2 pos = t->bounds.getPosition();
	if (xe::Input::isKeyPressed(XE_KEY_D)) {
		pos.x += 1;
	}
	if (xe::Input::isKeyPressed(XE_KEY_A)) {
		pos.x -= 1;
	}
	if (xe::Input::isKeyPressed(XE_KEY_W)) {
		pos.y += 1;
	}
	if (xe::Input::isKeyPressed(XE_KEY_S)) {
		pos.y -= 1;
	}
	t->bounds.setPosition(pos);


	ecs.updateSystems(mainSystems, ts.getSeconds());
}

void TestECS::tick() {
	xe::Application &app = xe::Application::getApplication();

	char buff[1024];
	sprintf(buff, "fps: %u | ups: %u | frame time: %f ms | DC: %u",
	        app.getFPS(), app.getUPS(), app.getFrameTime(), Renderer::getDC());

	app.getWindow().setTitle(buff);
}

void TestECS::onEvent(xe::Event &event) {
	xe::EventDispatcher dispatcher(event);
	dispatcher.dispatch<xe::KeyPressEvent>(METHOD(&TestECS::onKeyPressedEvent));
	dispatcher.dispatch<xe::MousePressEvent>(METHOD(&TestECS::onMousePressedEvent));
	dispatcher.dispatch<xe::MouseMoveEvent>(METHOD(&TestECS::onMouseMovedEvent));
}

bool TestECS::onKeyPressedEvent(xe::KeyPressEvent &event) {
	if (event.getRepeat()) return false;

	if (event.getKey() == XE_KEY_1) {
		GETSOUND("orunec")->play();
		GETSOUND("orunec")->setGain(0.2f);
	}
	if (event.getKey() == XE_KEY_2) {
		GETSOUND("test")->play();
		GETSOUND("test")->setGain(0.2f);
	}
	if (event.getKey() == XE_KEY_3) {
		if (!GETSOUND("orunec")->isPlaying()) {
			GETSOUND("orunec")->loop();
			GETSOUND("orunec")->setGain(0.2f);
		} else {
			GETSOUND("orunec")->stop();
		}
	}

	return false;
}

bool TestECS::onMousePressedEvent(xe::MousePressEvent &event) {
	return false;
}

bool TestECS::onMouseMovedEvent(xe::MouseMoveEvent &event) {
	return false;
}
