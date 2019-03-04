//
// Created by FLXR on 3/1/2019.
//

#ifndef X808_TEST3D_HPP
#define X808_TEST3D_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/camera.hpp>
#include <xe/gfx/model.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/gbuffer.hpp>
#include "dummyplayer.hpp"

#include <xe/gfx/uniformbuffer.hpp>
#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/quad.hpp>
#include <xe/gfx/finalfx.hpp>

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

	std::vector<xe::Model *> models;
	std::vector<xe::Light *> lights;
	xe::Model *model;
	xe::Material *material;
	xe::Material *material1;
	xe::SpotLight *sl;
	xe::PointLight *pl;

	xe::UniformBuffer *cameraUBO;

	xe::GBuffer *gBuffer;
	xe::FinalFX *final;
	xe::Quad *quad;
};


#endif //X808_TEST3D_HPP
