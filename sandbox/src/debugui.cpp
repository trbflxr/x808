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

	//create camera
	float w = app.getConfig().width / 10.0f;
	float h = app.getConfig().height / 10.0f;

	camera = new Camera(mat4::ortho(-w, w, -h, h, -1, 1000));

	renderer = new BatchRenderer2D(window.getSize().x, window.getSize().y, camera);

	const float xOffset = 3.0f;
	const float yOffset = 3.0f;

	//text
	fpsText = new Text(L"fps: ", 3, {-122, 65}, GETFONT("consolata"), color::WHITE, color::BLACK, 2);
	upsText = new Text(L"ups: ", 3, {-122, 60}, GETFONT("consolata"), color::WHITE, color::BLACK, 2);
	frameTimeText = new Text(L"frame time: ", 3, {-122, 55}, GETFONT("consolata"), color::WHITE, color::BLACK, 2);
	dcText = new Text(L"dc: ", 3, {-122, 50}, GETFONT("consolata"), color::WHITE, color::BLACK, 2);

	infoRect = new RectangleShape({45.0f, 21.0f});
	infoRect->setColor(color::rgba(0,0,0,0.5f));
	infoRect->setPosition({-w + xOffset, h - 21.0f - yOffset, 10.0f});

	//tracked
	tePosText = new Text(L"position: ", 3, {-122, 40}, GETFONT("consolata"), color::WHITE, color::BLACK, 2);
	teDirText = new Text(L"direction: ", 3, {-122, 35}, GETFONT("consolata"), color::WHITE, color::BLACK, 2);

	teRect = new RectangleShape({55.0f, 13.0f});
	teRect->setColor(color::rgba(0,0,0,0.5f));
	teRect->setPosition({-w + xOffset, h - 13.0f - 21.0f - yOffset - yOffset, 10.0f});

	//buffers
	sp0 = new RectangleShape({50, 30});
	sp0->setVisible(false);
	sp0->transformation({-125, -69, 0.0f});

	sp1 = new RectangleShape({50, 30});
	sp1->setVisible(false);
	sp1->transformation({-72, -69, 0.0f});

	sp2 = new RectangleShape({50, 30});
	sp2->setVisible(false);
	sp2->transformation({-19, -69, 0.0f});

	sp3 = new RectangleShape({50, 30});
	sp3->setVisible(false);
	sp3->transformation({34, -69, 0.0f});
}

DebugUI::~DebugUI() {
	delete camera;

	delete renderer;

	delete sp0;
	delete sp1;
	delete sp2;
	delete sp3;

	delete fpsText;
	delete upsText;
	delete frameTimeText;
	delete dcText;
	delete infoRect;

	delete tePosText;
	delete teDirText;
	delete teRect;
}

void DebugUI::render() {
	Renderer::clear(RendererBufferDepth);

	//render sprites and text
	renderer->submit(sp0);
	renderer->submit(sp1);
	renderer->submit(sp2);
	renderer->submit(sp3);

	renderer->submit(fpsText);
	renderer->submit(upsText);
	renderer->submit(frameTimeText);
	renderer->submit(dcText);

	renderer->submit(infoRect);

	if (trackedTransform) {
		renderer->submit(tePosText);
		renderer->submit(teDirText);

	}
	renderer->submit(teRect);

	renderer->renderSprites();
	renderer->renderText();

	renderer->clear();
}

void DebugUI::update(float delta) {

}

void DebugUI::lateUpdate(float delta) {
	static float s = 0.0f;
	s += delta;

	if (s >= 0.1f) {
		s = 0;
		fpsText->setString(L"fps: " + std::to_wstring(app.getFPS()));
		upsText->setString(L"ups: " + std::to_wstring(app.getUPS()));
		frameTimeText->setString(L"frame time: " + std::to_wstring(app.getFrameTime()));
		dcText->setString(L"dc: " + std::to_wstring(Renderer::getDC()));

		displayEntityInfo();
	}
}

void DebugUI::input(Event &event) {

	if (event.type == Event::KeyPressed) {
		if (event.key.code == Keyboard::Num1) {
			static bool visible = false;
			visible = !visible;
			sp0->setVisible(visible);
			event.handled = true;
		}
		if (event.key.code == Keyboard::Num2) {
			static bool visible = false;
			visible = !visible;
			sp1->setVisible(visible);
			event.handled = true;
		}
		if (event.key.code == Keyboard::Num3) {
			static bool visible = false;
			visible = !visible;
			sp2->setVisible(visible);
			event.handled = true;
		}
		if (event.key.code == Keyboard::Num4) {
			static bool visible = false;
			visible = !visible;
			sp3->setVisible(visible);
			event.handled = true;
		}
	}
}

void DebugUI::trackEntity(Transform *entityTransform) {
	trackedTransform = entityTransform;
}

void DebugUI::untrackEntity() {
	trackedTransform = nullptr;
}

void DebugUI::displayEntityInfo() {
	if (!trackedTransform) return;

	std::wstringstream ss;
	ss.precision(2);

	vec3 p = trackedTransform->getPosition();
	vec3 d = trackedTransform->getRotation().getForward();

	ss << std::fixed << L"pos: (" << p.x << ", " << p.y << ", " << p.z << ")";
	tePosText->setString(ss.str());
	ss.str(L"");

	ss << std::fixed << L"dir: (" << d.x << ", " << d.y << ", " << d.z << ")";
	teDirText->setString(ss.str());
	ss.str(L"");
}
