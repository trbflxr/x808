//
// Created by FLXR on 2/18/2019.
//

#ifndef X808_TESTP2D_HPP
#define X808_TESTP2D_HPP


#include <xe/gfx/layer2d.hpp>

class TestP2D : public xe::Layer2D {
public:
	explicit TestP2D();
	~TestP2D() override;

	void renderScene() override;

	void renderImGui() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

private:
	xe::ParticleEffect *effect;

	xe::RectangleShape *bg;
	std::vector<xe::IRenderable2D *> renderables;
};


#endif //X808_TESTP2D_HPP
