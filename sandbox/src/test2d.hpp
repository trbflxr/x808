//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_TEST2D_HPP
#define X808_TEST2D_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/rectangleshape.hpp>
#include <xe/gfx/batchrenderer2d.hpp>

class Test2D : public xe::Layer {
public:
	explicit Test2D();
	~Test2D() override;

	void render() override;

	void renderImGui() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

private:
	void addShellCommands();

private:
	xe::Camera *camera;
	xe::BatchRenderer2D *renderer;

	std::vector<xe::IRenderable2D *> renderables;
	xe::RectangleShape *star;

	std::vector<xe::Text *> text;
	xe::Text *inputText;
};


#endif //X808_TEST2D_HPP
