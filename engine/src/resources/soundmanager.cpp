//
// Created by FLXR on 2/12/2019.
//

#include <xe/utils/logger.hpp>
#include <xe/loaders/audioloader.hpp>
#include <xe/resources/soundmanager.hpp>

namespace xe {

	SoundManager::~SoundManager() {
		clean();
	}

	SoundManager &SoundManager::instance() {
		static SoundManager sm;
		return sm;
	}

	void SoundManager::init() {
		instance();
	}

	bool SoundManager::add(const Sound *sound) {
		auto &&it = instance().sounds.find(sound->getName());

		if (it != instance().sounds.end()) {
			XE_CORE_ERROR("[SoundManager]: sound '", sound->getName(), "' already exist and be deleted.");

			delete sound;
			return false;
		}

		instance().sounds.emplace(sound->getName(), sound);

		return true;
	}

	const Sound *SoundManager::get(const string &name) {
		auto &&it = instance().sounds.find(name);
		if (it == instance().sounds.end()) {
			XE_CORE_ERROR("[SoundManager]: sound '", name, "' not found!");
			return nullptr;
		}

		return it->second;
	}

	void SoundManager::clean() {
		for (const auto &s : instance().sounds) {
			delete s.second;
		}
	}

}
