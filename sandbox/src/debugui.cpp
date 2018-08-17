//
// Created by FLXR on 7/24/2018.
//

#include <sstream>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/texturemanager.hpp>
#include "debugui.hpp"

using namespace xe;

DebugUI::DebugUI() :
		trackedTransform(nullptr) {

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

	defaultTC.size = 3;
	defaultTC.font = GETFONT("consolata");
	defaultTC.textColor = color::WHITE;
	defaultTC.outlineColor = color::BLACK;
	defaultTC.outlineThickness = 2;

	defaultTC.string = L"fps: ";
	defaultTC.position = {-78, 55};
	fpsText = ecs.makeEntity(defaultTC);

	defaultTC.string = L"ups: ";
	defaultTC.position = {-78, 50};
	upsText = ecs.makeEntity(defaultTC);

	defaultTC.string = L"frame time: ";
	defaultTC.position = {-78, 45};
	frameTimeText = ecs.makeEntity(defaultTC);

	defaultTC.string = L"dc: ";
	defaultTC.position = {-78, 40};
	dcText = ecs.makeEntity(defaultTC);
}

DebugUI::~DebugUI() {
	delete spriteRenderer;
	delete textRenderer;
	delete cameraSystem;
}

void DebugUI::render() {
	Renderer::clear(RendererBufferDepth);

	renderer->begin();

	renderer->fillRect(-80, 37, 40, 25, 2, color::rgba(0, 0, 0, 0.5f));
	if (trackedTransform) {
		renderer->fillRect(-80, 17, 55, 17, 2, color::rgba(0, 0, 0, 0.5f));
	}

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

		displayEntityInfo();
	}
}

void DebugUI::input(Event &event) {
	ecs.inputSystems(mainSystems, event);
}

void DebugUI::trackEntity(const std::wstring_view &name, xe::Transform *entityTransform) {
	defaultTC.string = name.data();
	defaultTC.position = {-78, 30};
	teNameText = ecs.makeEntity(defaultTC);

	defaultTC.string = L"position: ";
	defaultTC.position = {-78, 25};
	tePosText = ecs.makeEntity(defaultTC);

	defaultTC.string = L"direction: ";
	defaultTC.position = {-78, 20};
	teDirText = ecs.makeEntity(defaultTC);

	trackedTransform = entityTransform;
}

void DebugUI::untrackEntity() {
	trackedTransform = nullptr;

	ecs.removeEntity(teNameText);
	ecs.removeEntity(tePosText);
	ecs.removeEntity(teDirText);

	teNameText = nullptr;
	tePosText = nullptr;
	teDirText = nullptr;
}

void DebugUI::displayEntityInfo() {
	if (!trackedTransform) return;
	static TextComponent *tePos = ecs.getComponent<TextComponent>(tePosText);
	static TextComponent *teDir = ecs.getComponent<TextComponent>(teDirText);

	static std::wstringstream ss;
	static std::wstring pos;
	static std::wstring dir;

	ss.precision(2);

	vec3 p = trackedTransform->getTranslation();
	vec3 d = trackedTransform->getRotation().getForward();

	ss << std::fixed << L"pos: (" << p.x << ", " << p.y << ", " << p.z << ")";
	pos = ss.str();
	ss.str(L"");

	ss << std::fixed << L"dir: (" << d.x << ", " << d.y << ", " << d.z << ")";
	dir = ss.str();
	ss.str(L"");

	tePos->string = pos.c_str();
	teDir->string = dir.c_str();
}
