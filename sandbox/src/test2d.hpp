//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_TEST2D_HPP
#define X808_TEST2D_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/rectangleshape.hpp>
#include <xe/gfx/2d/batchrenderer2d.hpp>

class Test2D : public xe::Layer {
public:
	explicit Test2D();
	~Test2D() override;

	void render() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

private:
	xe::Camera *camera;
	xe::BatchRenderer2D *renderer;

	std::vector<xe::IRenderable2D *> renderables;

	xe::RectangleShape *star;

	xe::Text *text0;
	xe::Text *text1;
	xe::Text *inputText;
};


#endif //X808_TEST2D_HPP
