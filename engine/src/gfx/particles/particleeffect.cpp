//
// Created by FLXR on 2/19/2019.
//

#include <xe/gfx/particles/particleeffect.hpp>

namespace xe {

	ParticleEffect::ParticleEffect(uint count, float z) :
			count(count),
			z(z) {

		for (uint i = 0; i < count; ++i) {
			Particle *p = new Particle({1.0f, 1.0f}, z);
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
			s->spawn(100.0f);
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