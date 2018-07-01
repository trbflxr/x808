//
// Created by FLXR on 6/30/2018.
//

#ifndef X808_ENTITY_HPP
#define X808_ENTITY_HPP


#include <unordered_map>
#include "components.hpp"
#include "utils/log.hpp"

namespace xe {

	class Entity {
	public:
		Entity() = default;

		explicit Entity(gfx::Sprite *sprite, const mat4 &transform = mat4(1.0f)) {
			addComponent(new SpriteComponent(sprite));
			addComponent(new TransformComponent(transform));
		}
		//todo: 3d mesh support

		void addComponent(Component *component) {
			XE_ASSERT(component->getType());
			components[component->getType()] = component;
		}

		template<typename T>
		const T *getComponent() const { return getComponentInternal<T>(); }

		template<typename T>
		T *getComponent() { return (T *) getComponentInternal<T>(); }

	private:
		template<typename T>
		const T *getComponentInternal() const {
			auto it = components.find(T::getStaticType());
			if (it == components.end()) return nullptr;

			return dynamic_cast<T *>(it->second);
		}

	protected:
		std::unordered_map<std::string, Component *> components;
	};

}


#endif //X808_ENTITY_HPP
