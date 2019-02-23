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
		rotationStates.emplace_back(0.0f, 45.0f, 10.0f);
		rotationStates.emplace_back(0.5f, 90.0f, 20.0f);
		rotationStates.emplace_back(1.0f, -90.0f, 10.0f);


		translationStates.emplace_back(0.0f, vec2(100.0f, 200.0f), vec2(10.0f, 10.0f));
		translationStates.emplace_back(0.2f, vec2(200.0f, 200.0f), vec2(10.0f, 10.0f));
		translationStates.emplace_back(0.6f, vec2(600.0f, 200.0f), vec2(10.0f, 10.0f));
		translationStates.emplace_back(1.0f, vec2(200.0f, 100.0f), vec2(10.0f, 10.0f));


		sizeStates.emplace_back(0.0f, vec2(100.0f, 100.0f), vec2(10.0f, 10.0f));
		sizeStates.emplace_back(0.2f, vec2(200.0f, 200.0f), vec2(10.0f, 10.0f));
		sizeStates.emplace_back(0.6f, vec2(600.0f, 200.0f), vec2(10.0f, 10.0f));
		sizeStates.emplace_back(1.0f, vec2(100.0f, 100.0f), vec2(10.0f, 10.0f));

		colorStates.emplace_back(0.0f, vec4(1.0f, 0.0f, 0.0f, 1.0f));
		colorStates.emplace_back(0.5f, vec4(0.0f, 1.0f, 0.0f, 1.0f));
		colorStates.emplace_back(1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f));


		for (auto &&p : particles) {
			Particle *s = dynamic_cast<Particle *>(p);

			float duration = 10.0f;

			s->setSize({100, 100});
			s->setPosition({100, 100});


			Ramp<float> *rotation = new Ramp<float>(rotationStates, Ramp<float>::lerp, duration);
			Ramp<vec2> *translation = new Ramp<vec2>(translationStates, Ramp<vec2>::lerp, duration);
			Ramp<vec2> *size = new Ramp<vec2>(sizeStates, Ramp<vec2>::lerp, duration);
			Ramp<vec4> *color = new Ramp<vec4>(colorStates, Ramp<vec4>::lerp, duration);

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