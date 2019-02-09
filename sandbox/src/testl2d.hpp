//
// Created by FLXR on 2/8/2019.
//

#ifndef X808_TESTL2D_HPP
#define X808_TESTL2D_HPP


#include <xe/gfx/layer2d.hpp>
#include <xe/gfx/rectangleshape.hpp>

class TestL2D : public xe::Layer2D {
public:
	explicit TestL2D();
	~TestL2D() override;

	void renderScene() override;

	void renderImGui() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

private:
	xe::RectangleShape *box0;
	xe::RectangleShape *box1;

	std::vector<xe::Light2D *> lights;
	std::vector<xe::IRenderable2D *> renderables;
};


#endif //X808_TESTL2D_HPP
