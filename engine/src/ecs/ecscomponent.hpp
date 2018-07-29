//
// Created by FLXR on 7/7/2018.
//

#ifndef X808_ECSCOMPONENT_HPP
#define X808_ECSCOMPONENT_HPP


#include <tuple>
#include <vector>
#include <functional>
#include "xeint.hpp"
#include "common.hpp"

namespace xe {

	struct BaseECSComponent;

	typedef void *EntityHandle;

	typedef std::function<uint(std::vector<byte> &, EntityHandle, BaseECSComponent *)> ECSComponentCreateFn;
	typedef std::function<void(BaseECSComponent *)> ECSComponentFreeFn;

	struct XE_API BaseECSComponent {
	public:
		static uint registerComponentType(ECSComponentCreateFn createFn, ECSComponentFreeFn freeFn, size_t size);

		inline static ECSComponentCreateFn getTypeCreateFn(uint id) {
			return std::get<0>((*componentTypes)[id]);
		}

		inline static ECSComponentFreeFn getTypeFreeFn(uint id) {
			return std::get<1>((*componentTypes)[id]);
		}

		inline static size_t getTypeSize(uint id) {
			return std::get<2>((*componentTypes)[id]);
		}

		inline static bool isTypeValid(uint id) {
			return id < componentTypes->size();
		}

	public:
		EntityHandle entity = nullptr;

	private:
		static std::vector<std::tuple<ECSComponentCreateFn, ECSComponentFreeFn, size_t>> *componentTypes;

	};


	///-------- ECSComponent --------///
	template<typename T>
	struct ECSComponent : public BaseECSComponent {
		static const ECSComponentCreateFn CREATE_FUNCTION;
		static const ECSComponentFreeFn FREE_FUNCTION;
		static const uint ID;
		static const size_t SIZE;
	};

	template<typename Component>
	uint ECSComponentCreate(std::vector<byte> &memory, EntityHandle entity, BaseECSComponent *comp) {
		uint index = static_cast<uint>(memory.size());
		memory.resize(index + Component::SIZE);

		Component *component = new(&memory[index])Component(*(Component *) comp);
		component->entity = entity;

		return index;
	}

	template<typename Component>
	void ECSComponentFree(BaseECSComponent *comp) {
		Component *component = (Component *) comp;
		component->~Component();
	}

	template<typename T>
	const uint xe::ECSComponent<T>::ID(xe::BaseECSComponent::registerComponentType(xe::ECSComponentCreate<T>,
	                                                                               xe::ECSComponentFree<T>,
	                                                                               sizeof(T)));

	template<typename T>
	const size_t ECSComponent<T>::SIZE(sizeof(T));

	template<typename T>
	const xe::ECSComponentCreateFn ECSComponent<T>::CREATE_FUNCTION(xe::ECSComponentCreate<T>);

	template<typename T>
	const xe::ECSComponentFreeFn ECSComponent<T>::FREE_FUNCTION(xe::ECSComponentFree<T>);


}


#endif //X808_ECSCOMPONENT_HPP
