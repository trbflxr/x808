//
// Created by FLXR on 7/24/2018.
//

#ifndef X808_TESTUI_HPP
#define X808_TESTUI_HPP


#include <xe/ecs/ecs.hpp>
#include <xe/ecs/systems/spriterenderersystem.hpp>
#include <xe/ecs/systems/textrenderersystem.hpp>
#include <xe/gfx/layer.hpp>
#include <xe/gfx/2d/batchrenderer2d.hpp>
#include <xe/gfx/2d/primitiverenderer.hpp>

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
	xe::Sprite *sp0;
	xe::Sprite *sp1;
	xe::Sprite *sp2;
	xe::Sprite *sp3;

private:
	xe::Camera *camera;

	xe::BatchRenderer2D *renderer;
	xe::PrimitiveRenderer *primitiveRenderer;

	xe::ECS ecs;

	xe::SpriteRendererSystem *spriteRendererSystem;
	xe::TextRendererSystem *textRendererSystem;

	xe::ECSSystemList renderingPipeline;
	xe::ECSSystemList mainSystems;

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
