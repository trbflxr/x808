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
			maxTime(0.0f) {

	}

	void Particle::spawn(float maxTime) {
		setVisible(true);
		Particle::maxTime = maxTime;
		time = 0.0f;
	}

	void Particle::update(float delta) {
		time += delta;

		if (time >= maxTime) {
//			setVisible(false);
		}

//		rotate(90 * delta);


		for (auto it = positionStates.end(); it != positionStates.begin();) {
			auto &&p = (*--it);
			if (time >= p.first * maxTime) {
				setPosition(effect->getPosition() + p.second);
				break;
			}
		}

		for (auto it = rotationStates.end(); it != rotationStates.begin();) {
			auto &&p = (*--it);
			if (time >= p.first * maxTime) {
				setRotation(p.second);
				break;
			}
		}

		for (auto it = sizeStates.end(); it != sizeStates.begin();) {
			auto &&p = (*--it);
			if (time >= p.first * maxTime) {
				setSize(p.second);
				break;
			}
		}

		for (auto it = colorStates.end(); it != colorStates.begin();) {
			auto &&p = (*--it);
			if (time >= p.first * maxTime) {
				setColor(color::encode(p.second));
				break;
			}
		}


	}

	void Particle::setPositionStates(const std::vector<std::pair<float, vec2>> &states) {
		positionStates = states;
	}

	void Particle::setRotationStates(const std::vector<std::pair<float, float>> &states) {
		rotationStates = states;
	}

	void Particle::setSizeStates(const std::vector<std::pair<float, vec2>> &states) {
		sizeStates = states
	}

	void Particle::setColorStates(const std::vector<std::pair<float, vec4>> &states) {
		colorStates = states;
	}

}