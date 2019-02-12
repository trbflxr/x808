//
// Created by FLXR on 2/12/2019.
//

#include <al/al.h>
#include <audio/alcommon.hpp>
#include <xe/audio/audiosource.hpp>
#include <xe/utils/assert.hpp>

namespace xe {

	AudioSource::AudioSource(const string &name, const Sound *sound) :
			name(name),
			sound(sound) {

		alCall(alGenSources(1, &handle));

		XE_ASSERT(handle, "[AudioSource]: unable to create audio source '", name, "'");

		bindSound(sound);
	}

	AudioSource::~AudioSource() {
		alCall(alSourcei(handle, AL_BUFFER, 0));
		alCall(alDeleteSources(1, &handle));
	}

	void AudioSource::play() const {
		alCall(alSourcePlay(handle));
	}

	void AudioSource::bindSound(const Sound *sound) const {
		alCall(alSourcei(handle, AL_BUFFER, sound->getHandle()));
	}

}