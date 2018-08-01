//
// Created by FLXR on 7/24/2018.
//

#include <resources/texturemanager.hpp>
#include <gfx/renderer.hpp>
#include "debugui.hpp"

using namespace xe;
using namespace gfx;
using namespace gfx::api;

DebugUI::DebugUI() {

	FontManager::add(new Font("consolata", "assets/fonts/consolata.otf", 100));

	//render system
	spriteRenderer = new SpriteRendererSystem(renderer);
	textRenderer = new TextRendererSystem(renderer);

	renderingPipeline.addSystem(*spriteRenderer);
	renderingPipeline.addSystem(*textRenderer);

	//main systems
	cameraSystem = new OrthoCameraSystem(renderer);

	mainSystems.addSystem(*cameraSystem);

	//create camera
	CameraComponent camera(mat4::ortho(-80.0f, 80.0f, -60.0f, 60.0f, -1, 1000));
	cameraEntity = ecs.makeEntity(camera);

	TextComponent t;
	t.size = 3;
	t.font = GETFONT("consolata");
	t.textColor = color::WHITE;
	t.outlineColor = color::BLACK;
	t.outlineThickness = 2;

	t.string = L"fps: ";
	t.position = {-78, 55};
	fpsText = ecs.makeEntity(t);

	t.string = L"ups: ";
	t.position = {-78, 50};
	upsText = ecs.makeEntity(t);

	t.string = L"frame time: ";
	t.position = {-78, 45};
	frameTimeText = ecs.makeEntity(t);

	t.string = L"dc: ";
	t.position = {-78, 40};
	dcText = ecs.makeEntity(t);
}

DebugUI::~DebugUI() {
	delete spriteRenderer;
	delete textRenderer;
	delete cameraSystem;
}

void DebugUI::render() {
	Renderer::enableBlend(true);
	Renderer::setBlendFunction(BlendFunction::SOURCE_ALPHA, BlendFunction::ONE_MINUS_SOURCE_ALPHA);
	Renderer::clear(RENDERER_BUFFER_DEPTH);

	renderer->begin();

	renderer->fillRect(-80, 37, 40, 25, 2, color::rgba(0, 0, 0, 0.5f));
	ecs.updateSystems(renderingPipeline, 0.0f);

	renderer->flush();
}

void DebugUI::update(float delta) {
	ecs.updateSystems(mainSystems, delta);
}

void DebugUI::lateUpdate(float delta) {
	static TextComponent *fps = ecs.getComponent<TextComponent>(fpsText);
	static TextComponent *ups = ecs.getComponent<TextComponent>(upsText);
	static TextComponent *frameTime = ecs.getComponent<TextComponent>(frameTimeText);
	static TextComponent *dc = ecs.getComponent<TextComponent>(dcText);

	static std::wstring fpsStr;
	static std::wstring upsStr;
	static std::wstring frameTimeStr;
	static std::wstring dcStr;

	static float s = 0.0f;
	s += delta;

	if (s >= 0.1f) {
		s = 0;
		fpsStr = L"fps: " + std::to_wstring(app.getFPS());
		upsStr = L"ups: " + std::to_wstring(app.getUPS());
		frameTimeStr = L"frame time: " + std::to_wstring(app.getFrameTime());
		dcStr = L"dc: " + std::to_wstring(Renderer::getDC());

		fps->string = fpsStr.c_str();
		ups->string = upsStr.c_str();
		frameTime->string = frameTimeStr.c_str();
		dc->string = dcStr.c_str();
	}
}

void DebugUI::input(Event &event) {
	ecs.inputSystems(mainSystems, event);
}
