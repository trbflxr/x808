//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_TEST2D_HPP
#define X808_TEST2D_HPP


#include <xe/gfx/layer2d.hpp>
#include <xe/gfx/rectangleshape.hpp>

class Test2D : public xe::Layer2D {
public:
	explicit Test2D();
	~Test2D() override;

	void renderScene() override;

	void renderImGui() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

private:
	void addShellCommands();

private:
	xe::RectangleShape *star;
	xe::Text *inputText;

	std::vector<xe::IRenderable2D *> renderables;
	std::vector<xe::Text *> text;
};


#endif //X808_TEST2D_HPP
