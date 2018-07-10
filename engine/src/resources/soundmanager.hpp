//
// Created by FLXR on 7/5/2018.
//

#ifndef X808_SOUNDMANAGER_HPP
#define X808_SOUNDMANAGER_HPP


#include <unordered_map>
#include "sound.hpp"

struct gau_Manager;
struct ga_Mixer;

namespace xe {

	class XE_API SoundManager {
	private:
		friend class Sound;

	public:
		~SoundManager();

		static void init();

		static void add(Sound *sound);
		static Sound *get(const std::string_view &name);

		static void update();
		static void clean();

		NULL_COPY_AND_ASSIGN(SoundManager);

	private:
		SoundManager();

		static SoundManager &instance();

	private:
		std::unordered_map<std::string, Sound *> sounds;

		gau_Manager *manager;
		ga_Mixer *mixer;
	};

}

#define GETSOUND(name) xe::SoundManager::get(name)


#endif //X808_SOUNDMANAGER_HPP