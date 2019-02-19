//
// Created by FLXR on 2/19/2019.
//

#include <xe/gfx/particles/particle.hpp>

namespace xe {

	Particle::Particle(const vec2 &size, float layer) :
			RectangleShape(size, layer),
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
			setVisible(false);
		}

		rotate(90 * delta);
	}

}