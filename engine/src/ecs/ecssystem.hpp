//
// Created by FLXR on 7/7/2018.
//

#ifndef X808_ECSSYSTEM_HPP
#define X808_ECSSYSTEM_HPP


#include "ecscomponent.hpp"

namespace xe {

	class XE_API BaseECSSystem {
	public:
		enum {
			FLAG_OPTIONAL = 1,
		};

	public:
		BaseECSSystem() = default;

		virtual void updateComponents(float delta, BaseECSComponent **components) { }

		inline const std::vector<uint> &getComponentTypes() const { return componentTypes; }
		inline const std::vector<uint> &getComponentFlags() const { return componentFlags; }

		bool isValid();

	protected:
		void addComponentType(uint componentType, uint componentFlag = 0) {
			componentTypes.push_back(componentType);
			componentFlags.push_back(componentFlag);
		}

	private:
		std::vector<uint> componentTypes;
		std::vector<uint> componentFlags;
	};


	///-------- ECSSystemList --------///
	class XE_API ECSSystemList {
	public:
		bool addSystem(BaseECSSystem &system);
		bool removeSystem(BaseECSSystem &system);

		inline size_t size() { return systems.size(); }

		inline BaseECSSystem *operator[](uint index) { return systems[index]; }

	private:
		std::vector<BaseECSSystem *> systems;
	};


}


#endif //X808_ECSSYSTEM_HPP
