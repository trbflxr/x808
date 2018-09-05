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
	renderer = new Renderer2D(window.getSize());

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


	const float width = app.getConfig().width;
	const float height = app.getConfig().height;

	uint texCount = 35;

	//render system
	spriteRenderer = new SpriteRendererSystem(renderer);
	textRenderer = new TextRendererSystem(renderer);

	renderingPipeline.addSystem(*spriteRenderer);
	renderingPipeline.addSystem(*textRenderer);

	//main systems
	cameraSystem = new OrthoCameraMoveSystem(renderer);

	mainSystems.addSystem(*cameraSystem);


	//create camera
	cameraEntity = ecs.makeEntity(
			new CameraComponent(mat4::ortho(-width, width, -height, height, -1, 1000)));


	uint sprites = 0;

	/// 0 - 1
	/// 1 - 1.2k
	/// 2 - 11k
	/// 3 - 59k
#define sp_size 3

#if sp_size == 3
	for (float x = -800; x < 800; x += 5.7f) {
		for (float y = -600; y < 600; y += 5.7f) {
			SpriteComponent *s = new SpriteComponent(GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1))));
			Transform2DComponent *t = new Transform2DComponent(vec2(x, y), vec2(4.9f), 0.0f);

			a = ecs.makeEntity(s, t);

			++sprites;
		}
	}
#elif sp_size == 2
	for (float x = -800; x < 800; x += 10.3f) {
		for (float y = -600; y < 600; y += 10.3f) {
			SpriteComponent *s = new SpriteComponent(GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1))));
			Transform2DComponent *t = new Transform2DComponent(vec2(x, y), vec2(9.0f), 0.0f);

			a = ecs.makeEntity(s, t);

			++sprites;
		}
	}
#elif sp_size == 1
	for (int32 x = -800; x < 800; x += 40) {
		for (int32 y = -600; y < 600; y += 40) {
			SpriteComponent *s = new SpriteComponent(GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1))));
			Transform2DComponent *t = new Transform2DComponent(vec2(x, y), vec2(30.0f), 0.0f);

			a = ecs.makeEntity(s, t);

			++sprites;
		}
	}
#elif sp_size == 0
	SpriteComponent *s = new SpriteComponent(GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1))));
	Transform2DComponent *t = new Transform2DComponent(vec2(0, 0), vec2(30.0f), 0.0f);

	a = ecs.makeEntity(s, t);

	++sprites;
#endif

	XE_INFO("size: ", sprites);

	text = ecs.makeEntity(new TextComponent(new Text(L"i:", 200, {-700, 300},
	                                                 GETFONT("default"), color::LIGHTGRAY, color::GRAY, 3)));

	inputText = ecs.makeEntity(new TextComponent(new Text(L"слава ukraine", 200, {-700, 100},
	                                                      GETFONT("consolata"), color::PINK, color::CYAN, 3)));

	ecs.makeEntity(new TextComponent(new Text(L"0", 200, {-200, -100},
	                                          GETFONT("consolata"), color::RED, color::GREEN, 3)));

	SpriteComponent *s0 = new SpriteComponent(GETTEXTURE("35"));
	SpriteComponent *s1 = new SpriteComponent(GETTEXTURE("35"));

	Transform2DComponent *t0 = new Transform2DComponent(vec2(-100.0f, -100.0f), vec2(200.0f), 1.0f);
	Transform2DComponent *t1 = new Transform2DComponent(vec2(-40.0f, -40.0f), vec2(200.0f), 1.0f);

	ecs.makeEntity(s0, t0);
	a = ecs.makeEntity(s1, t1);
}

Test2D::~Test2D() {
	delete renderer;
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

	static const vec2i halfSize = window.getSize() / 2;
	static constexpr float spriteHalfSize = 50.0f;

	const vec2i p = Mouse::getPosition(window);
	const vec2 pos = vec2((p.x - halfSize.x - spriteHalfSize) * 2.0f, -(p.y - halfSize.y + spriteHalfSize) * 2.0f);

	t->bounds.setPosition(pos);

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
				if (!t->text->getString().empty()) {
					t->text->getString().erase(t->text->getString().end() - 1);
				}
			} else {
				t->text->getString() += event.text.unicode;
			}

			break;
		}

	}

}
