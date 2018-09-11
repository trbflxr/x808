//
// Created by FLXR on 9/11/2018.
//

#ifndef X808_TESTB2D_HPP
#define X808_TESTB2D_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/camera.hpp>
#include <xe/gfx/2d/batchrenderer2d.hpp>
#include <xe/ecs/ecs.hpp>
#include <xe/ecs/systems/spriterenderersystem.hpp>
#include <xe/ecs/systems/textrenderersystem.hpp>
#include <xe/physics/2d/physicsworld2d.hpp>

class TestB2D : public xe::Layer {
public:
	explicit TestB2D();
	~TestB2D() override;

	void render() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

private:
	xe::Camera *camera;

	xe::BatchRenderer2D *renderer;

	xe::ECS ecs;

	xe::SpriteRendererSystem *spriteRendererSystem;
	xe::TextRendererSystem *textRendererSystem;

	xe::ECSSystemList mainSystems;
	xe::ECSSystemList renderingPipeline;

	xe::EntityHandle sprite;
	xe::EntityHandle sprite1;

	xe::PhysicsWorld2D *world;
};

#endif //X808_TESTB2D_HPP
