//
// Created by FLXR on 7/7/2018.
//

#include "ecscomponent.hpp"

namespace xe {

	std::vector<std::tuple<ECSComponentCreateFn, ECSComponentFreeFn, size_t>> *BaseECSComponent::componentTypes;

	uint BaseECSComponent::registerComponentType(ECSComponentCreateFn createFn,
	                                             ECSComponentFreeFn freeFn, size_t size) {
		if (!componentTypes) {
			componentTypes = new std::vector<std::tuple<ECSComponentCreateFn, ECSComponentFreeFn, size_t>>();
		}

		uint componentID = static_cast<uint>(componentTypes->size());
		componentTypes->push_back(std::tuple<ECSComponentCreateFn, ECSComponentFreeFn, size_t>(createFn, freeFn, size));

		return componentID;
	}

}