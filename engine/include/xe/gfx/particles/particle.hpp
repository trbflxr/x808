//
// Created by FLXR on 2/19/2019.
//

#ifndef X808_PARTICLE_HPP
#define X808_PARTICLE_HPP


#include <vector>
#include <xe/xeint.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>
#include <xe/timeline/ramp.hpp>

namespace xe {

  class ParticleEffect;

  class Particle : public RectangleShape {
  public:
    explicit Particle(ParticleEffect *effect);
    ~Particle() override;

    void spawn(float lifeTime);

    void update(float delta);
    void fixedUpdate(float delta);

    inline Ramp<float> *getRotationRamp() const { return rotationRamp; }
    inline void setRotationRamp(Ramp<float> *ramp) { rotationRamp = ramp; }

    inline Ramp<vec2> *getTranslationRamp() const { return translationRamp; }
    inline void setTranslationRamp(Ramp<vec2> *ramp) { translationRamp = ramp; }

    inline Ramp<vec2> *getSizeRamp() const { return sizeRamp; }
    inline void setSizeRamp(Ramp<vec2> *ramp) { sizeRamp = ramp; }

    inline Ramp<vec4> *getColorRamp() const { return colorRamp; }
    inline void setColorRamp(Ramp<vec4> *ramp) { colorRamp = ramp; }

  private:
    ParticleEffect *effect;

    float time;
    float lifeTime;

    Ramp<float> *rotationRamp;
    Ramp<vec2> *translationRamp;
    Ramp<vec2> *sizeRamp;
    Ramp<vec4> *colorRamp;

    bool updateRotation;
    bool updateTranslation;
    bool updateSize;
    bool updateColor;
  };

}


#endif //X808_PARTICLE_HPP
