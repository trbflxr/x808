//
// Created by FLXR on 7/8/2018.
//


#include <xe/app/application.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/texturemanager.hpp>
#include <xe/resources/soundmanager.hpp>
#include <xe/utils/random.hpp>
#include <xe/gfx/indexedmodel.hpp>
#include <xe/utils/log.hpp>
#include <xe/gfx/circleshape.hpp>
#include <xe/systems/shell.hpp>
#include "test2d.hpp"

using namespace xe;

Test2D::Test2D() {
	addShellCommands();

	const float width = app.getConfig().width;
	const float height = app.getConfig().height;

	TextureParameters params;

	TextureManager::add(new Texture("0", L"assets/textures/test1.png", params));
	TextureManager::add(new Texture("1", L"assets/textures/test2.png", params));
	TextureManager::add(new Texture("2", L"assets/textures/test3.png", params));
	TextureManager::add(new Texture("3", L"assets/textures/test4.png", params));
	TextureManager::add(new Texture("4", L"assets/textures/test5.png", params));
	TextureManager::add(new Texture("5", L"assets/textures/test6.png", params));
	TextureManager::add(new Texture("6", L"assets/textures/test7.png", params));
	TextureManager::add(new Texture("7", L"assets/textures/test8.png", params));

	TextureManager::add(new Texture("8", L"assets/textures/test1.png", params));
	TextureManager::add(new Texture("9", L"assets/textures/test2.png", params));
	TextureManager::add(new Texture("10", L"assets/textures/test3.png", params));
	TextureManager::add(new Texture("11", L"assets/textures/test4.png", params));
	TextureManager::add(new Texture("12", L"assets/textures/test5.png", params));
	TextureManager::add(new Texture("13", L"assets/textures/test6.png", params));
	TextureManager::add(new Texture("14", L"assets/textures/test7.png", params));
	TextureManager::add(new Texture("15", L"assets/textures/test8.png", params));

	TextureManager::add(new Texture("16", L"assets/textures/test1.png", params));
	TextureManager::add(new Texture("17", L"assets/textures/test2.png", params));
	TextureManager::add(new Texture("18", L"assets/textures/test3.png", params));
	TextureManager::add(new Texture("19", L"assets/textures/test4.png", params));
	TextureManager::add(new Texture("20", L"assets/textures/test5.png", params));
	TextureManager::add(new Texture("21", L"assets/textures/test6.png", params));
	TextureManager::add(new Texture("22", L"assets/textures/test7.png", params));
	TextureManager::add(new Texture("23", L"assets/textures/test8.png", params));

	TextureManager::add(new Texture("24", L"assets/textures/test1.png", params));
	TextureManager::add(new Texture("25", L"assets/textures/test2.png", params));
	TextureManager::add(new Texture("26", L"assets/textures/test3.png", params));
	TextureManager::add(new Texture("27", L"assets/textures/test4.png", params));
	TextureManager::add(new Texture("28", L"assets/textures/test5.png", params));
	TextureManager::add(new Texture("29", L"assets/textures/test6.png", params));
	TextureManager::add(new Texture("30", L"assets/textures/test7.png", params));
	TextureManager::add(new Texture("31", L"assets/textures/error.png", params));

	TextureManager::add(new Texture("32", L"assets/textures/enemyspotted.png", params));
	TextureManager::add(new Texture("33", L"assets/textures/enemyspotted.png", params));
	TextureManager::add(new Texture("34", L"assets/textures/enemyspotted.png", params));
	TextureManager::add(new Texture("35", L"assets/textures/jdm.png", params));
	TextureManager::add(new Texture("36", L"assets/textures/star.png", params));
	TextureManager::add(new Texture("37", L"assets/textures/cosmic.png", params));
	TextureManager::add(new Texture("38", L"assets/textures/test7.png", params));
	TextureManager::add(new Texture("39", L"assets/textures/test8.png", params));


	SoundManager::add(new Sound("test", "assets/sounds/test.wav"));
	SoundManager::add(new Sound("orunec", "assets/sounds/orunec.wav"));


	FontManager::add(new Font("consolata72", L"assets/fonts/consolata.otf", 72.0f));
	FontManager::add(new Font("consolata32", L"assets/fonts/consolata.otf", 32.0f));
	FontManager::add(new Font("fogsans72", L"assets/fonts/fogsans.otf", 72.0f));
	FontManager::add(new Font("fogsansit72", L"assets/fonts/fogsansit.otf", 72.0f));
	FontManager::add(new Font("robotoregular72", L"assets/fonts/robotoregular.ttf", 72.0f));
	FontManager::add(new Font("robotobold72", L"assets/fonts/robotobold.ttf", 72.0f));

	uint texCount = 40;

	camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1000.0f));
	renderer = new BatchRenderer2D(width, height, camera);

	uint sprites = 0;

	/// 1 - 2304
	/// 2 - 14400
	/// 3 - 60865
	/// 4 - 102480
#define sp_size 2

	Timer timer;

#if sp_size == 4
	for (float x = 0.0f; x < 1280; x += 3.0f) {
		for (float y = 0.0f; y < 720; y += 3.0f) {
			RectangleShape *s = new RectangleShape({2.5f, 2.5f}, 0.0f);
			s->setTexture(GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1))));
			s->transformation({x, y});

			renderables.push_back(s);

			++sprites;
		}
	}
#elif sp_size == 3
	for (float x = 0.0f; x < 1280; x += 3.9f) {
		for (float y = 0.0f; y < 720; y += 3.9f) {
			RectangleShape *s = new RectangleShape({3.4f, 3.4f}, 0.0f);
			s->setTexture(GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1))));
			s->transformation({x, y});

			renderables.push_back(s);

			++sprites;
		}
	}
#elif sp_size == 2
	for (uint x = 0; x < 1280; x += 8) {
		for (uint y = 0; y < 720; y += 8) {
			RectangleShape *s = new RectangleShape({6.0f, 6.0f}, 0.0f);
			s->setTexture(GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1))));
			s->transformation(vec2(x + 3.0f, y + 3.0f));

			renderables.push_back(s);

			++sprites;
		}
	}
#elif sp_size == 1
	for (int32 x = 0; x < 1280; x += 20) {
		for (int32 y = 0; y < 720; y += 20) {
			RectangleShape *s = new RectangleShape({15.0f, 15.0f}, 0.0f);
			s->setTexture(GETTEXTURE(std::to_string(random::nextUint(0, texCount - 1))));
			s->transformation(vec2(x + 7.5f, y + 7.5f));

			renderables.push_back(s);

			++sprites;
		}
	}
#endif

	timer.reset();

	XE_INFO(L"size: ", sprites);
	XE_INFO(L"elapsed: ", timer.elapsedMillis(), L" ms");

	inputText = new Text(L"consolata72", GETFONT("consolata72"));
	inputText->setTextColor(color::WHITE);
	inputText->setOutlineColor(color::BLACK);
	inputText->setOutlineThickness(3.0f);
	inputText->setPosition({50.0f, 500.0f});
	text.push_back(inputText);

	Text *t0 = new Text(L"fogsans72", GETFONT("fogsans72"));
	t0->setTextColor(color::WHITE);
	t0->setOutlineColor(color::BLACK);
	t0->setOutlineThickness(3.0f);
	t0->setPosition({50.0f, 400.0f});
	text.push_back(t0);

	Text *t1 = new Text(L"fogsansit72", GETFONT("fogsansit72"));
	t1->setTextColor(color::WHITE);
	t1->setOutlineColor(color::BLACK);
	t1->setOutlineThickness(3.0f);
	t1->setPosition({50.0f, 300.0f});
	text.push_back(t1);

	Text *t2 = new Text(L"robotoregular72", GETFONT("robotoregular72"));
	t2->setTextColor(color::WHITE);
	t2->setOutlineColor(color::BLACK);
	t2->setOutlineThickness(3.0f);
	t2->setPosition({50.0f, 200.0f});
	text.push_back(t2);

	Text *t3 = new Text(L"robotobold72", GETFONT("robotobold72"));
	t3->setTextColor(color::WHITE);
	t3->setOutlineColor(color::BLACK);
	t3->setOutlineThickness(3.0f);
	t3->setPosition({50.0f, 100.0f});
	text.push_back(t3);

	wstring s = std::to_wstring(sprites);
	s += L" sprites drawn with ";
	s += std::to_wstring(texCount);
	s += L" different textures";

	Text *t4 = new Text(s, GETFONT("consolata32"));
	t4->setTextColor(color::RED);
	t4->setOutlineColor(color::BLACK);
	t4->setOutlineThickness(3.0f);
	t4->setPosition({10.0f, height - 50.0f});
	text.push_back(t4);

	RectangleShape *s0 = new RectangleShape({100.0f, 100.0f}, 2.0f);
	s0->setTexture(GETTEXTURE("35"));
	s0->transformation({640.0f, 420.0f});

	RectangleShape *s1 = new RectangleShape({100.0f, 100.0f}, 4.0f);
	s1->setTexture(GETTEXTURE("37"));
	s1->transformation({640.0f, 350.0f});

	star = new RectangleShape({100.0f, 100.0f}, 3.0f);
	star->setTexture(GETTEXTURE("36"));
	star->transformation({640.0f, 350.0f});

	renderables.push_back(s0);
	renderables.push_back(s1);
	renderables.push_back(star);


	//circle test
	CircleShape *c0 = new CircleShape(50.0f, 2.0f);
	c0->setTexture(GETTEXTURE("1"));
	c0->transformation({710.0f, 350.0f});
	renderables.push_back(c0);

	Renderer::setClearColor(0xff57513c);
}

Test2D::~Test2D() {
	delete camera;
	delete renderer;

	for (const auto &r : renderables) {
		delete r;
	}

	for (const auto &t : text) {
		delete t;
	}

}

void Test2D::render() {
	for (const auto &r : renderables) {
//		((RectangleShape *) r)->rotate(0.5f);
		renderer->submit(r);
	}

	for (const auto &t : text) {
		renderer->submit(t);
	}

	renderer->renderSprites();
	renderer->renderText();

	renderer->clear();
}

void Test2D::update(float delta) {
	const vec2 pos = vec2(Mouse::getPosition(window) + vec2(camera->transform.getPosition()));

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

void Test2D::addShellCommands() {
	Shell &shell = app.getShell();

	shell.addCommand("r2d_wireframe", [&](const std::vector<string> &args, bool hint) -> string {
		if (hint) return "Enable / disable wireframe for renderer2d.\n  Example: r2d_wireframe (0 || 1)";

		bool enable;
		if (args[0] == "1") {
			enable = true;
		} else if (args[0] == "0") {
			enable = false;
		} else {
			return "[E]Bad args. Type r2d_wireframe -h for help";
		}

		renderer->getRenderer2D()->enableWireframe(enable);

		return "";
	});
}
