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

	createCamera(width, height, -1.0f, 1000.0f);
	createRenderer(width, height);

	TextureParameters params;

	TextureManager::add(new Texture("p0", "jdm.png", params));

	params.wrap = TextureWrap::Repeat;
	TextureManager::add(new Texture("pepe_bg", "feelsconflictedman.jpg", params));

	bg = new RectangleShape({width * 4, height * 4}, 0.5f);
	bg->setTexture(GETTEXTURE("pepe_bg"));
	bg->transformation({width * 4 / 2.0f, height * 4 / 2.0f});
	bg->setTextureRect({0.0f, 0.0f, width * 8, height * 8});
	renderables.push_back(bg);

	effect = new ParticleEffect(1.0f, 0.5f, 50, true, 10.0f);
	effect->setPosition({width / 2, height / 3});

	effect->setRotationStates({std::make_tuple(0.0f, 45.0f, 10.0f),
	                           std::make_tuple(0.5f, 90.0f, 20.0f),
	                           std::make_tuple(1.0f, -90.0f, 10.0f)});

	effect->setTranslationStates({std::make_tuple(0.0f, vec2(0.0f, 0.0f), vec2(5.0f, 10.0f)),
	                              std::make_tuple(1.0f, vec2(0.0f, 100.0f), vec2(20.0f, 50.0f))});

	effect->setSizeStates({std::make_tuple(0.0f, vec2(10.0f, 10.0f), vec2(1.0f, 1.0f)),
	                       std::make_tuple(1.0f, vec2(5.0f, 5.0f), vec2(0.5f, 0.5f))});

	effect->setColorStates({std::make_pair(0.1f, vec4(1.0f, 1.0f, 1.0f, 1.0f))});

	effect->setColorStates({std::make_pair(0.0f, vec4(1.0f, 0.1f, 0.0f, 1.0f)),
	                        std::make_pair(1.0f, vec4(1.0f, 1.0f, 0.0f, 0.95f))});


//	effect->setTexture(GETTEXTURE("p0"));

	effect->create();
}

TestP2D::~TestP2D() {
	delete effect;

	for (auto &&r : renderables) {
		delete r;
	}
}

void TestP2D::renderScene() {
	for (const auto &r : renderables) {
		submit(r);
	}

	submit(effect);
}

void TestP2D::renderImGui() {
	ImGui::Begin("Particle test");


	if (ImGui::Button("play")) {
		effect->play();
	}

	if (ImGui::Button("stop")) {
		effect->stop();
	}

	static bool looped = true;
	if (ImGui::Button("toggle loop")) {
		looped = !looped;
		effect->setLooped(looped);
	}


	ImGui::End();
}

void TestP2D::update(float delta) {
	effect->update(delta);
}

void TestP2D::input(xe::Event &event) {

}
