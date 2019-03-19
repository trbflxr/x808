//
// Created by FLXR on 3/1/2019.
//

#ifndef X808_TEST3D_HPP
#define X808_TEST3D_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/camera.hpp>
#include <xe/gfx/model.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/deferredrenderer.hpp>
#include "dummyplayer.hpp"


class Test3D : public xe::Layer {
public:
	explicit Test3D();
	~Test3D() override;

	void render() override;
	void renderImGui() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

private:
	DummyPlayer *player;
	xe::Camera *camera;

	//test
	bool hook = false;
	bool hook2 = false;
	bool rock = false;
	bool dlr = false;

	xe::Scene *scene;

	xe::Model *model;

	xe::Material *material;
	xe::Material *material1;
	xe::Material *parallax;
	xe::Material *disp;
	xe::Material *bricks;
	xe::Material *pebble;

	xe::SpotLight *sl;
	xe::PointLight *pl;
	xe::DirectionalLight *dl;

	xe::DeferredRenderer *renderer;
};


#endif //X808_TEST3D_HPP
