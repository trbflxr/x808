//
// Created by FLXR on 7/8/2018.
//


#include <application/application.hpp>
#include <gfx/renderer.hpp>
#include <resources/texturemanager.hpp>
#include <resources/fontmanager.hpp>
#include <resources/soundmanager.hpp>
#include <utils/random.hpp>
#include <gfx/indexedmodel.hpp>
#include "utils/utf.hpp"
#include "testecs.hpp"

using namespace xe;
using namespace gfx;
using namespace gfx::api;


TestECS::TestECS() {

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
	textRenderer = new TextRendererSystem(renderer);

	renderingPipeline.addSystem(*spriteRenderer);
	renderingPipeline.addSystem(*textRenderer);

	//main systems
	cameraSystem = new OrthoCameraMoveSystem(renderer);

	mainSystems.addSystem(*cameraSystem);


	//create camera
	CameraComponent camera(mat4::ortho(-80.0f, 80.0f, -60.0f, 60.0f, -1, 1000));
	cameraEntity = ecs.makeEntity(camera);

	//sprite components
	SpriteComponent sprite;
	Transform2DComponent transform;

	uint sprites = 0;

	/// 0 - 1
	/// 1 - 1.2k
	/// 2 - 11k
	/// 3 - 59k
#define sp_size 1

#if sp_size == 3
	for (float x = -80; x < 80; x += 0.57f) {
		for (float y = -60; y < 60; y += 0.57f) {
			sprite.texture = &GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1)));

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
			sprite.texture = &GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1)));

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
			sprite.texture = GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1)));

			transform.zIndex = 0;
			transform.bounds.setPosition(x, y);
			transform.bounds.setSize(3, 3);

			a = ecs.makeEntity(sprite, transform);

			++sprites;
		}
	}
#elif sp_size == 0
	sprite.texture = &GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1)));

	transform.zIndex = 0;
	transform.bounds.setPosition(0, 0);
	transform.bounds.setSize(3, 3);

	a = ecs.makeEntity(sprite, transform);

	++sprites;
#endif

	XE_INFO("size: ", sprites);

	TextComponent t;
	t.size = 20;
	t.font = GETFONT("consolata");
	t.outlineThickness = 3;

	t.string = L"слава ukraine";
	t.position = {-70, 30};
	t.textColor = color::WHITE;
	t.outlineColor = color::BLACK;
	text = ecs.makeEntity(t);

	t.string = L"Input:";
	t.position = {-70, -20};
	t.textColor = color::PINK;
	t.outlineColor = color::CYAN;
	inputText = ecs.makeEntity(t);

	sprite.texture = GETTEXTURE("32");
	transform.zIndex = 1;
	transform.bounds.setPosition(-10, -10);
	transform.bounds.setSize(20, 20);

	a = ecs.makeEntity(sprite, transform);
}

TestECS::~TestECS() {
	delete spriteRenderer;
	delete textRenderer;
	delete cameraSystem;
}

void TestECS::render() {
	renderer->begin();

	ecs.updateSystems(renderingPipeline, 0.0f);

	renderer->flush();
}

void TestECS::update(float delta) {
//	Transform2DComponent *t = ecs.getComponent<Transform2DComponent>(a);
	ecs.updateSystems(mainSystems, delta);
}

void TestECS::input(xe::Event &event) {
	switch (event.type) {
		default: break;

		case Event::KeyPressed: {
			if (event.key.code == Keyboard::Num1) {
				GETSOUND("orunec")->play();
				GETSOUND("orunec")->setGain(0.2f);
				event.handled = true;
			}
			if (event.key.code == Keyboard::Num2) {
				GETSOUND("test")->play();
				GETSOUND("test")->setGain(0.2f);
				event.handled = true;
			}
			if (event.key.code == Keyboard::Num3) {
				if (!GETSOUND("orunec")->isPlaying()) {
					GETSOUND("orunec")->loop();
					GETSOUND("orunec")->setGain(0.2f);
				} else {
					GETSOUND("orunec")->stop();
				}
				event.handled = true;
			}
			break;
		}

		case Event::MouseButtonPressed: {

			break;
		}

		case Event::MouseMoved: {
//			XE_INFO("mouse(x: ", event.mouseMove.x, ", y:", event.mouseMove.y, ")");

			break;
		}

		case Event::TextEntered: {
			static TextComponent *t = ecs.getComponent<TextComponent>(inputText);

			if (event.text.unicode == 8) {
				if (!inputString.empty()) {
					inputString.erase(inputString.end() - 1);
				}
			} else {
				inputString += event.text.unicode;
			}

			t->string = inputString.c_str();

			break;
		}

	}

}
