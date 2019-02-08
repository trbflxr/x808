//
// Created by FLXR on 2/8/2019.
//

#ifndef X808_TESTL2D_HPP
#define X808_TESTL2D_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/camera.hpp>
#include <xe/gfx/batchrenderer2d.hpp>
#include <xe/gfx/rectangleshape.hpp>

class TestL2D : public xe::Layer {
public:
	explicit TestL2D();
	~TestL2D() override;

	void render() override;
	void renderImGui() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

private:
	xe::Camera *camera;
	xe::BatchRenderer2D *renderer;

	xe::Shader *lightShader;

	xe::RectangleShape *box0;
	xe::RectangleShape *box1;

	std::vector<xe::Light2D *> lights;

	std::vector<xe::IRenderable2D *> renderables;
};


#endif //X808_TESTL2D_HPP
