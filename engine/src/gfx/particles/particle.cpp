//
// Created by FLXR on 2/19/2019.
//

#include <xe/gfx/particles/particleeffect.hpp>
#include <xe/gfx/particles/particle.hpp>

#include <xe/utils/logger.hpp> //fixme

namespace xe {

	Particle::Particle(ParticleEffect *effect, float layer) :
			RectangleShape({1.0f, 1.0f}, layer),
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
			setRotation(rotationRamp->getValue());
		}

		if (translationRamp) {
			setPosition(translationRamp->getValue());
		}

		if (sizeRamp) {
			setSize(sizeRamp->getValue());
		}

		if (colorRamp) {
			setColor(color::encode(colorRamp->getValue()));
		}
	}

	void Particle::update(float delta) {
		time += delta;

		if (time >= lifeTime) {
//			setVisible(false);
		}

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