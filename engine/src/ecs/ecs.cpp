//
// Created by FLXR on 7/7/2018.
//

#include "ecs.hpp"
#include "utils/log.hpp"

namespace xe {

	ECS::~ECS() {
		for (auto &&component : components) {
			size_t typeSize = BaseECSComponent::getTypeSize(component.first);
			ECSComponentFreeFn freeFn = BaseECSComponent::getTypeFreeFn(component.first);

			for (uint i = 0; i < component.second.size(); i += typeSize) {
				freeFn((BaseECSComponent *) &component.second[i]);
			}
		}

		for (auto &&entity : entities) {
			delete entity;
		}
	}

	EntityHandle ECS::makeEntity(BaseECSComponent **components, const uint *componentIDs, size_t numComponents) {
		auto *newEntity = new std::pair<uint, std::vector<std::pair<uint, uint>>>();
		EntityHandle handle = (EntityHandle) newEntity;

		for (uint i = 0; i < numComponents; i++) {
			if (!BaseECSComponent::isTypeValid(componentIDs[i])) {
				XE_FATAL("[ECS] ", componentIDs[i], " is not a valid component type");

				delete newEntity;
				return nullptr;
			}

			addComponentInternal(handle, newEntity->second, componentIDs[i], components[i]);
		}

		newEntity->first = static_cast<uint>(entities.size());
		entities.push_back(newEntity);

		return handle;
	}

	void ECS::removeEntity(EntityHandle handle) {
		std::vector<std::pair<uint, uint> > &entity = handleToEntity(handle);

		for (auto &&component : entity) {
			deleteComponent(component.first, component.second);
		}

		uint destIndex = handleToEntityIndex(handle);
		uint srcIndex = static_cast<uint>(entities.size() - 1);

		delete entities[destIndex];

		entities[destIndex] = entities[srcIndex];
		entities.pop_back();
	}

	void ECS::updateSystems(ECSSystemList &systems, float delta) {
		std::vector<BaseECSComponent *> componentParam;
		std::vector<std::vector<uint8> *> componentArrays;

		for (uint i = 0; i < systems.size(); i++) {
			const std::vector<uint> &componentTypes = systems[i]->getComponentTypes();

			if (componentTypes.size() == 1) {
				size_t typeSize = BaseECSComponent::getTypeSize(componentTypes[0]);
				std::vector<uint8> &array = components[componentTypes[0]];

				for (uint j = 0; j < array.size(); j += typeSize) {
					BaseECSComponent *component = (BaseECSComponent *) &array[j];
					systems[i]->updateComponents(delta, &component);
				}
			} else {
				updateSystemWithMultipleComponents(i, systems, delta, componentTypes,
				                                   componentParam, componentArrays);
			}
		}
	}

	void ECS::deleteComponent(uint componentID, uint index) {
		std::vector<uint8> &array = components[componentID];
		ECSComponentFreeFn freeFn = BaseECSComponent::getTypeFreeFn(componentID);
		size_t typeSize = BaseECSComponent::getTypeSize(componentID);

		uint srcIndex = static_cast<uint>(array.size() - typeSize);

		BaseECSComponent *destComponent = (BaseECSComponent *) &array[index];
		BaseECSComponent *srcComponent = (BaseECSComponent *) &array[srcIndex];
		freeFn(destComponent);

		if (index == srcIndex) {
			array.resize(srcIndex);
			return;
		}
		memcpy(destComponent, srcComponent, typeSize);

		for (auto &&component : handleToEntity(srcComponent->entity)) {
			if (componentID == component.first && srcIndex == component.second) {
				component.second = index;
				break;
			}
		}

		array.resize(srcIndex);
	}

	bool ECS::removeComponentInternal(EntityHandle handle, uint componentID) {
		std::vector<std::pair<uint, uint> > &entityComponents = handleToEntity(handle);

		for (uint i = 0; i < entityComponents.size(); i++) {
			if (componentID == entityComponents[i].first) {
				deleteComponent(entityComponents[i].first, entityComponents[i].second);

				uint srcIndex = static_cast<uint>(entityComponents.size() - 1);
				uint destIndex = i;

//				entityComponents[destIndex] = entityComponents[srcIndex];
				memcpy(&entityComponents[destIndex],
				       &entityComponents[srcIndex],
				       sizeof(entityComponents[srcIndex]));

				entityComponents.pop_back();

				return true;
			}
		}
		return false;
	}

	void ECS::addComponentInternal(EntityHandle handle,
	                               std::vector<std::pair<uint, uint>> &entity,
	                               uint componentID,
	                               BaseECSComponent *component) {

		ECSComponentCreateFn createFn = BaseECSComponent::getTypeCreateFn(componentID);
		std::pair<uint, uint> newPair;

		newPair.first = componentID;
		newPair.second = createFn(components[componentID], handle, component);

		entity.push_back(newPair);
	}

	BaseECSComponent *ECS::getComponentInternal(std::vector<std::pair<uint, uint>> &entityComponents,
	                                            std::vector<uint8> &array,
	                                            uint componentID) {

		for (auto &&component : entityComponents) {
			if (componentID == component.first) {
				return (BaseECSComponent *) &array[component.second];
			}
		}
		return nullptr;
	}

	void ECS::updateSystemWithMultipleComponents(uint index, ECSSystemList &systems, float delta,
	                                             const std::vector<uint> &componentTypes,
	                                             std::vector<BaseECSComponent *> &componentParam,
	                                             std::vector<std::vector<uint8> *> &componentArrays) {

		const std::vector<uint> &componentFlags = systems[index]->getComponentFlags();

		componentParam.resize(__max(componentParam.size(), componentTypes.size()));
		componentArrays.resize(__max(componentArrays.size(), componentTypes.size()));

		for (uint i = 0; i < componentTypes.size(); i++) {
			componentArrays[i] = &components[componentTypes[i]];
		}
		uint minSizeIndex = findLeastCommonComponent(componentTypes, componentFlags);

		size_t typeSize = BaseECSComponent::getTypeSize(componentTypes[minSizeIndex]);
		std::vector<uint8> &array = *componentArrays[minSizeIndex];

		for (uint i = 0; i < array.size(); i += typeSize) {
			componentParam[minSizeIndex] = (BaseECSComponent *) &array[i];
			auto &entityComponents = handleToEntity(componentParam[minSizeIndex]->entity);

			bool isValid = true;
			for (uint j = 0; j < componentTypes.size(); j++) {
				if (j == minSizeIndex) {
					continue;
				}

				componentParam[j] = getComponentInternal(entityComponents, *componentArrays[j], componentTypes[j]);

				if (componentParam[j] == nullptr && (componentFlags[j] & BaseECSSystem::FLAG_OPTIONAL) == 0) {
					isValid = false;
					break;
				}
			}

			if (isValid) {
				systems[index]->updateComponents(delta, &componentParam[0]);
			}
		}

	}

	uint ECS::findLeastCommonComponent(const std::vector<uint> &componentTypes,
	                                   const std::vector<uint> &componentFlags) {

		uint minSize = static_cast<uint>(-1);
		uint minIndex = static_cast<uint>(-1);

		for (uint i = 0; i < componentTypes.size(); i++) {
			if ((componentFlags[i] & BaseECSSystem::FLAG_OPTIONAL) != 0) {
				continue;
			}

			size_t typeSize = BaseECSComponent::getTypeSize(componentTypes[i]);
			uint size = static_cast<uint>(components[componentTypes[i]].size() / typeSize);

			if (size <= minSize) {
				minSize = size;
				minIndex = i;
			}
		}

		return minIndex;
	}
}