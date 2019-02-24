//
// Created by FLXR on 2/19/2019.
//

#include <xe/gfx/particles/particleeffect.hpp>
#include <xe/gfx/particles/particle.hpp>

#include <xe/utils/logger.hpp> //fixme

namespace xe {

	Particle::Particle(ParticleEffect *effect) :
			RectangleShape({1.0f, 1.0f}),
			effect(effect),
			time(0.0f),
			lifeTime(0.0f),
			rotationRamp(nullptr),
			translationRamp(nullptr),
			sizeRamp(nullptr),
			colorRamp(nullptr) {

	}

	Particle::~Particle() {
		delete rotationRamp;
		delete translationRamp;
		delete sizeRamp;
		delete colorRamp;
	}


	void Particle::spawn(float lifeTime) {
		setVisible(true);
		Particle::lifeTime = lifeTime;
		time = 0.0f;

		if (rotationRamp) {
			rotationRamp->reset(lifeTime);
			setRotation(rotationRamp->getValue());
		}

		if (translationRamp) {
			translationRamp->reset(lifeTime);
			setPosition(translationRamp->getValue());
		}

		if (sizeRamp) {
			sizeRamp->reset(lifeTime);
			setSize(sizeRamp->getValue());
		}

		if (colorRamp) {
			colorRamp->reset(lifeTime);
			setColor(color::encode(colorRamp->getValue()));
		}
	}

	void Particle::update(float delta) {
		if (time >= lifeTime) {
			setVisible(false);
			return;
		}

		time += delta;

		if (rotationRamp && rotationRamp->update(delta)) {
			setRotation(rotationRamp->getValue());
		}

		if (translationRamp && translationRamp->update(delta)) {
			setPosition(translationRamp->getValue());
		}

		if (sizeRamp && sizeRamp->update(delta)) {
			setSize(sizeRamp->getValue());
		}

		if (colorRamp && colorRamp->update(delta)) {
			setColor(color::encode(colorRamp->getValue()));
		}
	}

}