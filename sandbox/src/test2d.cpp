//
// Created by FLXR on 7/8/2018.
//


#include <xe/app/application.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/texturemanager.hpp>
#include <xe/resources/soundmanager.hpp>
#include <xe/utils/random.hpp>
#include <xe/gfx/indexedmodel.hpp>
#include <xe/utils/logger.hpp>
#include <xe/gfx/circleshape.hpp>
#include <xe/systems/shell.hpp>
#include <xe/ui/imgui/imgui_impl_xe.hpp>
#include "test2d.hpp"

using namespace xe;

Test2D::Test2D() {
	addShellCommands();

	const float width = app.getWindowSize().x;
	const float height = app.getWindowSize().y;

	Timer timer;

	TextureParameters params;

	TextureManager::add(new Texture("0", "test1.png", params));
	TextureManager::add(new Texture("1", "test2.png", params));
	TextureManager::add(new Texture("2", "test3.png", params));
	TextureManager::add(new Texture("3", "test4.png", params));
	TextureManager::add(new Texture("4", "test5.png", params));
	TextureManager::add(new Texture("5", "test6.png", params));
	TextureManager::add(new Texture("6", "test7.png", params));
	TextureManager::add(new Texture("7", "test8.png", params));

	TextureManager::add(new Texture("8", "test1.png", params));
	TextureManager::add(new Texture("9", "test2.png", params));
	TextureManager::add(new Texture("10", "test3.png", params));
	TextureManager::add(new Texture("11", "test4.png", params));
	TextureManager::add(new Texture("12", "test5.png", params));
	TextureManager::add(new Texture("13", "test6.png", params));
	TextureManager::add(new Texture("14", "test7.png", params));
	TextureManager::add(new Texture("15", "test8.png", params));

	TextureManager::add(new Texture("16", "test1.png", params));
	TextureManager::add(new Texture("17", "test2.png", params));
	TextureManager::add(new Texture("18", "test3.png", params));
	TextureManager::add(new Texture("19", "test4.png", params));
	TextureManager::add(new Texture("20", "test5.png", params));
	TextureManager::add(new Texture("21", "test6.png", params));
	TextureManager::add(new Texture("22", "test7.png", params));
	TextureManager::add(new Texture("23", "test8.png", params));

	TextureManager::add(new Texture("24", "test1.png", params));
	TextureManager::add(new Texture("25", "test2.png", params));
	TextureManager::add(new Texture("26", "test3.png", params));
	TextureManager::add(new Texture("27", "test4.png", params));
	TextureManager::add(new Texture("28", "test5.png", params));
	TextureManager::add(new Texture("29", "test6.png", params));
	TextureManager::add(new Texture("30", "test7.png", params));
	TextureManager::add(new Texture("31", "error.png", params));

	TextureManager::add(new Texture("32", "enemyspotted.png", params));
	TextureManager::add(new Texture("33", "enemyspotted.png", params));
	TextureManager::add(new Texture("34", "enemyspotted.png", params));
	TextureManager::add(new Texture("35", "jdm.png", params));
	TextureManager::add(new Texture("36", "star.png", params));
	TextureManager::add(new Texture("37", "cosmic.png", params));
	TextureManager::add(new Texture("38", "test7.png", params));
	TextureManager::add(new Texture("39", "test8.png", params));

	params.wrap = TextureWrap::Repeat;
	TextureManager::add(new Texture("repeat", "sp0.png", params));

	timer.reset();
	XE_TRACE("Tex load elapsed: ", timer.elapsedMillis(), "ms");

	SoundManager::add(new Sound("test", "xe_sandbox_assets/sounds/test.wav"));
	SoundManager::add(new Sound("orunec", "xe_sandbox_assets/sounds/orunec.wav"));


	FontManager::add(new Font("consolata72", "consolata.otf", 72.0f));
	FontManager::add(new Font("consolata32", "consolata.otf", 32.0f));
	FontManager::add(new Font("fogsans72", "fogsans.otf", 72.0f));
	FontManager::add(new Font("fogsansit72", "fogsansit.otf", 72.0f));
	FontManager::add(new Font("robotoregular72", "robotoregular.ttf", 72.0f));
	FontManager::add(new Font("robotobold72", "robotobold.ttf", 72.0f));

	uint texCount = 40;

	createCamera(width, height, -1.0f, 1000.0f);
	createRenderer(width, height);

	uint sprites = 0;

	/// 1 - 2304
	/// 2 - 14400
	/// 3 - 60865
	/// 4 - 102480
#define sp_size 2

	timer.reset();

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

	XE_TRACE("size: ", sprites);
	XE_TRACE("elapsed: ", timer.elapsedMillis(), "ms");

	inputText = new Text("consolata72", GETFONT("consolata72"));
	inputText->setTextColor(color::White);
	inputText->setOutlineColor(color::Black);
	inputText->setOutlineThickness(3.0f);
	inputText->setPosition({50.0f, 500.0f});
	text.push_back(inputText);

	Text *t0 = new Text("fogsans72", GETFONT("fogsans72"));
	t0->setTextColor(color::White);
	t0->setOutlineColor(color::Black);
	t0->setOutlineThickness(3.0f);
	t0->setPosition({50.0f, 400.0f});
	text.push_back(t0);

	Text *t1 = new Text("fogsansit72", GETFONT("fogsansit72"));
	t1->setTextColor(color::White);
	t1->setOutlineColor(color::Black);
	t1->setOutlineThickness(3.0f);
	t1->setPosition({50.0f, 300.0f});
	text.push_back(t1);

	Text *t2 = new Text("robotoregular72", GETFONT("robotoregular72"));
	t2->setTextColor(color::White);
	t2->setOutlineColor(color::Black);
	t2->setOutlineThickness(3.0f);
	t2->setPosition({50.0f, 200.0f});
	text.push_back(t2);

	Text *t3 = new Text("robotobold72", GETFONT("robotobold72"));
	t3->setTextColor(color::White);
	t3->setOutlineColor(color::Black);
	t3->setOutlineThickness(3.0f);
	t3->setPosition({50.0f, 100.0f});
	text.push_back(t3);

	string s = std::to_string(sprites);
	s += " sprites drawn with ";
	s += std::to_string(texCount);
	s += " different textures🌍";

	Text *t4 = new Text(s, GETFONT("consolata32"));
	t4->setTextColor(color::Red);
	t4->setOutlineColor(color::Black);
	t4->setOutlineThickness(3.0f);
	t4->setPosition({10.0f, height - 50.0f});
	text.push_back(t4);

	RectangleShape *s0 = new RectangleShape({100.0f, 100.0f}, 2.0f);
	s0->setTexture(GETTEXTURE("35"));
	s0->transformation({640.0f, 420.0f});
	renderables.push_back(s0);

	RectangleShape *s1 = new RectangleShape({100.0f, 100.0f}, 4.0f);
	s1->setTexture(GETTEXTURE("37"));
	s1->transformation({640.0f, 350.0f});
	renderables.push_back(s1);

	RectangleShape *bg = new RectangleShape({width, height}, 0.0f);
	bg->setTexture(GETTEXTURE("repeat"));
	bg->transformation({width + width / 2.0f, height / 2.0f});
	bg->setTextureRect({0.0f, 0.0f, width, height});
	renderables.push_back(bg);

	star = new RectangleShape({100.0f, 100.0f}, 3.0f);
	star->setTexture(GETTEXTURE("36"));
	star->transformation({640.0f, 350.0f});
	renderables.push_back(star);

	//circle test
	CircleShape *c0 = new CircleShape(50.0f, 2.0f);
	c0->setTexture(GETTEXTURE("1"));
	c0->transformation({710.0f, 350.0f});
	renderables.push_back(c0);

	Renderer::setClearColor(0xff57513c);
}

Test2D::~Test2D() {
	for (const auto &r : renderables) {
		delete r;
	}

	for (const auto &t : text) {
		delete t;
	}
}

void Test2D::renderScene() {
	for (const auto &r : renderables) {
//		((RectangleShape *) r)->rotate(0.5f);
		submit(r);
	}

	for (const auto &t : text) {
		submit(t);
	}
}

void Test2D::renderImGui() {
	ImGui::Begin("UI", nullptr);

	//debug
	ImGui::Text("info");
	ImGui::Text("fps: %i", app.getFPS());
	ImGui::Text("frame time: %.3f", app.getFrameTime());
	ImGui::Separator();
	ImGui::Dummy({10.0f, 0.0f});


	//sound section
	ImGui::Text("Sound test");

	if (ImGui::Button("test")) {
		GETSOUND("test")->play();
		GETSOUND("test")->setGain(0.2f);
	}
	ImGui::SameLine();

	if (ImGui::Button("orunec")) {
		GETSOUND("orunec")->play();
		GETSOUND("orunec")->setGain(0.2f);
	}
	ImGui::SameLine();

	if (ImGui::Button("orunec looped")) {
		if (!GETSOUND("orunec")->isPlaying()) {
			GETSOUND("orunec")->loop();
			GETSOUND("orunec")->setGain(0.2f);
		} else {
			GETSOUND("orunec")->stop();
		}
	}

	ImGui::End();
}

void Test2D::update(float delta) {
	const vec2 pos = vec2(Mouse::getPosition(window) + vec2(getCamera()->transform.getPosition()));

	star->setPosition(pos);

	///update camera
	vec3 camPos = getCamera()->transform.getPosition();

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
	getCamera()->transform.setPosition(camPos);

	getCamera()->update();
}

void Test2D::input(xe::Event &event) {
	switch (event.type) {
		default: break;

		case Event::KeyPressed: {

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
					string &utf8 = inputText->getString();
					char *cp = utf8.data() + utf8.size();
					while (--cp >= utf8.data() && ((*cp & 0b10000000) && !(*cp & 0b01000000)));
					if (cp >= utf8.data()) {
						utf8.resize(cp - utf8.data());
					}
				}
			} else {
				inputText->getString() += (const char *) &event.text.unicode;
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

		getRenderer()->getRenderer2D()->enableWireframe(enable);

		return "";
	});
}
