//
// Created by FLXR on 2/18/2019.
//

#include "testp2d.hpp"
#include <xe/gfx/renderer.hpp>
#include <xe/resources/texturemanager.hpp>
#include <xe/ui/imgui/imgui.h>

using namespace xe;

TestP2D::TestP2D() {
	const float width = app.getWindowSize().x;
	const float height = app.getWindowSize().y;

	camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1000.0f));
	renderer = new Renderer2D(width, height, camera);

	TextureParameters params;

	TextureManager::add(new Texture("p0", "jdm.png", params));
	TextureManager::add(new Texture("p1", "star.png", params));

	params.wrap = TextureWrap::Repeat;
	TextureManager::add(new Texture("pepe_bg", "feelsconflictedman.jpg", params));

	bg = new RectangleShape({width * 4, height * 4});
	bg->setTexture(GETTEXTURE("pepe_bg"));
	bg->transformation({width * 4 / 2.0f, height * 4 / 2.0f});
	bg->setTextureRect({0.0f, 0.0f, width * 8, height * 8});

	s0 = new RectangleShape({200, 200});
	s0->setPosition({300, 200});
	s0->setTexture(GETTEXTURE("p0"));

	s1 = new RectangleShape({200, 200});
	s1->setPosition({300, 200});
	s1->setTexture(GETTEXTURE("p1"));

	renderables.push_back(bg);
	renderables.push_back(s0);
	renderables.push_back(s1);


	Text *t0 = new Text("text0", GETFONT("default"), 0.5f);
	t0->setPosition({50, 300});
	t0->setOutlineThickness(4.0f);
	t0->setTextColor(color::White);
	t0->setOutlineColor(color::Black);

	Text *t1 = new Text("text1", GETFONT("default"), 0.5f);
	t1->setPosition({50, 400});
	t1->setOutlineThickness(4.0f);
	t1->setTextColor(color::White);
	t1->setOutlineColor(color::Black);

	text.push_back(t0);
	text.push_back(t1);

//	effect = new ParticleEffect(1.0f, 0.5f, 50, true);
//	effect->setPosition({width / 2, height / 3});
//
//	effect->setRotationStates({std::make_tuple(0.0f, 45.0f, 10.0f),
//	                           std::make_tuple(0.5f, 90.0f, 20.0f),
//	                           std::make_tuple(1.0f, -90.0f, 10.0f)});
//
//	effect->setTranslationStates({std::make_tuple(0.0f, vec2(0.0f, 0.0f), vec2(5.0f, 10.0f)),
//	                              std::make_tuple(1.0f, vec2(0.0f, 100.0f), vec2(20.0f, 50.0f))});
//
//	effect->setSizeStates({std::make_tuple(0.0f, vec2(10.0f, 10.0f), vec2(1.0f, 1.0f)),
//	                       std::make_tuple(1.0f, vec2(5.0f, 5.0f), vec2(0.5f, 0.5f))});
//
//	effect->setColorStates({std::make_tuple(0.0f, vec4(1.0f, 0.1f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f)),
//	                        std::make_tuple(1.0f, vec4(1.0f, 0.8f, 0.0f, 0.95f), vec4(0.0f, 0.2f, 0.0f, 0.0f))});


//	effect->setTexture(GETTEXTURE("p0"));

//	effect->create();
}

TestP2D::~TestP2D() {
//	delete effect;

	delete camera;
	delete renderer;

	for (auto &&r : renderables) {
		delete r;
	}

	for (auto &&t : text) {
		delete t;
	}
}

void TestP2D::render() {
	renderer->begin();

	for (auto &&r : renderables) {
		renderer->submit(r);
	}

	for (auto &&t : text) {
		renderer->submit(t);
	}

	renderer->end();
	renderer->flush();
}

void TestP2D::renderImGui() {
//	ImGui::Begin("Particle test");
//
//
//	if (ImGui::Button("play")) {
//		effect->play();
//	}
//
//	if (ImGui::Button("stop")) {
//		effect->stop();
//	}
//
//	static bool looped = true;
//	if (ImGui::Button("toggle loop")) {
//		looped = !looped;
//		effect->setLooped(looped);
//	}
//
//
//	ImGui::End();
}

void TestP2D::update(float delta) {
//	effect->update(delta);
}

void TestP2D::input(xe::Event &event) {

}
