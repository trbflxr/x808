//
// Created by FLXR on 7/1/2018.
//

#include "gameobject.hpp"
#include "components/gamecomponent.hpp"


xe::GameObject::GameObject(xe::Application *app) : application(app) { }

xe::GameObject &xe::GameObject::addObject(xe::GameObject *object) {
	object->getTransform().setParent(&transform);
	objects.emplace_back(std::unique_ptr<GameObject>(object));

	return *this;
}

xe::GameObject &xe::GameObject::addComponent(xe::GameComponent *component) {
	component->setBase(this);
	components.emplace_back(std::unique_ptr<GameComponent>(component));

	return *this;
}

void xe::GameObject::update(const xe::TimeStep &ts) {
	for (auto &&component : components) {
		component->update(ts);
	}

	for (auto &&object : objects) {
		object->update(ts);
	}
}

void xe::GameObject::input(const xe::TimeStep &ts) {
	for (auto &&component : components) {
		component->input(ts);
	}

	for (auto &&object : objects) {
		object->input(ts);
	}
}

void xe::GameObject::render(const xe::gfx::api::Shader *shader,
                            const xe::gfx::RenderingEngine *renderingEngine) const {

	for (auto &&component : components) {
		component->render(shader, renderingEngine);
	}

	for (auto &&object : objects) {
		object->render(shader, renderingEngine);
	}
}
