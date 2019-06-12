//
// Created by FLXR on 2/19/2019.
//

#ifndef X808_PARTICLEEFFECT_HPP
#define X808_PARTICLEEFFECT_HPP


#include <xe/xeint.hpp>
#include <xe/common.hpp>
#include <xe/math/itransformable2d.hpp>
#include <xe/gfx/particles/particle.hpp>

namespace xe {

  class Renderer2D;

  class XE_API ParticleEffect : public ITransformable2D {
  public:
    explicit ParticleEffect(float duration, float change, uint count, bool looped, uint maxTicks = 0);
    virtual ~ParticleEffect();

    void create();

    void update(float delta);
    void fixedUpdate(float delta);

    void play();
    void stop();

    void render(Renderer2D *renderer);

    inline bool isLooped() const { return looped; }
    inline void setLooped(bool looped) { ParticleEffect::looped = looped; }

    inline bool isFinished() const { return finished; }

    inline const Texture *getTexture() const { return texture; }
    inline void setTexture(const Texture *texture) { ParticleEffect::texture = texture; }

    inline const rect &getTextureRect() const { return textureRect; }
    inline void setTextureRect(const rect &rect) { textureRect = rect; }

    inline float getDuration() const { return duration; }
    inline void setDuration(float time) { duration = time; }

    inline float getChange() const { return change; }
    inline void setChange(float time) { change = time; }

    inline bool hasRotationChange() const { return rotationChange; }
    void setRotationChange(bool change);

    inline bool hasTranslationChange() const { return translationChange; }
    void setTranslationChange(bool change);

    inline bool hasSizeChange() const { return sizeChange; }
    void setSizeChange(bool change);

    inline bool hasColorChange() const { return colorChange; }
    void setColorChange(bool change);

    void setRotationStates(const std::vector<std::tuple<float, float, float>> &states);
    void setTranslationStates(const std::vector<std::tuple<float, vec2, vec2>> &states);
    void setSizeStates(const std::vector<std::tuple<float, vec2, vec2>> &states);
    void setColorStates(const std::vector<std::tuple<float, vec4, vec4>> &states);

  private:
    bool created;

    float duration;
    float change;

    bool looped;
    bool finished;

    uint count;

    float time;
    float tickTime;

    const Texture *texture;
    rect textureRect;

    std::vector<Particle *> particles;
    std::vector<Particle *> spawnQueue;

    bool rotationChange;
    bool translationChange;
    bool sizeChange;
    bool colorChange;

    std::vector<std::tuple<float, float, float>> rotationStates;
    std::vector<std::tuple<float, vec2, vec2>> translationStates;
    std::vector<std::tuple<float, vec2, vec2>> sizeStates;
    std::vector<std::tuple<float, vec4, vec4>> colorStates;
  };

}


#endif //X808_PARTICLEEFFECT_HPP
