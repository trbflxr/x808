//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_TEST2D_HPP
#define X808_TEST2D_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/textureatlas.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>
#include <xe/gfx/2d/circleshape.hpp>
#include <xe/gfx/2d/polygon.hpp>
#include <xe/gfx/2d/renderer2d.hpp>

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
	xe::Renderer2D *renderer;

	xe::CircleShape *c0;
	xe::Polygon *p0;
	xe::RectangleShape *star;
	xe::Text *inputText;

	std::vector<xe::IRenderable2D *> renderables;
	std::vector<xe::Text *> text;
};


#endif //X808_TEST2D_HPP
