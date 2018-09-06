//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_TEST2D_HPP
#define X808_TEST2D_HPP


#include <xe/ecs/ecs.hpp>
#include <xe/ecs/components/spritecomponent.hpp>
#include <xe/ecs/components/transform2dcomponent.hpp>
#include <xe/ecs/components/textcomponent.hpp>
#include <xe/ecs/systems/spriterenderersystem.hpp>
#include <xe/ecs/systems/textrenderersystem.hpp>
#include <xe/gfx/layer.hpp>
#include <xe/gfx/2d/primitiverenderer.hpp>

#include "orthocameramovesystem.hpp"

class Test2D : public xe::Layer {
public:
	explicit Test2D();
	~Test2D() override;

	void render() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

private:
	xe::SpriteRenderer *spriteRenderer;
	xe::PrimitiveRenderer *primitiveRenderer;
	xe::TextRenderer* textRenderer;

	xe::ECS ecs;

	OrthoCameraMoveSystem *cameraSystem;
	xe::EntityHandle cameraEntity;

	xe::SpriteRendererSystem *spriteRendererSystem;
	xe::TextRendererSystem *textRendererSystem;

	xe::ECSSystemList mainSystems;
	xe::ECSSystemList spriteRenderingPipeline;
	xe::ECSSystemList textRenderingPipeline;

	xe::EntityHandle text;
	xe::EntityHandle inputText;
	xe::EntityHandle a;
};


#endif //X808_TEST2D_HPP
