//
// Created by FLXR on 2/18/2019.
//

#include "testp2d.hpp"
#include <xe/gfx/renderer.hpp>
#include <xe/resources/texturemanager.hpp>

using namespace xe;

TestP2D::TestP2D() {
	const float width = app.getWindowSize().x;
	const float height = app.getWindowSize().y;

	createCamera(width, height, -1.0f, 1000.0f);
	createRenderer(width, height);

	TextureParameters params;

	params.wrap = TextureWrap::Repeat;
	TextureManager::add(new Texture("pepe_bg", "feelsconflictedman.jpg", params));

	bg = new RectangleShape({width * 4, height * 4}, 0.5f);
	bg->setTexture(GETTEXTURE("pepe_bg"));
	bg->transformation({width * 4 / 2.0f, height * 4 / 2.0f});
	bg->setTextureRect({0.0f, 0.0f, width * 8, height * 8});
	renderables.push_back(bg);

	effect = new ParticleEffect(10, 10.0f);
	effect->setPosition({width / 2, height / 3});
	effect->generate();
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

}

void TestP2D::update(float delta) {
	effect->update(delta);
}

void TestP2D::input(xe::Event &event) {

}
