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

	atlas = new TextureAtlas("test_atlas", "test.atlas", params);

	TextureManager::add(new Texture("p0", "jdm.png", params));
	TextureManager::add(new Texture("p1", "star.png", params));

	params.wrap = TextureWrap::Repeat;
	TextureManager::add(new Texture("pepe_bg", "feelsconflictedman.jpg", params));

	bg = new RectangleShape({width * 4, height * 4});
	bg->setTexture(GETTEXTURE("pepe_bg"));
	bg->setTextureRect({0.0f, 0.0f, width * 8, height * 8});
	bg->transformation({width * 4 / 2.0f, height * 4 / 2.0f});

	renderables.push_back(bg);

	RectangleShape *r = new RectangleShape({100, 100});
	r->setPosition({200, 100});
	r->setTexture(atlas->getTexture());
	r->setTextureRect(atlas->getArea("test1.png"));
	renderables.push_back(r);

	dummy = new RectangleShape({100, 100});
	dummy->setPosition({500, height});
	dummy->setTexture(atlas->getTexture());
	dummy->setTextureRect(atlas->getArea("test1.png"));
	renderables.push_back(dummy);

	effect = new ParticleEffect(1.0f, 0.5f, 100, true);
	effect->setPosition({width / 2, height / 3});

	effect->setRotationStates({std::make_tuple(0.0f, 45.0f, 10.0f),
	                           std::make_tuple(0.5f, 90.0f, 20.0f),
	                           std::make_tuple(1.0f, -90.0f, 10.0f)});

	effect->setTranslationStates({std::make_tuple(0.0f, vec2(0.0f, 0.0f), vec2(5.0f, 10.0f)),
	                              std::make_tuple(1.0f, vec2(0.0f, 100.0f), vec2(20.0f, 50.0f))});

	effect->setSizeStates({std::make_tuple(0.0f, vec2(10.0f, 10.0f), vec2(1.0f, 1.0f)),
	                       std::make_tuple(1.0f, vec2(5.0f, 5.0f), vec2(0.5f, 0.5f))});

	effect->setColorStates({std::make_tuple(0.0f, vec4(1.0f, 0.1f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f)),
	                        std::make_tuple(1.0f, vec4(1.0f, 0.8f, 0.0f, 0.95f), vec4(0.0f, 0.2f, 0.0f, 0.0f))});


//	effect->setTexture(atlas->getTexture());
//	effect->setTextureRect(atlas->getArea("test1.png"));

	effect->create();

	t.reset();
}

TestP2D::~TestP2D() {
	delete atlas;

	delete effect;

	delete camera;
	delete renderer;

	for (auto &&r : renderables) {
		delete r;
	}
}

void TestP2D::render() {
	renderer->begin();

	for (auto &&r : renderables) {
		renderer->submit(r);
	}

	effect->render(renderer);

	renderer->end();
	renderer->flush();
}

void TestP2D::renderImGui() {
	ImGui::Begin("Particle test");

	ImGui::Text("fps: %i", app.getFPS());
	ImGui::Text("tps: %i", app.getTPS());
	ImGui::Text("draw calls: %i", Renderer::getDC());
	ImGui::Separator();
	ImGui::Dummy({10.0f, 0.0f});

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

	if (ImGui::Button("dummy")) {
		dummy->setPosition({500, app.getWindowSize().y});
	}

	ImGui::End();
}

void TestP2D::update(float delta) {
	static const float speed = 5.0f / Config::get().tickRate;

	effect->update();

	dummy->move({0.0f, y * delta});

	if (Keyboard::isKeyPressed(Keyboard::Key::Q)) {
		bg->rotate(-speed * delta);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
		bg->rotate(speed * delta);
	}
}

void TestP2D::fixedUpdate(float delta) {
	effect->fixedUpdate(delta);
	y = -500.0f * delta;

	if (dummy->getPosition().y < 0) {
		dummy->setPosition({500, app.getWindowSize().y});
		XE_CORE_TRACE(t.elapsed());
		t.reset();
	}
}

void TestP2D::input(xe::Event &event) {

}
