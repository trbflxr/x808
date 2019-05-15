//
// Created by FLXR on 2/12/2019.
//

#ifndef X808_AUDIOSOURCE_HPP
#define X808_AUDIOSOURCE_HPP


#include <xe/math/vec3.hpp>
#include <xe/resources/sound.hpp>

namespace xe {

  class XE_API AudioSource {
  public:
    explicit AudioSource(const string &name, const Sound *sound);
    virtual ~AudioSource();

    void play() const;
    void pause() const;
    void stop() const;
    void rewind() const;

    int32 state() const;

    bool isPlaying() const;
    bool isPaused() const;
    bool isStopped() const;

    void setPosition(const vec3 &position) const;
    vec3 getPosition() const;

    void setVelocity(const vec3 &velocity) const;
    vec3 getVelocity() const;

    void setOffset(float sec) const;
    float getOffset() const;

    void setPitch(float pitch) const;
    float getPitch() const;

    void setGain(float gain) const;
    float getGain() const;

    void setReferenceDistance(float distance) const;
    float getReferenceDistance() const;

    void setRolloffFactor(float factor) const;
    float getRolloffFactor() const;

    void setMaxDistance(float distance) const;
    float getMaxDistance() const;

    void setLooping(bool loop) const;
    bool isLooped() const;

    void bindSound(const Sound *sound) const;

    inline const Sound *getSound() const { return sound; }
    inline uint getHandle() const { return handle; }

    inline const string &getName() const { return name; }

  private:
    string name;
    const Sound *sound;

    uint handle;
  };

}


#endif //X808_AUDIOSOURCE_HPP
