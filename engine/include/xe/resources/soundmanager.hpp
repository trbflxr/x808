//
// Created by FLXR on 2/12/2019.
//

#ifndef X808_SOUNDMANAGER_HPP
#define X808_SOUNDMANAGER_HPP


#include <unordered_map>
#include <xe/common.hpp>
#include <xe/string.hpp>
#include <xe/resources/sound.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

	class XE_API SoundManager : NonCopyable {
	public:
		~SoundManager() override;

		static void init();

		static bool add(const Sound *sound);
		static const Sound *get(const string &name);

		static void clean();

	private:
		static SoundManager &instance();

	private:
		std::unordered_map<string, const Sound *> sounds;
	};

}

#define GETSOUND(name) xe::SoundManager::get(name)


#endif //X808_SOUNDMANAGER_HPP
