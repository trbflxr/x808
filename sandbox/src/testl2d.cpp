//
// Created by FLXR on 2/8/2019.
//

#include <xe/ui/imgui/imgui_impl_xe.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/texturemanager.hpp>
#include <xe/utils/random.hpp>
#include "testl2d.hpp"

using namespace xe;

TestL2D::TestL2D() {
	const float width = app.getWindowSize().x;
	const float height = app.getWindowSize().y;

	TextureParameters params;

	TextureManager::add(new Texture("0", "enemyspotted.png", params));
	TextureManager::add(new Texture("jdm", "jdm.png", params));
	TextureManager::add(new Texture("2", "test1.png", params));
	TextureManager::add(new Texture("3", "test6.png", params));
	TextureManager::add(new Texture("cosm", "cosmic.png", params));
	TextureManager::add(new Texture("star", "star.png", params));

	params.wrap = TextureWrap::Repeat;
	TextureManager::add(new Texture("bg0", "feelsconflictedman.jpg", params));
	TextureManager::add(new Texture("bg1", "sp0.png", params));


	createCamera(width, height, -1.0f, 1000.0f);
	createRenderer(width, height, true);
	setAmbientLight({0.05f, 0.05f, 0.05f});


	RectangleShape *bg = new RectangleShape({width * 4, height * 4}, 0.5f);
	bg->setTexture(GETTEXTURE("bg0"));
	bg->transformation({width * 4 / 2.0f, height * 4 / 2.0f});
	bg->setTextureRect({0.0f, 0.0f, width * 8, height * 8});
	renderables.push_back(bg);

	RectangleShape *jdm = new RectangleShape({100.0f, 100.0f}, 1.0f);
	jdm->setTexture(GETTEXTURE("star"));
	jdm->transformation({800.0f, 350.0f});
	renderables.push_back(jdm);

	box0 = new RectangleShape({100.0f, 100.0f}, 2.0f);
	box0->setTexture(GETTEXTURE("jdm"));
	box0->transformation({640.0f, 350.0f});
	renderables.push_back(box0);

	box1 = new RectangleShape({100.0f, 100.0f}, 2.0f);
	box1->setTexture(GETTEXTURE("cosm"));
	box1->transformation({340.0f, 350.0f});
	box1->setColor(color::Yellow);
	renderables.push_back(box1);


	Light2D *l0 = new Light2D("l0", {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 150.0f);
	lights.push_back(l0);

	for (int i = 1; i < 50; ++i) {
		const float x = random::nextFloat(50, 4000);
		const float y = random::nextFloat(50, 2000);

		const float r = random::nextFloat(0, 1);
		const float g = random::nextFloat(0, 1);
		const float b = random::nextFloat(0, 1);

		const float s = random::nextFloat(50, 200);

		Light2D *l = new Light2D("l" + std::to_string(i), {x, y}, {r, g, b}, s);
		lights.push_back(l);
	}

//	Light2D *l1 = new Light2D("l1", {150.0f, 150.0f}, {1, 0, 0}, 100.0f);
//	lights.push_back(l1);
//
//	Light2D *l2 = new Light2D("l2", {640.0f, 320.0f}, {0.5f, 0.5f, 0.5f}, 50.0f);
//	lights.push_back(l2);
//
//	Light2D *l3 = new Light2D("l3", {640.0f, 600.0f}, {1, 1, 0}, 100.0f);
//	lights.push_back(l3);
}

TestL2D::~TestL2D() {
	for (const auto &r : renderables) {
		delete r;
	}

	for (const auto &l : lights) {
		delete l;
	}
}

void TestL2D::renderScene() {
	vec2 pos = Mouse::getPosition(window) + vec2(getCamera()->transform.getPosition());
	lights[0]->setPosition(pos);

	for (const auto &r : renderables) {
		submit(r);
	}

	for (const auto &l : lights) {
		submit(l);
	}
}

void TestL2D::renderImGui() {
//	ImGui::Begin("Lights", nullptr);
//
//
//	ImGui::End();
}

void TestL2D::update(float delta) {
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

void TestL2D::input(xe::Event &event) { }
