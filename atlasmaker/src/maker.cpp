//
// Created by FLXR on 2/25/2019.
//

#include "maker.hpp"

namespace xe {


	Maker::Maker() {
		const float width = app.getWindowSize().x;
		const float height = app.getWindowSize().y;

		camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1000.0f));
		renderer = new Renderer2D(width, height, camera);

		TextureParameters params;

		texture = new Texture("test1", "test1.png", params);

		Sprite *s0 = new Sprite(texture);
		s0->setPosition({100, 100});
		sprites.emplace("s0", s0);
	}

	Maker::~Maker() {
		delete camera;
		delete renderer;

		for (auto &&s : sprites) {
			delete s.second;
		}

		delete texture;
	}

	void Maker::render() {
		renderer->begin();

		for (auto &&s : sprites) {
			renderer->submit(s.second);
		}

		renderer->end();
		renderer->flush();
	}

	void Maker::renderImGui() {

	}

	void Maker::update(float delta) {

	}

	void Maker::input(Event &event) {

	}

}