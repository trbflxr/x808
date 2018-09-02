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
#include <xe/gfx/deferredrenderer.hpp>
#include "debugui.hpp"
#include "dummyplayercontrolsystem.hpp"

class Test3D : public xe::Layer {
public:
	explicit Test3D(DebugUI *ui);
	~Test3D();

	void render() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

private:
	DebugUI *ui;

	xe::ECS ecs;
	xe::ECSSystemList mainSystems;
	xe::ECSSystemList renderingPipeline;

	xe::Camera *camera;

	DummyPlayerControlSystem *playerControlSystem;
	xe::EntityHandle playerEntity;

	xe::Scene *scene;

	xe::DeferredRenderer *renderer;

	bool light = false;
};


#endif //X808_TEST3DDEFERRED_HPP
