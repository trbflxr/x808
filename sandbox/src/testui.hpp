//
// Created by FLXR on 7/24/2018.
//

#ifndef X808_TESTUI_HPP
#define X808_TESTUI_HPP

#include <gfx/layers/layer2d.hpp>
#include <ecs/components/transform2dcomponent.hpp>
#include <ecs/systems/spriterenderersystem.hpp>
#include "orthocamerasystem.hpp"

using namespace xe;
using namespace gfx;
using namespace gfx::api;


class TestUI : public Layer2D {
private:
	friend class Test3D;

public:
	explicit TestUI();
	~TestUI() override;

	void render() override;

	void tick() override;

	void update(float delta) override;
	void fixedUpdate(float delta) override;

	void input(Event &event) override;

private:
	ECS &ecs;

	OrthoCameraSystem *cameraSystem;
	EntityHandle cameraEntity;

	SpriteRendererSystem *spriteRenderer;

	ECSSystemList mainSystems;
	ECSSystemList renderingPipeline;

	EntityHandle spriteHandle;
};


#endif //X808_TESTUI_HPP
