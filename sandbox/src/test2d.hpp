//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_TESTECS_HPP
#define X808_TESTECS_HPP


#include <xe/ecs/ecs.hpp>
#include <xe/ecs/components/spritecomponent.hpp>
#include <xe/ecs/components/transform2dcomponent.hpp>
#include <xe/ecs/components/textcomponent.hpp>
#include <xe/ecs/systems/spriterenderersystem.hpp>
#include <xe/ecs/systems/textrenderersystem.hpp>
#include <xe/gfx/layers/layer2d.hpp>

#include "orthocameramovesystem.hpp"

class Test2D : public xe::Layer2D {
public:
	explicit Test2D();
	~Test2D() override;

	void render() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

private:
	xe::ECS ecs;

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
