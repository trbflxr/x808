//
// Created by FLXR on 7/5/2018.
//

#include <gorilla/ga.h>
#include <gorilla/gau.h>
#include <vector>
#include <xe/resources/sound.hpp>
#include <xe/string.hpp>
#include <xe/utils/log.hpp>
#include <xe/resources/soundmanager.hpp>

namespace xe {

	Sound::Sound(const string &name, const string &path) :
			name(name),
			path(path),
			count(0),
			playing(false),
			gain(1.0f) {

		std::vector<string> split = splitString(path, '.');
		if (split.size() < 2) {
			XE_ERROR("[Sound]: Invalid filename ", path);
			return;
		}

		sound = gau_load_sound_file(path.data(), split.back().c_str());
		if (!sound) {
			XE_ERROR("[Sound]: Could not load file ", path);
		}
	}

	Sound::~Sound() {
		ga_sound_release(sound);
	}

	void Sound::play() const {
		playing = true;

		gc_int32 quit = 0;
		handle = gau_create_handle_sound(SoundManager::instance().mixer, sound, &destroyOnFinish, &quit, nullptr);
		handle->sound = (void *) this;
		ga_handle_play(handle);
		count++;
	}

	void Sound::loop() const {
		playing = true;

		gc_int32 quit = 0;
		handle = gau_create_handle_sound(SoundManager::instance().mixer, sound, &loopOnFinish, &quit, nullptr);
		handle->sound = (void *) this;
		ga_handle_play(handle);
	}

	void Sound::pause() const {
		if (!playing) return;

		playing = false;
		ga_handle_stop(handle);

	}

	void Sound::resume() const {
		if (playing) return;

		playing = true;
		ga_handle_play(handle);
	}

	void Sound::stop() const {
		if (!playing) return;

		ga_handle_stop(handle);
		playing = false;
	}

	void Sound::setGain(float gain) const {
		if (!playing) {
			XE_ERROR(L"[Sound]: Cannot set gain! Sound is not currently playing!");
			return;
		}

		Sound::gain = gain;

		ga_handle_setParamf(handle, GA_HANDLE_PARAM_GAIN, gain);
	}

	void destroyOnFinish(ga_Handle *handle, void *context) {
		Sound *sound = (Sound *) handle->sound;
		sound->count--;

		if (sound->count == 0) {
			sound->stop();
		}
	}

	void loopOnFinish(ga_Handle *handle, void *context) {
		Sound *sound = (Sound *) handle->sound;
		sound->loop();
		sound->setGain(sound->gain);
		ga_handle_destroy(handle);
	}

}
