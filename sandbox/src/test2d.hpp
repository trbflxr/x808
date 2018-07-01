//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_TEST_HPP
#define X808_TEST_HPP


#include <gfx/layers/layer.hpp>
#include <gfx/api/texture2d.hpp>
#include <gfx/renderer2d.hpp>
#include <core/gameobject.hpp>
#include <gfx/api/basicshader.hpp>

class Test2D : public xe::gfx::Layer {
public:
	explicit Test2D();
	~Test2D() override;

	void init() override;
	void render() override;
	void update(const xe::TimeStep &ts) override;
	void tick() override;

	void onEvent(xe::Event &event) override;

	bool onKeyPressedEvent(xe::KeyPressEvent &event);
	bool onMousePressedEvent(xe::MousePressEvent &event);
	bool onMouseMovedEvent(xe::MouseMoveEvent &event);

private:
	xe::gfx::Renderer2D *renderer;
	xe::gfx::api::BasicShader *shader;

	xe::GameObject *root;

};


#endif //X808_TEST_HPP
