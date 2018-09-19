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
#include <xe/gfx/circleshape.hpp>
#include "xe/utils/utf.hpp"
#include "test2d.hpp"

using namespace xe;

Test2D::Test2D() {
	const float width = app.getConfig().width;
	const float height = app.getConfig().height;

	TextureParameters params;

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
	TextureManager::add(new Texture("35", "assets/textures/jdm.png", params, true));
	TextureManager::add(new Texture("36", "assets/textures/star.png", params, true));
	TextureManager::add(new Texture("37", "assets/textures/cosmic.png", params, true));
	TextureManager::add(new Texture("38", "assets/textures/test7.png", params));
	TextureManager::add(new Texture("39", "assets/textures/test8.png", params));


	FontManager::add(new Font("sourceSans", "assets/fonts/sourcesanspro-regular.ttf", 100));
	FontManager::add(new Font("consolata", "assets/fonts/consolata.otf", 100));


	SoundManager::add(new Sound("test", "assets/sounds/test.wav"));
	SoundManager::add(new Sound("orunec", "assets/sounds/orunec.wav"));

	uint texCount = 38;


	camera = new Camera(mat4::ortho(-width, width, -height, height, -1000, 1000));
	renderer = new BatchRenderer2D(width, height, camera);

	uint sprites = 0;

	/// 0 - 1
	/// 1 - 1.2k
	/// 2 - 11k
	/// 3 - 59k
#define sp_size 1

#if sp_size == 3
	for (float x = -800; x < 800; x += 5.7f) {
		for (float y = -600; y < 600; y += 5.7f) {
			RectangleShape *s = new RectangleShape({4.9f, 4.9f}, 0.0f);
			s->setTexture(GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1))));
			s->transformation({x, y});

			renderables.push_back(s);

			++sprites;
		}
	}
#elif sp_size == 2
	for (float x = -800; x < 800; x += 10.3f) {
		for (float y = -600; y < 600; y += 10.3f) {
			RectangleShape *s = new RectangleShape({9.0f, 9.0f}, 0.0f);
			s->setTexture(GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1))));
			s->transformation({x, y});

			renderables.push_back(s);

			++sprites;
		}
	}
#elif sp_size == 1
	for (int32 x = -800; x < 800; x += 40) {
		for (int32 y = -600; y < 600; y += 40) {
			RectangleShape *s = new RectangleShape({30.0f, 30.0f}, 0.0f);
			s->setTexture(GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1))));
			s->transformation(vec2(x, y));

			renderables.push_back(s);

			++sprites;
		}
	}
#endif

	XE_INFO("size: ", sprites);

	inputText = new Text(L"слава ukraine", 200, {-700, 300}, GETFONT("consolata"), color::PINK, color::CYAN, 3);

	RectangleShape *s0 = new RectangleShape({200.0f, 200.0f}, 2.0f);
	s0->setTexture(GETTEXTURE("35"));
	s0->transformation({-100.0f, -100.0f});

	RectangleShape *s1 = new RectangleShape({200.0f, 200.0f}, 4.0f);
	s1->setTexture(GETTEXTURE("37"));
	s1->transformation({-40.0f, -40.0f});

	star = new RectangleShape({200.0f, 200.0f}, 3.0f);
	star->setTexture(GETTEXTURE("36"));
	star->transformation({-40.0f, -40.0f});

	renderables.push_back(s0);
//	renderables.push_back(s1);
//	renderables.push_back(star);


	//circle test
	CircleShape *c0 = new CircleShape(300.0f, 1.0f);
	c0->setTexture(GETTEXTURE("1"));
	c0->transformation({-40.0f, -40.0f});

	renderables.push_back(c0);
}

Test2D::~Test2D() {
	delete camera;
	delete renderer;

	for (const auto &r : renderables) {
		delete r;
	}

	delete inputText;
}

void Test2D::render() {
	for (const auto &r : renderables) {
//		((RectangleShape *) r)->rotate(0.5f);
		renderer->submit(r);
	}

	renderer->submit(inputText);

	renderer->renderSprites();
	renderer->renderText();

	renderer->clear();
}

void Test2D::update(float delta) {
	static const vec2i halfSize = window.getSize() / 2;

	const vec2 p = Mouse::getPosition(window);
	const vec2 pos = vec2((p.x - halfSize.x) * 2.0f, (p.y - halfSize.y) * 2.0f);

	star->setPosition(pos);

	///update camera
	vec3 camPos = camera->transform.getPosition();

	if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::D)) {
		camPos.x += 1000 * delta;
	}
	if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::A)) {
		camPos.x -= 1000 * delta;
	}
	if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::W)) {
		camPos.y += 1000 * delta;
	}
	if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::S)) {
		camPos.y -= 1000 * delta;
	}
	camera->transform.setPosition(camPos);

	camera->update();
}

void Test2D::input(xe::Event &event) {
	switch (event.type) {
		default: break;

		case Event::KeyPressed: {
			if (event.key.code == Keyboard::Num0) {
				GETSOUND("orunec")->play();
				GETSOUND("orunec")->setGain(0.2f);
				event.handled = true;
			}
			if (event.key.code == Keyboard::Num9) {
				GETSOUND("test")->play();
				GETSOUND("test")->setGain(0.2f);
				event.handled = true;
			}
			if (event.key.code == Keyboard::Num8) {
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
			if (event.text.unicode == 8) {
				if (!inputText->getString().empty()) {
					inputText->getString().erase(inputText->getString().end() - 1);
				}
			} else {
				inputText->getString() += event.text.unicode;
			}

			break;
		}

	}

}
