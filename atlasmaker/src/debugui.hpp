//
// Created by FLXR on 7/24/2018.
//

#ifndef X808_TESTUI_HPP
#define X808_TESTUI_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>
#include <xe/gfx/2d/renderer2d.hpp>

class DebugUI : public xe::Layer {
private:
	friend class Test3D;

public:
	explicit DebugUI();
	~DebugUI() override;

	void render() override;

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
	xe::Camera *camera;
	xe::Renderer2D *renderer;

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
