//
// Created by FLXR on 8/4/2018.
//

#ifndef X808_TEST3DDEFERRED_HPP
#define X808_TEST3DDEFERRED_HPP


#include <xe/gfx/layers/layer.hpp>
#include <xe/gfx/scene.hpp>
#include <xe/gfx/shader.hpp>
#include "debugui.hpp"
#include "dummyplayercontrolsystem.hpp"

class Test3D : public xe::Layer {
public:
	explicit Test3D(DebugUI* ui);
	~Test3D();

	void render() override;

	void update(float delta) override;
	void fixedUpdate(float delta) override;

	void input(xe::Event &event) override;

private:
	DebugUI *ui;

	xe::ECS ecs;
	xe::ECSSystemList mainSystems;
	xe::ECSSystemList renderingPipeline;

	xe::Camera *camera;

	DummyPlayerControlSystem *playerControlSystem;
	xe::EntityHandle player;

	xe::Scene *scene;

	xe::Shader* dummyShader;
};


#endif //X808_TEST3DDEFERRED_HPP
