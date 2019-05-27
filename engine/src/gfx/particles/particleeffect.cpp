//
// Created by FLXR on 2/19/2019.
//

#include <xe/gfx/particles/particleeffect.hpp>
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/timeline/ramp.hpp>
#include <xe/config.hpp>

namespace xe {

  ParticleEffect::ParticleEffect(float duration, float change, uint count, bool looped, uint maxTicks) :
      created(false),
      duration(duration),
      change(change),
      looped(looped),
      finished(true),
      count(count),
      time(0.0f),
      tickTime(0.0f),
      texture(nullptr),
      rotationChange(true),
      translationChange(true),
      sizeChange(true),
      colorChange(true) {

    uint ups = maxTicks == 0 ? Config::get().tickRate : maxTicks;
    tickTime = 1.0f / ups;

    for (uint i = 0; i < count; ++i) {
      Particle *p = new Particle(this);
      p->setVisible(false);
      particles.push_back(p);
    }

    rotationStates.emplace_back(0.0f, 0.0f, 0.0f);
    translationStates.emplace_back(0.0f, vec2(0.0f), vec2(0.0f));
    sizeStates.emplace_back(0.0f, vec2(0.0f), vec2(0.0f));
    colorStates.emplace_back(0.0f, vec4(1.0f), vec4(0.0f));
  }

  ParticleEffect::~ParticleEffect() {
    for (const auto &p : particles) {
      delete p;
    }
  }

  void ParticleEffect::create() {
    created = true;

    for (auto &&p : particles) {
      Particle *s = dynamic_cast<Particle *>(p);

      Ramp<float> *rotation = new Ramp<float>(rotationStates, Ramp<float>::lerp);
      rotation->setHasChange(rotationChange);

      Ramp<vec2> *translation = new Ramp<vec2>(translationStates, Ramp<vec2>::lerp);
      translation->setHasChange(translationChange);

      Ramp<vec2> *size = new Ramp<vec2>(sizeStates, Ramp<vec2>::lerp);
      size->setHasChange(sizeChange);

      Ramp<vec4> *color = new Ramp<vec4>(colorStates, Ramp<vec4>::lerp);
      color->setHasChange(colorChange);

      s->setRotationRamp(rotation);
      s->setTranslationRamp(translation);
      s->setSizeRamp(size);
      s->setColorRamp(color);

      s->setTexture(texture);
      s->setTextureRect(textureRect);
    }
  }

  void ParticleEffect::update(float delta) {
    XE_ASSERT(created, "Call create() first");

    if (finished) return;

    for (auto &&p : particles) {
      if (p->isVisible()) {
        Particle *s = dynamic_cast<Particle *>(p);

        s->update(delta);
        if (!s->isVisible()) {
          spawnQueue.push(s);

          if (spawnQueue.size() == count) {
            finished = true;
          }
        }
      }
    }

    if (looped) {
      if (!spawnQueue.empty()) {
        const float d = random::next<float>(duration - change, duration + change);

        Particle *p = spawnQueue.front();
        spawnQueue.pop();
        p->spawn(d);
      }
    }
  }

  void ParticleEffect::fixedUpdate(float delta) {
    XE_ASSERT(created, "Call create() first");

    if (finished) return;

    time += delta;
    if (time >= tickTime) {
      time = 0.0f;

      for (auto &&p : particles) {
        if (p->isVisible()) {
          Particle *s = dynamic_cast<Particle *>(p);
          s->fixedUpdate(delta);
        }
      }
    }
  }

  void ParticleEffect::play() {
    if (!finished) return;

    finished = false;

    for (auto &&p : particles) {
      Particle *s = dynamic_cast<Particle *>(p);
      const float d = random::next<float>(duration - change, duration + change);

      s->spawn(d);
    }

    while (!spawnQueue.empty()) {
      spawnQueue.pop();
    }
  }

  void ParticleEffect::stop() {
    if (finished) return;

    finished = true;

    for (auto &&p : particles) {
      p->setVisible(false);
    }

    while (!spawnQueue.empty()) {
      spawnQueue.pop();
    }
  }

  void ParticleEffect::render(Renderer2D *renderer) {
    renderer->push(toMatrix());

    for (auto &&p : particles) {
      renderer->submit(p);
    }

    renderer->pop();
  }

  void ParticleEffect::setRotationStates(const std::vector<std::tuple<float, float, float>> &states) {
    rotationStates = states;
    if (created) {
      for (auto &&p : particles) {
        dynamic_cast<Particle *>(p)->getRotationRamp()->setStates(rotationStates);
      }
    }
  }

  void ParticleEffect::setTranslationStates(const std::vector<std::tuple<float, vec2, vec2>> &states) {
    translationStates = states;
    if (created) {
      for (auto &&p : particles) {
        dynamic_cast<Particle *>(p)->getTranslationRamp()->setStates(translationStates);
      }
    }
  }

  void ParticleEffect::setSizeStates(const std::vector<std::tuple<float, vec2, vec2>> &states) {
    sizeStates = states;
    if (created) {
      for (auto &&p : particles) {
        dynamic_cast<Particle *>(p)->getSizeRamp()->setStates(sizeStates);
      }
    }
  }

  void ParticleEffect::setColorStates(const std::vector<std::tuple<float, vec4, vec4>> &states) {
    colorStates = states;
    if (created) {
      for (auto &&p : particles) {
        dynamic_cast<Particle *>(p)->getColorRamp()->setStates(colorStates);
      }
    }
  }

  void ParticleEffect::setRotationChange(bool change) {
    rotationChange = change;
    if (created) {
      for (auto &&p : particles) {
        dynamic_cast<Particle *>(p)->getRotationRamp()->setHasChange(rotationChange);
      }
    }
  }

  void ParticleEffect::setTranslationChange(bool change) {
    translationChange = change;
    if (created) {
      for (auto &&p : particles) {
        dynamic_cast<Particle *>(p)->getTranslationRamp()->setHasChange(translationChange);
      }
    }
  }

  void ParticleEffect::setSizeChange(bool change) {
    sizeChange = change;
    if (created) {
      for (auto &&p : particles) {
        dynamic_cast<Particle *>(p)->getSizeRamp()->setHasChange(sizeChange);
      }
    }
  }

  void ParticleEffect::setColorChange(bool change) {
    colorChange = change;
    if (created) {
      for (auto &&p : particles) {
        dynamic_cast<Particle *>(p)->getColorRamp()->setHasChange(colorChange);
      }
    }
  }

}