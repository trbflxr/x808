//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_TESTECS_HPP
#define X808_TESTECS_HPP


#include <ecs/ecs.hpp>
#include <ecs/components/spritecomponent.hpp>
#include <ecs/components/transform2dcomponent.hpp>
#include <ecs/components/textcomponent.hpp>
#include <ecs/systems/spriterenderersystem.hpp>
#include <ecs/systems/textrenderersystem.hpp>
#include <gfx/layers/layer2d.hpp>
#include "orthocameramovesystem.hpp"

class TestECS : public xe::gfx::Layer2D {
public:
	explicit TestECS();
	~TestECS() override;

	void render() override;

	void tick() override;

	void update(float delta) override;
	void fixedUpdate(float delta) override;

	void input(xe::Event &event) override;

private:
	xe::ECS &ecs;

	OrthoCameraMoveSystem *cameraSystem;
	xe::EntityHandle cameraEntity;

	xe::SpriteRendererSystem *spriteRenderer;
	xe::TextRendererSystem *textRenderer;

	xe::ECSSystemList mainSystems;
	xe::ECSSystemList renderingPipeline;

	xe::EntityHandle text;
	xe::EntityHandle inputText;
	xe::EntityHandle a;

	std::wstring inputString;
};


#endif //X808_TESTECS_HPP
