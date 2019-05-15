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
    stop();
    alCall(alSourcei(handle, AL_BUFFER, 0));
    alCall(alDeleteSources(1, &handle));
  }

  int32 AudioSource::state() const {
    int32 state;
    alCall(alGetSourcei(handle, AL_SOURCE_STATE, &state));
    return state;
  }

  void AudioSource::play() const {
    alCall(alSourcePlay(handle));
  }

  void AudioSource::pause() const {
    alCall(alSourcePause(handle));
  }

  void AudioSource::stop() const {
    alCall(alSourceStop(handle));
  }

  void AudioSource::rewind() const {
    alCall(alSourceRewind(handle));
  }

  bool AudioSource::isPlaying() const {
    return state() == AL_PLAYING;
  }

  bool AudioSource::isPaused() const {
    return state() == AL_PAUSED;
  }

  bool AudioSource::isStopped() const {
    return state() == AL_STOPPED;
  }

  void AudioSource::setPosition(const vec3 &position) const {
    alCall(alSource3f(handle, AL_POSITION, position.x, position.y, position.z));
  }

  vec3 AudioSource::getPosition() const {
    vec3 position;
    alCall(alGetSource3f(handle, AL_POSITION, &position.x, &position.y, &position.z));
    return position;
  }

  void AudioSource::setVelocity(const vec3 &velocity) const {
    alCall(alSource3f(handle, AL_VELOCITY, velocity.x, velocity.y, velocity.z));
  }

  vec3 AudioSource::getVelocity() const {
    vec3 velocity;
    alCall(alGetSource3f(handle, AL_VELOCITY, &velocity.x, &velocity.y, &velocity.z));
    return velocity;
  }

  void AudioSource::setOffset(float sec) const {
    alCall(alSourcef(handle, AL_SEC_OFFSET, sec));
  }

  float AudioSource::getOffset() const {
    float offset = 0;
    alCall(alGetSourcef(handle, AL_SEC_OFFSET, &offset));
    return offset;
  }

  void AudioSource::setPitch(float pitch) const {
    alCall(alSourcef(handle, AL_PITCH, pitch));
  }

  float AudioSource::getPitch() const {
    float pitch = 0.0f;
    alCall(alGetSourcef(handle, AL_PITCH, &pitch));
    return pitch;
  }

  void AudioSource::setGain(float gain) const {
    alCall(alSourcef(handle, AL_GAIN, gain));
  }

  float AudioSource::getGain() const {
    float gain = 0.0f;
    alCall(alGetSourcef(handle, AL_GAIN, &gain));
    return gain;
  }

  void AudioSource::bindSound(const Sound *sound) const {
    alCall(alSourcei(handle, AL_BUFFER, sound->getHandle()));
  }

  void AudioSource::setReferenceDistance(float distance) const {
    alCall(alSourcef(handle, AL_REFERENCE_DISTANCE, distance));
  }

  float AudioSource::getReferenceDistance() const {
    float distance = 0.0f;
    alCall(alGetSourcef(handle, AL_REFERENCE_DISTANCE, &distance));
    return distance;
  }

  void AudioSource::setRolloffFactor(float factor) const {
    alCall(alSourcef(handle, AL_ROLLOFF_FACTOR, factor));
  }

  float AudioSource::getRolloffFactor() const {
    float factor = 0.0f;
    alCall(alGetSourcef(handle, AL_ROLLOFF_FACTOR, &factor));
    return factor;
  }

  void AudioSource::setMaxDistance(float distance) const {
    alCall(alSourcef(handle, AL_MAX_DISTANCE, distance));
  }

  float AudioSource::getMaxDistance() const {
    float distance = 0.0f;
    alCall(alGetSourcef(handle, AL_MAX_DISTANCE, &distance));
    return distance;
  }

  void AudioSource::setLooping(bool loop) const {
    alCall(alSourcei(handle, AL_LOOPING, loop ? AL_TRUE : AL_FALSE));
  }

  bool AudioSource::isLooped() const {
    int32 looped = 0;
    alCall(alGetSourcei(handle, AL_LOOPING, &looped));
    return looped != 0;
  }

}