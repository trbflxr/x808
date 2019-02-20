//
// Created by FLXR on 2/19/2019.
//

#include <xe/gfx/particles/particleeffect.hpp>

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

			s->setColor(color::Red);
			s->setSize({100, 100});
			s->setPosition(getPosition());

			s->setColorStates({std::make_pair(0.0f, vec4(1, 1, 1, 1)),
			                   std::make_pair(0.5f, vec4(1, 0, 1, 1)),
			                   std::make_pair(1.0f, vec4(1, 0, 0, 1))});

			s->setRotationStates({std::make_pair(0.0f, 0.0f),
			                      std::make_pair(0.5f, 15.0f),
			                      std::make_pair(1.0f, 45.0f)});

			s->setPositionStates({std::make_pair(0.0f, vec2(0.0f, 0.0f)),
			                      std::make_pair(0.2f, vec2(20.0f, 20.0f)),
			                      std::make_pair(0.5f, vec2(50.0f, 50.0f)),
			                      std::make_pair(1.0f, vec2(100.0f, 100.0f))});

			s->setSizeStates({std::make_pair(0.0f, vec2(100.0f, 100.0f)),
			                  std::make_pair(0.2f, vec2(20.0f, 20.0f)),
			                  std::make_pair(0.5f, vec2(50.0f, 50.0f)),
			                  std::make_pair(1.0f, vec2(100.0f, 100.0f))});

			s->spawn(3.0f);
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