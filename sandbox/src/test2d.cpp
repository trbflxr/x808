//
// Created by FLXR on 7/8/2018.
//


#include <xe/app/application.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/texturemanager.hpp>
#include <xe/resources/fontmanager.hpp>
#include <xe/resources/soundmanager.hpp>
#include <xe/utils/random.hpp>
#include <xe/gfx/indexedmodel.hpp>
#include <xe/utils/log.hpp>
#include "xe/utils/utf.hpp"
#include "test2d.hpp"

using namespace xe;

Test2D::Test2D() {
	TextureParameters params(TextureTarget::Tex2D,
	                         PixelInternalFormat::Rgba,
	                         PixelFormat::Rgba,
	                         PixelType::UnsignedByte,
	                         TextureMinFilter::Linear,
	                         TextureMagFilter::Linear,
	                         TextureWrap::ClampToBorder);

	TextureManager::add(new Texture("0", "assets/textures/test1.png", params));
	TextureManager::add(new Texture("1", "assets/textures/test2.png", params));
	TextureManager::add(new Texture("2", "assets/textures/test3.png", params));
	TextureManager::add(new Texture("3", "assets/textures/test4.png", params));
	TextureManager::add(new Texture("4", "assets/textures/test5.png", params));
	TextureManager::add(new Texture("5", "assets/textures/test6.png", params));
	TextureManager::add(new Texture("6", "assets/textures/test7.png", params));
	TextureManager::add(new Texture("7", "assets/textures/test8.png", params));

	TextureManager::add(new Texture("8", "assets/textures/test1.png", params));
	TextureManager::add(new Texture("9", "assets/textures/test2.png", params));
	TextureManager::add(new Texture("10", "assets/textures/test3.png", params));
	TextureManager::add(new Texture("11", "assets/textures/test4.png", params));
	TextureManager::add(new Texture("12", "assets/textures/test5.png", params));
	TextureManager::add(new Texture("13", "assets/textures/test6.png", params));
	TextureManager::add(new Texture("14", "assets/textures/test7.png", params));
	TextureManager::add(new Texture("15", "assets/textures/test8.png", params));

	TextureManager::add(new Texture("16", "assets/textures/test1.png", params));
	TextureManager::add(new Texture("17", "assets/textures/test2.png", params));
	TextureManager::add(new Texture("18", "assets/textures/test3.png", params));
	TextureManager::add(new Texture("19", "assets/textures/test4.png", params));
	TextureManager::add(new Texture("20", "assets/textures/test5.png", params));
	TextureManager::add(new Texture("21", "assets/textures/test6.png", params));
	TextureManager::add(new Texture("22", "assets/textures/test7.png", params));
	TextureManager::add(new Texture("23", "assets/textures/test8.png", params));

	TextureManager::add(new Texture("24", "assets/textures/test1.png", params));
	TextureManager::add(new Texture("25", "assets/textures/test2.png", params));
	TextureManager::add(new Texture("26", "assets/textures/test3.png", params));
	TextureManager::add(new Texture("27", "assets/textures/test4.png", params));
	TextureManager::add(new Texture("28", "assets/textures/test5.png", params));
	TextureManager::add(new Texture("29", "assets/textures/test6.png", params));
	TextureManager::add(new Texture("30", "assets/textures/test7.png", params));
	TextureManager::add(new Texture("31", "assets/textures/test8.png", params));

	TextureManager::add(new Texture("32", "assets/textures/enemyspotted.png", params));
	TextureManager::add(new Texture("33", "assets/textures/enemyspotted.png", params));
	TextureManager::add(new Texture("34", "assets/textures/enemyspotted.png", params));
	TextureManager::add(new Texture("35", "assets/textures/jdm.png", params));
	TextureManager::add(new Texture("36", "assets/textures/test5.png", params));
	TextureManager::add(new Texture("37", "assets/textures/test6.png", params));
	TextureManager::add(new Texture("38", "assets/textures/test7.png", params));
	TextureManager::add(new Texture("39", "assets/textures/test8.png", params));


	FontManager::add(new Font("sourceSans", "assets/fonts/sourcesanspro-regular.ttf", 100));
	FontManager::add(new Font("consolata", "assets/fonts/consolata.otf", 100));


	SoundManager::add(new Sound("test", "assets/sounds/test.wav"));
	SoundManager::add(new Sound("orunec", "assets/sounds/orunec.wav"));


	uint texCount = 10;

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
			sprite.texture = GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1)));

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
			sprite.texture = GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1)));

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

	sprite.texture = GETTEXTURE("35");
	transform.zIndex = 1;
	transform.bounds.setPosition(-10, -10);
	transform.bounds.setSize(20, 20);

	ecs.makeEntity(sprite, transform);

	sprite.texture = GETTEXTURE("35");
	transform.zIndex = 2;
	transform.bounds.setPosition(-4, -4);
	transform.bounds.setSize(20, 20);

	a = ecs.makeEntity(sprite, transform);
}

Test2D::~Test2D() {
	delete spriteRenderer;
	delete textRenderer;
	delete cameraSystem;
}

void Test2D::render() {
	renderer->begin();

	ecs.updateSystems(renderingPipeline, 0.0f);

	renderer->flush();
}

void Test2D::update(float delta) {
	static Transform2DComponent *t = ecs.getComponent<Transform2DComponent>(a);

	vec2i p = Mouse::getPosition(app.getWindow());
	t->bounds.setPosition({p.x / 5.0f, -p.y / 5.0f});

	ecs.updateSystems(mainSystems, delta);
}

void Test2D::input(xe::Event &event) {
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
