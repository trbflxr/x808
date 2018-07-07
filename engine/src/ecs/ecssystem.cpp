//
// Created by FLXR on 7/7/2018.
//

#include "ecssystem.hpp"

namespace xe {

	///-------- BaseECSSystem --------///
	bool BaseECSSystem::isValid() {
		for (uint componentFlag : componentFlags) {
			if((componentFlag & BaseECSSystem::FLAG_OPTIONAL) == 0) {
				return true;
			}
		}
		return false;
	}


	///-------- ECSSystemList --------///
	bool ECSSystemList::addSystem(BaseECSSystem &system) {
		if (!system.isValid()) {
			return false;
		}
		systems.push_back(&system);
		return true;
	}

	bool ECSSystemList::removeSystem(BaseECSSystem &system) {
		for(uint i = 0; i < systems.size(); i++) {
			if(&system == systems[i]) {
				systems.erase(systems.begin() + i);
				return true;
			}
		}
		return false;
	}

}