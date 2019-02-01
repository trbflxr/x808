//
// Created by FLXR on 7/5/2018.
//

#ifndef X808_SOUNDMANAGER_HPP
#define X808_SOUNDMANAGER_HPP


#include <unordered_map>
#include <xe/resources/sound.hpp>
#include <xe/string.hpp>
#include <xe/utils/noncopyable.hpp>

struct gau_Manager;
struct ga_Mixer;

namespace xe {

	class XE_API SoundManager : NonCopyable {
	private:
		friend class Sound;

	public:
		~SoundManager() override;

		static void init();

		static bool add(Sound *sound);
		static const Sound *get(const string &name);

		static void update();
		static void clean();

	private:
		SoundManager();

		static SoundManager &instance();

	private:
		std::unordered_map<string, const Sound *> sounds;

		gau_Manager *manager;
		ga_Mixer *mixer;
	};

}

#define GETSOUND(name) xe::SoundManager::get(name)


#endif //X808_SOUNDMANAGER_HPP
