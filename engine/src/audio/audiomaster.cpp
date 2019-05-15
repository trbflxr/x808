//
// Created by FLXR on 2/12/2019.
//

#include <al/al.h>
#include <al/alc.h>
#include <al/alext.h>
#include <audio/alcommon.hpp>
#include <xe/utils/logger.hpp>
#include <xe/audio/audiomaster.hpp>

namespace xe {

  int32 distanceModelToAl(DistanceModel model) {
    switch (model) {
      case DistanceModel::Inverse: return AL_INVERSE_DISTANCE;
      case DistanceModel::InverseClamped: return AL_INVERSE_DISTANCE_CLAMPED;
      case DistanceModel::Linear: return AL_LINEAR_DISTANCE;
      case DistanceModel::LinearClamped: return AL_LINEAR_DISTANCE_CLAMPED;
      case DistanceModel::Exponent: return AL_EXPONENT_DISTANCE;
      case DistanceModel::ExponentClamped: return AL_EXPONENT_DISTANCE_CLAMPED;
      default: return 0;
    }
    return 0;
  }

  void AudioMaster::initialize() {
    alCall(get().device = alcOpenDevice(nullptr));
    if (get().device) {
      alCall(get().context = alcCreateContext(static_cast<ALCdevice *>(get().device), nullptr));
      alCall(alcMakeContextCurrent(static_cast<ALCcontext *>(get().context)));
    } else {
      XE_CORE_FATAL("[AudioMaster]: Cant open device");
    }
  }

  AudioMaster::~AudioMaster() {
    alCall(alcMakeContextCurrent(nullptr));
    alCall(alcDestroyContext(static_cast<ALCcontext *>(context)));
    alCall(alcCloseDevice(static_cast<ALCdevice *>(device)));
  }

  AudioMaster &AudioMaster::get() {
    static AudioMaster am;
    return am;
  }

  void AudioMaster::setDistanceModel(DistanceModel model) {
    alCall(alDistanceModel(distanceModelToAl(model)));
  }

  std::vector<string> AudioMaster::getDeviceList() {
    alCall(const char *list = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER));

    const char *device = list;
    const char *next = list + 1;
    size_t len = 0;

    std::vector<string> devices;
    while (device && *device != '\0' && next && *next != '\0') {
      devices.emplace_back(device);
      len = strlen(device);
      device += (len + 1);
      next += (len + 2);
    }

    return devices;
  }

}
