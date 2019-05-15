//
// Created by FLXR on 2/12/2019.
//

#include <al/al.h>
#include <audio/alcommon.hpp>
#include <xe/loaders/audioloader.hpp>
#include <xe/resources/sound.hpp>

namespace xe {

  int32 formatToAL(Sound::Format format) {
    switch (format) {
      case Sound::Format::Mono8: return AL_FORMAT_MONO8;
      case Sound::Format::Mono16: return AL_FORMAT_MONO16;
      case Sound::Format::Stereo8: return AL_FORMAT_STEREO8;
      case Sound::Format::Stereo16: return AL_FORMAT_STEREO16;
      case Sound::Format::Invalid: return 0;
    }
    return 0;
  }

  Sound::Sound(const string &name, const string &file) :
      name(name),
      handle(0),
      format(Format::Invalid) {

    byte *data = AudioLoader::load(file, this);

    if (data) {
      alCall(alGenBuffers(1, &handle));
      alCall(alBufferData(handle, formatToAL(format), data, size, freq));

      delete[] data;
    }
  }

  Sound::~Sound() {
    if (handle) {
      alCall(alDeleteBuffers(1, &handle));
    }
  }

}