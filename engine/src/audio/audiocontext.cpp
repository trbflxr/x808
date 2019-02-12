//
// Created by FLXR on 2/12/2019.
//

#include <al/alc.h>
#include <audio/alcommon.hpp>
#include <xe/audio/audiocontext.hpp>
#include <xe/utils/logger.hpp>

namespace xe {

	AudioContext::~AudioContext() {
		alCall(alcMakeContextCurrent(nullptr));
		alCall(alcDestroyContext(static_cast<ALCcontext *>(context)));
		alCall(alcCloseDevice(static_cast<ALCdevice *>(device)));
	}

	void AudioContext::create() {
		alCall(instance().device = alcOpenDevice(nullptr));
		if (instance().device) {
			alCall(instance().context = alcCreateContext(static_cast<ALCdevice *>(instance().device), nullptr));
			alCall(alcMakeContextCurrent(static_cast<ALCcontext *>(instance().context)));
		} else {
			XE_CORE_FATAL("[AudioContext]: Cant open device");
		}
	}

	AudioContext &AudioContext::instance() {
		static AudioContext ac;
		return ac;
	}

}
