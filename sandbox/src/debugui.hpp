//
// Created by FLXR on 7/24/2018.
//

#ifndef X808_TESTUI_HPP
#define X808_TESTUI_HPP


#include <xe/gfx/layer2d.hpp>
#include <xe/gfx/rectangleshape.hpp>

class DebugUI : public xe::Layer2D {
private:
	friend class Test3D;

public:
	explicit DebugUI();
	~DebugUI() override;

	void renderScene() override;

	void update(float delta) override;
	void lateUpdate(float delta) override;

	void input(xe::Event &event) override;

	void trackEntity(xe::Transform *entityTransform);
	void untrackEntity();
	void displayEntityInfo();

public:
	xe::RectangleShape *sp0;
	xe::RectangleShape *sp1;
	xe::RectangleShape *sp2;
	xe::RectangleShape *sp3;

private:
	xe::Text *gpuText;
	xe::Text *fpsText;
	xe::Text *upsText;
	xe::Text *frameTimeText;
	xe::Text *dcText;
	xe::RectangleShape *infoRect;

	xe::Transform *trackedTransform;
	xe::Text *tePosText;
	xe::Text *teDirText;
	xe::RectangleShape *teRect;
};


#endif //X808_TESTUI_HPP
