//
// Created by FLXR on 7/5/2018.
//

#define GAU_THREAD_POLICY_MULTI 2

#include <gorilla/ga.h>
#include <gorilla/gau.h>
#include "soundmanager.hpp"
#include "utils/log.hpp"

namespace xe {

	SoundManager::SoundManager() {
		manager = gau_manager_create();
		mixer = gau_manager_mixer(manager);
	}

	SoundManager::~SoundManager() {
		clean();
	}

	SoundManager &SoundManager::instance() {
		static SoundManager sm;
		return sm;
	}

	void SoundManager::init() {
		gc_initialize(nullptr);
	}

	void SoundManager::add(Sound *sound) {
		auto &&it = instance().sounds.find(sound->getName());

		if (it != instance().sounds.end()) {
			XE_ERROR(sound->getName(), " already exist!");
			return;
		}

		instance().sounds.emplace(sound->getName(), sound);
	}

	Sound *SoundManager::get(const std::string_view &name) {
		auto &&it = instance().sounds.find(name.data());
		if (it == instance().sounds.end()) {
			return nullptr;
		}

		return it->second;
	}

	void SoundManager::update() {
		gau_manager_update(instance().manager);
	}

	void SoundManager::clean() {
		instance().sounds.clear();

		gau_manager_destroy(instance().manager);
		gc_shutdown();
	}


}