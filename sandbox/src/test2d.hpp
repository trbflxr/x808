//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_TEST_HPP
#define X808_TEST_HPP


#include <gfx/layers/layer2d.hpp>

class Test2D : public xe::gfx::Layer2D {
public:
	explicit Test2D();
	~Test2D() override;

	void init(xe::gfx::Renderer2D &renderer) override;

	void tick() override;
	void onEvent(xe::Event &event) override;

	bool onKeyPressedEvent(xe::KeyPressEvent &event);
	bool onMousePressedEvent(xe::MousePressEvent &event);
	bool onMouseMovedEvent(xe::MouseMoveEvent &event);

private:
	xe::gfx::Renderer2D *renderer;
};


#endif //X808_TEST_HPP
