//
// Created by FLXR on 7/8/2018.
//

#include <application/application.hpp>
#include <gfx/renderer.hpp>
#include <gfx/sprite.hpp>
#include <resources/texturemanager.hpp>
#include <ctime>
#include "testecs.hpp"

using namespace xe;
using namespace gfx;
using namespace gfx::api;


TestECS::TestECS() :
		Layer2D(math::ortho(-80.0f, 80.0f, -60.0f, 60.0f, -1, 1000)) {

	srand((uint) time(nullptr));

	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	TextureParameters params(TextureFilter::NEAREST);

	TextureManager::add(Texture2D::create("0", "assets/textures/test1.png", params));
	TextureManager::add(Texture2D::create("1", "assets/textures/test2.png", params));
	TextureManager::add(Texture2D::create("2", "assets/textures/test3.png", params));
	TextureManager::add(Texture2D::create("3", "assets/textures/test4.png", params));
	TextureManager::add(Texture2D::create("4", "assets/textures/test5.png", params));
	TextureManager::add(Texture2D::create("5", "assets/textures/test6.png", params));
	TextureManager::add(Texture2D::create("6", "assets/textures/test7.png", params));
	TextureManager::add(Texture2D::create("7", "assets/textures/test8.png", params));

	TextureManager::add(Texture2D::create("8", "assets/textures/test1.png", params));
	TextureManager::add(Texture2D::create("9", "assets/textures/test2.png", params));
	TextureManager::add(Texture2D::create("10", "assets/textures/test3.png", params));
	TextureManager::add(Texture2D::create("11", "assets/textures/test4.png", params));
	TextureManager::add(Texture2D::create("12", "assets/textures/test5.png", params));
	TextureManager::add(Texture2D::create("13", "assets/textures/test6.png", params));
	TextureManager::add(Texture2D::create("14", "assets/textures/test7.png", params));
	TextureManager::add(Texture2D::create("15", "assets/textures/test8.png", params));

	TextureManager::add(Texture2D::create("16", "assets/textures/test1.png", params));
	TextureManager::add(Texture2D::create("17", "assets/textures/test2.png", params));
	TextureManager::add(Texture2D::create("18", "assets/textures/test3.png", params));
	TextureManager::add(Texture2D::create("19", "assets/textures/test4.png", params));
	TextureManager::add(Texture2D::create("20", "assets/textures/test5.png", params));
	TextureManager::add(Texture2D::create("21", "assets/textures/test6.png", params));
	TextureManager::add(Texture2D::create("22", "assets/textures/test7.png", params));
	TextureManager::add(Texture2D::create("23", "assets/textures/test8.png", params));

	TextureManager::add(Texture2D::create("24", "assets/textures/test1.png", params));
	TextureManager::add(Texture2D::create("25", "assets/textures/test2.png", params));
	TextureManager::add(Texture2D::create("26", "assets/textures/test3.png", params));
	TextureManager::add(Texture2D::create("27", "assets/textures/test4.png", params));
	TextureManager::add(Texture2D::create("28", "assets/textures/test5.png", params));
	TextureManager::add(Texture2D::create("29", "assets/textures/test6.png", params));
	TextureManager::add(Texture2D::create("30", "assets/textures/test7.png", params));
	TextureManager::add(Texture2D::create("31", "assets/textures/test8.png", params));

	TextureManager::add(Texture2D::create("32", "assets/textures/enemyspotted.png", params));
	TextureManager::add(Texture2D::create("33", "assets/textures/enemyspotted.png", params));
	TextureManager::add(Texture2D::create("34", "assets/textures/enemyspotted.png", params));
	TextureManager::add(Texture2D::create("35", "assets/textures/test4.png", params));
	TextureManager::add(Texture2D::create("36", "assets/textures/test5.png", params));
	TextureManager::add(Texture2D::create("37", "assets/textures/test6.png", params));
	TextureManager::add(Texture2D::create("38", "assets/textures/test7.png", params));
	TextureManager::add(Texture2D::create("39", "assets/textures/test8.png", params));

	/// 1 - 1.2k
	/// 2 - 11k
	/// 3 - 59k
	uint texCount = 40;
//	uint texCount = 31;

	Renderable2DComponent r2dc;

#define sp_size  2

	//59k
#if sp_size == 3
	for (float x = -80; x < 80; x += 0.57f) {
		for (float y = -60; y < 60; y += 0.57f) {
			add(new Sprite({x, y}, 0, {0.49f, 0.49f}, 0, &GETTEXTURE(std::to_string(rand() % texCount))));

			r2dc.renderable = renderables.back();
			ecs.makeEntity(r2dc);
		}
	}
#elif sp_size == 2
	for (float x = -80; x < 80; x += 1.3f) {
		for (float y = -60; y < 60; y += 1.3f) {
			add(new Sprite({x, y}, 0, {0.9f, 0.9f}, 0, &GETTEXTURE(std::to_string(rand() % texCount))));

			r2dc.renderable = renderables.back();
			ecs.makeEntity(r2dc);
		}
	}
#elif sp_size == 1
	for (int32 x = -80; x < 80; x += 4) {
		for (int32 y = -60; y < 60; y += 4) {
			add(new Sprite({(float) x, (float) y}, 0, {3, 3}, 0,
						   &GETTEXTURE(std::to_string(rand() % texCount))));

			r2dc.renderable = renderables.back();
			ecs.makeEntity(r2dc);
		}
	}
#endif

	XE_INFO("size: ", renderables.size());


	r2ds = new Renderable2DSystem(renderer);

	renderingPipeline.addSystem(*r2ds);
}

TestECS::~TestECS() {
	delete r2ds;
}

void TestECS::render() {
	renderer->begin();

	ecs.updateSystems(renderingPipeline, 0.0f);
	renderer->drawLine(-20, -20, 200, 200, 1, color::GREEN, 2);

	renderer->flush();
}

void TestECS::update(const xe::TimeStep &ts) {
	ecs.updateSystems(mainSystems, ts.getSeconds());
}

void TestECS::tick() {
	xe::Application &app = xe::Application::getApplication();

	char buff[1024];
	sprintf(buff, "fps: %u | ups: %u | frame time: %f ms | DC: %u",
	        app.getFPS(), app.getUPS(), app.getFrameTime(), Renderer::getDC());

	app.getWindow().setTitle(buff);
}

void TestECS::onEvent(xe::Event &event) {
	xe::EventDispatcher dispatcher(event);
	dispatcher.dispatch<xe::KeyPressEvent>(METHOD(&TestECS::onKeyPressedEvent));
	dispatcher.dispatch<xe::MousePressEvent>(METHOD(&TestECS::onMousePressedEvent));
	dispatcher.dispatch<xe::MouseMoveEvent>(METHOD(&TestECS::onMouseMovedEvent));
}

bool TestECS::onKeyPressedEvent(xe::KeyPressEvent &event) {
	return false;
}

bool TestECS::onMousePressedEvent(xe::MousePressEvent &event) {
	return false;
}

bool TestECS::onMouseMovedEvent(xe::MouseMoveEvent &event) {
	return false;
}
