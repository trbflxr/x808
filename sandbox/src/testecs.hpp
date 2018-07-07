//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_TESTECS_HPP
#define X808_TESTECS_HPP


#include <gfx/layers/layer2d.hpp>
#include <ecs/ecs.hpp>

///components
struct Renderable2DComponent : public xe::ECSComponent<Renderable2DComponent> {
	xe::gfx::Renderable2D *renderable;
};

///systems
class Renderable2DSystem : public xe::BaseECSSystem {
public:
	explicit Renderable2DSystem(xe::gfx::Renderer2D *renderer) : BaseECSSystem(), renderer(renderer) {
		addComponentType(Renderable2DComponent::ID);
	}

	void updateComponents(float delta, xe::BaseECSComponent **components) override {
		Renderable2DComponent *r = (Renderable2DComponent *) components[0];

		r->renderable->rotate(1);

		renderer->submit(r->renderable);
	}

private:
	xe::gfx::Renderer2D *renderer;
};


class TestECS : public xe::gfx::Layer2D {
public:
	explicit TestECS();
	~TestECS() override;

	void render() override;
	void update(const xe::TimeStep &ts) override;
	void tick() override;

	void onEvent(xe::Event &event) override;

	bool onKeyPressedEvent(xe::KeyPressEvent &event);
	bool onMousePressedEvent(xe::MousePressEvent &event);
	bool onMouseMovedEvent(xe::MouseMoveEvent &event);

private:
	xe::ECS ecs;

	Renderable2DSystem *r2ds;

	xe::ECSSystemList mainSystems;
	xe::ECSSystemList renderingPipeline;
};


#endif //X808_TESTECS_HPP
