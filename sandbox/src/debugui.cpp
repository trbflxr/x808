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

	XE_INFO(Context::getInfo());

	//create camera
	float w = app.getConfig().width;
	float h = app.getConfig().height;

	camera = new Camera(mat4::ortho(0, w, 0, h, -1, 1000));

	renderer = new BatchRenderer2D(window.getSize().x, window.getSize().y, camera);

	const float offset = 10.0f;
	const float textOffset = 32.0f;

	const float lw = 25.0f;

	const float irw = 250.0f;
	const float irh = 110.0f;

	const float ttw = 320.0f;
	const float tth = 55.0f;

	const float spWidth = 250.0f;
	const float spHeight = 150.0f;
	const float spY = spHeight / 2.0f + offset;

	const float outline = 4.0f;

	//text
	fpsText = new Text(L"fps: ", GETFONT("default"), 0.25f);
	fpsText->setPosition({offset + offset, h - textOffset});
	fpsText->setOutlineColor(color::BLACK);
	fpsText->setOutlineThickness(outline);

	upsText = new Text(L"ups: ", GETFONT("default"), 0.25f);
	upsText->setPosition({offset + offset, fpsText->getPosition().y - lw});
	upsText->setOutlineColor(color::BLACK);
	upsText->setOutlineThickness(outline);

	frameTimeText = new Text(L"frame time: ", GETFONT("default"), 0.25f);
	frameTimeText->setPosition({offset + offset, upsText->getPosition().y - lw});
	frameTimeText->setOutlineColor(color::BLACK);
	frameTimeText->setOutlineThickness(outline);

	dcText = new Text(L"dc: ", GETFONT("default"), 0.25f);
	dcText->setPosition({offset + offset, frameTimeText->getPosition().y - lw});
	dcText->setOutlineColor(color::BLACK);
	dcText->setOutlineThickness(outline);

	infoRect = new RectangleShape({irw, irh}, 10.0f);
	infoRect->setColor(color::rgba(0, 0, 0, 0.6f));
	infoRect->setPosition({offset + irw / 2.0f, h - irh / 2.0f - offset});

	//tracked
	tePosText = new Text(L"position: ", GETFONT("default"), 0.25f);
	tePosText->setPosition({offset + offset, dcText->getPosition().y - offset * 4.0f - (offset / 2.0f)});
	tePosText->setOutlineColor(color::BLACK);
	tePosText->setOutlineThickness(outline);

	teDirText = new Text(L"direction: ", GETFONT("default"), 0.25f);
	teDirText->setPosition({offset + offset, tePosText->getPosition().y - lw});
	teDirText->setOutlineColor(color::BLACK);
	teDirText->setOutlineThickness(outline);

	teRect = new RectangleShape({ttw, tth}, 10.0f);
	teRect->setColor(color::rgba(0, 0, 0, 0.6f));
	teRect->setPosition({offset + ttw / 2.0f, infoRect->getPosition().y - irh / 2.0f - (offset * 4.0f)});

	//buffers
	sp0 = new RectangleShape({spWidth, spHeight}, 0.0f);
	sp0->setVisible(false);
	sp0->transformation({spWidth / 2.0f + offset, spY}, 180.0f);

	sp1 = new RectangleShape({spWidth, spHeight}, 0.0f);
	sp1->setVisible(false);
	sp1->transformation({sp0->getPosition().x + offset + spWidth, spY}, 180.0f);

	sp2 = new RectangleShape({spWidth, spHeight}, 0.0f);
	sp2->setVisible(false);
	sp2->transformation({sp1->getPosition().x + offset + spWidth, spY}, 180.0f);

	sp3 = new RectangleShape({spWidth, spHeight}, 0.0f);
	sp3->setVisible(false);
	sp3->transformation({sp2->getPosition().x + offset + spWidth, spY}, 180.0f);
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
		if (trackedTransform) {
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
