//
// Created by FLXR on 2/19/2019.
//

#include <xe/gfx/particles/particleeffect.hpp>
#include <xe/timeline/ramp.hpp>

namespace xe {

	ParticleEffect::ParticleEffect(uint count, float z) :
			count(count),
			z(z) {

		for (uint i = 0; i < count; ++i) {
			Particle *p = new Particle(this, z);
			p->setVisible(false);
			particles.push_back(p);
		}
	}

	ParticleEffect::~ParticleEffect() {
		for (const auto &p : particles) {
			delete p;
		}
	}

	void ParticleEffect::generate() {
		for (auto &&p : particles) {
			Particle *s = dynamic_cast<Particle *>(p);

			float duration = 10.0f;


			Ramp<float> *rotation = new Ramp<float>({std::make_pair(0.0f, 45.0f),
			                                         std::make_pair(0.5f, 90.0f),
			                                         std::make_pair(1.0f, -90.0f)},
			                                        [&](const float &s, const float &e, float t) -> float {
				                                        return (1.0f - t) * s + t * e;
			                                        },
			                                        duration);

			Ramp<vec2> *translation = new Ramp<vec2>({std::make_pair(0.0f, vec2(100.0f, 200.0f)),
			                                          std::make_pair(0.2f, vec2(200.0f, 200.0f)),
			                                          std::make_pair(0.6f, vec2(600.0f, 200.0f)),
			                                          std::make_pair(1.0f, vec2(200.0f, 100.0f))},
			                                         [&](const vec2 &s, const vec2 &e, float t) -> vec2 {
				                                         const float mt = (1.0f - t);
				                                         return vec2(mt * s.x + t * e.x, mt * s.y + t * e.y);
			                                         },
			                                         duration);

			Ramp<vec2> *size = new Ramp<vec2>({std::make_pair(0.0f, vec2(100.0f, 100.0f)),
			                                   std::make_pair(0.2f, vec2(200.0f, 200.0f)),
			                                   std::make_pair(0.5f, vec2(600.0f, 200.0f)),
			                                   std::make_pair(1.0f, vec2(100.0f, 100.0f))},
			                                  [&](const vec2 &s, const vec2 &e, float t) -> vec2 {
				                                  const float mt = (1.0f - t);
				                                  return vec2(mt * s.x + t * e.x, mt * s.y + t * e.y);
			                                  },
			                                  duration);

			Ramp<vec4> *color = new Ramp<vec4>({std::make_pair(0.0f, vec4(1.0f, 1.0f, 1.0f, 1.0f)),
			                                    std::make_pair(0.3f, vec4(1.0f, 0.0f, 0.0f, 1.0f)),
			                                    std::make_pair(1.0f, vec4(0.0f, 1.0f, 0.0f, 1.0f))},
			                                   [&](const vec4 &s, const vec4 &e, float t) -> vec4 {
				                                   const float mt = (1.0f - t);
				                                   return vec4(mt * s.x + t * e.x,
				                                               mt * s.y + t * e.y,
				                                               mt * s.z + t * e.z,
				                                               mt * s.w + t * e.w);
			                                   },
			                                   duration);

			s->setRotationRamp(rotation);
			s->setTranslationRamp(translation);
			s->setSizeRamp(size);
			s->setColorRamp(color);

			s->spawn(duration);
		}
	}

	void ParticleEffect::update(float delta) {
		for (auto &&p : particles) {
			if (p->isVisible()) {
				dynamic_cast<Particle *>(p)->update(delta);
			}
		}
	}

}