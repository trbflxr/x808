//
// Created by FLXR on 7/8/2018.
//


#include <xe/app/application.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/texturemanager.hpp>
#include <xe/utils/random.hpp>
#include <xe/utils/logger.hpp>
#include <xe/gfx/2d/circleshape.hpp>
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

	TextureManager::add(new TextureAtlas("atlas", "test.atlas", params));

	params.wrap = TextureWrap::Repeat;
	TextureManager::add(new Texture("repeat", "sp0.png", params));

	timer.reset();
	XE_TRACE("Tex load elapsed: ", timer.elapsedMillis(), "ms");

	std::vector<rect> rects;
	for (const auto &a : GETATLAS("atlas")->getAreas()) {
		rects.push_back(a.second);
	}

	FontManager::add(new Font("consolata72", "consolata.otf", 72.0f));
	FontManager::add(new Font("consolata32", "consolata.otf", 32.0f));
	FontManager::add(new Font("fogsans72", "fogsans.otf", 72.0f));
	FontManager::add(new Font("fogsansit72", "fogsansit.otf", 72.0f));
	FontManager::add(new Font("robotoregular72", "robotoregular.ttf", 72.0f));
	FontManager::add(new Font("robotobold72", "robotobold.ttf", 72.0f));

	uint texCount = rects.size();

	camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1000.0f));
	renderer = new Renderer2D(width, height, camera);

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
			RectangleShape *s = new RectangleShape({2.5f, 2.5f});
			s->setTexture(GETTEXTURE(std::to_string(random::next<uint>(0, texCount - 1))));
			s->transformation({x, y});

			renderables.push_back(s);

			++sprites;
		}
	}
#elif sp_size == 3
	for (float x = 0.0f; x < 1280; x += 3.9f) {
		for (float y = 0.0f; y < 720; y += 3.9f) {
			RectangleShape *s = new RectangleShape({3.4f, 3.4f});
			s->setTexture(GETTEXTURE(std::to_string(random::next<uint>(0, texCount - 1))));
			s->transformation({x, y});

			renderables.push_back(s);

			++sprites;
		}
	}
#elif sp_size == 2
	for (uint x = 0; x < 1280; x += 8) {
		for (uint y = 0; y < 720; y += 8) {
			RectangleShape *s = new RectangleShape({6.0f, 6.0f});
			s->setTexture(GETATLAS("atlas")->getTexture());
			s->setTextureRect(rects[random::next<uint>(0, texCount - 1)]);
			s->transformation(vec2(x + 3.0f, y + 3.0f));

			renderables.push_back(s);

			++sprites;
		}
	}
#elif sp_size == 1
	for (int32 x = 0; x < 1280; x += 20) {
		for (int32 y = 0; y < 720; y += 20) {
			RectangleShape *s = new RectangleShape({15.0f, 15.0f});
			s->setTexture(GETTEXTURE(std::to_string(random::next<uint>(0, texCount - 1))));
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

	RectangleShape *s0 = new RectangleShape({100.0f, 100.0f});
	s0->setTexture(GETATLAS("atlas")->getTexture());
	s0->setTextureRect(GETATLAS("atlas")->getArea("test2.png"));
	s0->transformation({640.0f, 420.0f});
	renderables.push_back(s0);

	RectangleShape *s1 = new RectangleShape({100.0f, 100.0f});
	s1->setTexture(GETATLAS("atlas")->getTexture());
	s1->setTextureRect(GETATLAS("atlas")->getArea("translucent.png"));
	s1->transformation({640.0f, 350.0f});
	renderables.push_back(s1);

	RectangleShape *bg = new RectangleShape({width, height});
	bg->setTexture(GETTEXTURE("repeat"));
	bg->setTextureRect({0.0f, 0.0f, width, height});
	bg->transformation({width + width / 2.0f, height / 2.0f});
	renderables.push_back(bg);

	star = new RectangleShape({100.0f, 100.0f});
	star->setTexture(GETATLAS("atlas")->getTexture());
	star->setTextureRect(GETATLAS("atlas")->getArea("star.png"));
	star->transformation({640.0f, 350.0f});
	renderables.push_back(star);

	//circle test
	c0 = new CircleShape(50.0f);
	c0->setTexture(GETATLAS("atlas")->getTexture());
	c0->setTextureRect(GETATLAS("atlas")->getArea("test1.png"));
	c0->transformation({710.0f, 350.0f});
	renderables.push_back(c0);

	//polygon
	p0 = new Polygon({{0.0f,   148.0f},
	                  {70.0f,  82.0f},
	                  {62.0f,  57.0f},
	                  {101.0f, 13.0f},
	                  {274.0f, 87.0f},
	                  {134.0f, 165.0f}});
	p0->transformation({510.0f, 150.0f});
	p0->setTexture(GETTEXTURE("repeat"));
	renderables.push_back(p0);

//	Renderer::setClearColor(0xff57513c);
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
	//sprites
	renderer->begin();

	for (const auto &r : renderables) {
//		((RectangleShape *) r)->rotate(0.5f);
		renderer->submit(r);
	}

	for (const auto &t : text) {
		renderer->submit(t);
	}

	renderer->end();
	renderer->flush();
}

void Test2D::renderImGui() {
	ImGui::Begin("Test2D", nullptr);

	//debug
	ImGui::Text("fps: %i", app.getFPS());
	ImGui::Text("tick rate: %i", app.getTPS());
	ImGui::Text("draw calls: %i", Renderer::getDC());
	ImGui::Separator();
	ImGui::Dummy({10.0f, 0.0f});

	ImGui::End();
}

void Test2D::update(float delta) {
	static const float speed = 500.0f / Config::get().tickRate;

	const vec2 pos = vec2(Mouse::getPosition(window) + vec2(camera->getPosition()));

	star->setPosition(pos);

	///update camera
	vec3 camPos = camera->getPosition();

	if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::D)) {
		camPos.x += speed * delta;
	}
	if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::A)) {
		camPos.x -= speed * delta;
	}
	if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::W)) {
		camPos.y += speed * delta;
	}
	if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::S)) {
		camPos.y -= speed * delta;
	}
	camera->setPosition(camPos);
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

		renderer->enableWireframe(enable);

		return "";
	});
}
