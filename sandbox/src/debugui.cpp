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

	camera = new Camera(mat4::ortho(0, w, 0, h, -1, 1000));

	renderer = new BatchRenderer2D(window.getSize().x, window.getSize().y, camera);

	const float xOffset = 1.5f;
	const float yOffset = 1.5f;

	const float lw = 2.5f;
	const float lxo = 1.0f;

	const float irw = 22.0f;
	const float irh = 10.0f;

	const float ttw = 27.0f;
	const float tth = 6.0f;

	//text
	fpsText = new Text(L"fps: ", 1.5f, {xOffset + lxo, h - yOffset / lw - lw},
	                   GETFONT("consolata"), color::WHITE, color::BLACK, 2);

	upsText = new Text(L"ups: ", 1.5f, {xOffset + lxo, fpsText->getPosition().y - lw},
	                   GETFONT("consolata"), color::WHITE, color::BLACK, 2);

	frameTimeText = new Text(L"frame time: ", 1.5f, {xOffset + lxo, upsText->getPosition().y - lw},
	                         GETFONT("consolata"), color::WHITE, color::BLACK, 2);

	dcText = new Text(L"dc: ", 1.5f, {xOffset + lxo, frameTimeText->getPosition().y - lw},
	                  GETFONT("consolata"), color::WHITE, color::BLACK, 2);

	infoRect = new RectangleShape({irw, irh}, 10.0f);
	infoRect->setColor(color::rgba(0, 0, 0, 0.5f));
	infoRect->setPosition({xOffset + irw / 2.0f, h - irh / 2.0f - yOffset});

	//tracked
	tePosText = new Text(L"position: ", 1.5f, {xOffset + lxo, dcText->getPosition().y - yOffset * 1.5f - yOffset},
	                     GETFONT("consolata"), color::WHITE, color::BLACK, 2);

	teDirText = new Text(L"direction: ", 1.5f, {xOffset + lxo, tePosText->getPosition().y - lw},
	                     GETFONT("consolata"), color::WHITE, color::BLACK, 2);

	teRect = new RectangleShape({ttw, tth}, 10.0f);
	teRect->setColor(color::rgba(0, 0, 0, 0.5f));
	teRect->setPosition({xOffset + ttw / 2.0f, infoRect->getPosition().y - tth * yOffset});

	//buffers
	sp0 = new RectangleShape({50, 30}, 0.0f);
	sp0->setVisible(false);
	sp0->transformation({-125, -69});

	sp1 = new RectangleShape({50, 30}, 0.0f);
	sp1->setVisible(false);
	sp1->transformation({-72, -69});

	sp2 = new RectangleShape({50, 30}, 0.0f);
	sp2->setVisible(false);
	sp2->transformation({-19, -69});

	sp3 = new RectangleShape({50, 30}, 0.0f);
	sp3->setVisible(false);
	sp3->transformation({34, -69});
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
		renderer->submit(teRect);
	}


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
