//
// Created by FLXR on 8/4/2018.
//

#ifndef X808_TEST3DDEFERRED_HPP
#define X808_TEST3DDEFERRED_HPP


#include <xe/gfx/layers/layer.hpp>
#include <xe/gfx/scene.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/fx/gbuffer.hpp>
#include <xe/gfx/fx/final.hpp>
#include <xe/gfx/fx/hdr.hpp>
#include <xe/gfx/fx/quad.hpp>
#include <xe/gfx/uniformbuffer.hpp>
#include "debugui.hpp"
#include "dummyplayercontrolsystem.hpp"

class Test3D : public xe::Layer {
public:
	explicit Test3D(DebugUI *ui);
	~Test3D();

	void render() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

	void updateUBO(const xe::mat4 &view, const xe::mat4 &perspective, const xe::vec3 &pos, const xe::vec3 &look);

private:
	xe::fx::GBuffer *gBuffer;
	xe::fx::Quad *quad;
	xe::fx::Final *final;
	xe::fx::HDR *hdr;

	DebugUI *ui;

	xe::ECS ecs;
	xe::ECSSystemList mainSystems;
	xe::ECSSystemList renderingPipeline;

	xe::Camera *camera;

	xe::UniformBuffer *cameraUBO;

	DummyPlayerControlSystem *playerControlSystem;
	xe::EntityHandle playerEntity;

	xe::Scene *scene;

	bool light = false;
};


#endif //X808_TEST3DDEFERRED_HPP
