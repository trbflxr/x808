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
	float w = app.getConfig().width / 10.0f;
	float h = app.getConfig().height / 10.0f;

	cameraEntity = ecs.makeEntity(new CameraComponent(mat4::ortho(-w, w, -h, h, -1, 1000)));

	//text
	fpsText = ecs.makeEntity(new TextComponent(
			new Text(L"fps: ", 3, {-122, 65}, GETFONT("consolata"), color::WHITE, color::BLACK, 2)));

	upsText = ecs.makeEntity(new TextComponent(
			new Text(L"ups: ", 3, {-122, 60}, GETFONT("consolata"), color::WHITE, color::BLACK, 2)));

	frameTimeText = ecs.makeEntity(new TextComponent(
			new Text(L"frame time: ", 3, {-122, 55}, GETFONT("consolata"), color::WHITE, color::BLACK, 2)));

	dcText = ecs.makeEntity(new TextComponent(
			new Text(L"dc: ", 3, {-122, 50}, GETFONT("consolata"), color::WHITE, color::BLACK, 2)));


	sp0 = new SpriteComponent(nullptr, color::WHITE, true, false);
	sp1 = new SpriteComponent(nullptr, color::WHITE, true, false);
	sp2 = new SpriteComponent(nullptr, color::WHITE, true, false);
	sp3 = new SpriteComponent(nullptr, color::WHITE, true, false);
}

DebugUI::~DebugUI() {
	delete spriteRenderer;
	delete textRenderer;
	delete cameraSystem;

	delete sp0;
	delete sp1;
	delete sp2;
	delete sp3;
}

void DebugUI::render() {
	Renderer::clear(RendererBufferDepth);

	renderer->begin();

	renderer->fillRect(-125, 47, 45, 23, 2, color::rgba(0, 0, 0, 0.5f));
	if (trackedTransform) {
		renderer->fillRect(-125, 27, 55, 17, 2, color::rgba(0, 0, 0, 0.5f));
	}

	ecs.updateSystems(renderingPipeline, 0.0f);

	static Transform2DComponent *t0 = new Transform2DComponent(vec2(-125, -69), vec2(50, 30), 0.0f);
	static Transform2DComponent *t1 = new Transform2DComponent(vec2(-72, -69), vec2(50, 30), 0.0f);
	static Transform2DComponent *t2 = new Transform2DComponent(vec2(-19, -69), vec2(50, 30), 0.0f);
	static Transform2DComponent *t3 = new Transform2DComponent(vec2(34, -69), vec2(50, 30), 0.0f);
	renderer->submit(sp0, t0);
	renderer->submit(sp1, t1);
	renderer->submit(sp2, t2);
	renderer->submit(sp3, t3);

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

	static float s = 0.0f;
	s += delta;

	if (s >= 0.1f) {
		s = 0;
		fps->text->setString(L"fps: " + std::to_wstring(app.getFPS()));
		ups->text->setString(L"ups: " + std::to_wstring(app.getUPS()));
		frameTime->text->setString(L"frame time: " + std::to_wstring(app.getFrameTime()));
		dc->text->setString(L"dc: " + std::to_wstring(Renderer::getDC()));

		displayEntityInfo();
	}
}

void DebugUI::input(Event &event) {
	ecs.inputSystems(mainSystems, event);

	if (event.type == Event::KeyPressed) {
		if (event.key.code == Keyboard::Num1) {
			static bool visible = false;
			visible = !visible;
			sp0->visible = visible;
		}
		if (event.key.code == Keyboard::Num2) {
			static bool visible = false;
			visible = !visible;
			sp1->visible = visible;
		}
		if (event.key.code == Keyboard::Num3) {
			static bool visible = false;
			visible = !visible;
			sp2->visible = visible;
		}
		if (event.key.code == Keyboard::Num4) {
			static bool visible = false;
			visible = !visible;
			sp3->visible = visible;
		}
	}
}

void DebugUI::trackEntity(const std::wstring &name, xe::Transform *entityTransform) {
	teNameText = ecs.makeEntity(new TextComponent(
			new Text(L"name: " + name, 3, {-122, 40}, GETFONT("consolata"), color::WHITE, color::BLACK, 2)));

	tePosText = ecs.makeEntity(new TextComponent(
			new Text(L"position: ", 3, {-122, 35}, GETFONT("consolata"), color::WHITE, color::BLACK, 2)));

	teDirText = ecs.makeEntity(new TextComponent(
			new Text(L"direction: ", 3, {-122, 30}, GETFONT("consolata"), color::WHITE, color::BLACK, 2)));


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

	std::wstringstream ss;
	ss.precision(2);

	vec3 p = trackedTransform->getPosition();
	vec3 d = trackedTransform->getRotation().getForward();

	ss << std::fixed << L"pos: (" << p.x << ", " << p.y << ", " << p.z << ")";
	tePos->text->setString(ss.str());
	ss.str(L"");

	ss << std::fixed << L"dir: (" << d.x << ", " << d.y << ", " << d.z << ")";
	teDir->text->setString(ss.str());
	ss.str(L"");
}
