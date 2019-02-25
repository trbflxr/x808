//
// Created by FLXR on 2/18/2019.
//

#ifndef X808_TESTP2D_HPP
#define X808_TESTP2D_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>
#include <xe/gfx/particles/particleeffect.hpp>

class TestP2D : public xe::Layer {
public:
	explicit TestP2D();
	~TestP2D() override;

	void render() override;

	void renderImGui() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

private:
	xe::Camera *camera;
	xe::Renderer2D *renderer;

	xe::ParticleEffect *effect;

	xe::RectangleShape *bg;
	std::vector<xe::IRenderable2D *> renderables;
};


#endif //X808_TESTP2D_HPP
