//
// Created by FLXR on 7/1/2018.
//

#include "gameobject.hpp"

xe::GameObject &xe::GameObject::addObject(xe::GameObject *object) {
	object->getTransform().setParent(&transform);
	objects.emplace_back(std::unique_ptr<GameObject>(object));

	return *this;
}

void xe::GameObject::update(const xe::TimeStep &ts) {
	updateInternal(ts);

	for (auto &&object : objects) {
		object->update(ts);
	}
}

void xe::GameObject::input(const xe::TimeStep &ts) {
	inputInternal(ts);

	for (auto &&object : objects) {
		object->input(ts);
	}
}

void xe::GameObject::render(const xe::gfx::api::Shader1 *shader) {
	renderInternal(shader);

	for (auto &&object : objects) {
		object->render(shader);
	}
}
