//
// Created by FLXR on 7/5/2018.
//

#define GAU_THREAD_POLICY_MULTI 2

#include <gorilla/ga.h>
#include <gorilla/gau.h>
#include <xe/resources/soundmanager.hpp>
#include <xe/utils/logger.hpp>

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

	bool SoundManager::add(Sound *sound) {
		auto &&it = instance().sounds.find(sound->getName());

		if (it != instance().sounds.end()) {
			XE_CORE_ERROR("[SoundManager]: sound '", sound->getName(), "' already exist and be deleted");

			delete sound;
			return false;
		}

		instance().sounds.emplace(sound->getName(), sound);
		return true;
	}

	const Sound *SoundManager::get(const string &name) {
		auto &&it = instance().sounds.find(name);
		if (it == instance().sounds.end()) {
			return nullptr;
		}

		return it->second;
	}

	void SoundManager::update() {
		gau_manager_update(instance().manager);
	}

	void SoundManager::clean() {
		for (auto &&sound : instance().sounds) {
			delete sound.second;
		}

		gau_manager_destroy(instance().manager);
		gc_shutdown();
	}


}