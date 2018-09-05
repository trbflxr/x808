//
// Created by FLXR on 7/24/2018.
//

#ifndef X808_TESTUI_HPP
#define X808_TESTUI_HPP


#include <xe/ecs/ecs.hpp>
#include <xe/ecs/components/transform2dcomponent.hpp>
#include <xe/ecs/systems/spriterenderersystem.hpp>
#include <xe/ecs/systems/textrenderersystem.hpp>
#include <xe/gfx/layer.hpp>
#include "orthocamerasystem.hpp"

class DebugUI : public xe::Layer {
private:
	friend class Test3D;

public:
	explicit DebugUI();
	~DebugUI() override;

	void render() override;

	void update(float delta) override;
	void lateUpdate(float delta) override;

	void input(xe::Event &event) override;

	void trackEntity(const std::wstring &name, xe::Transform *entityTransform);
	void untrackEntity();
	void displayEntityInfo();

public:
	xe::SpriteComponent *sp0;
	xe::SpriteComponent *sp1;
	xe::SpriteComponent *sp2;
	xe::SpriteComponent *sp3;

private:
	xe::Renderer2D *renderer;

	xe::ECS ecs;

	OrthoCameraSystem *cameraSystem;
	xe::EntityHandle cameraEntity;

	xe::SpriteRendererSystem *spriteRenderer;
	xe::TextRendererSystem *textRenderer;

	xe::ECSSystemList mainSystems;
	xe::ECSSystemList renderingPipeline;

	xe::EntityHandle fpsText;
	xe::EntityHandle upsText;
	xe::EntityHandle frameTimeText;
	xe::EntityHandle dcText;

	xe::Transform *trackedTransform;
	xe::EntityHandle teNameText;
	xe::EntityHandle tePosText;
	xe::EntityHandle teDirText;
};


#endif //X808_TESTUI_HPP
