//
// Created by FLXR on 2/19/2019.
//

#ifndef X808_PARTICLE_HPP
#define X808_PARTICLE_HPP


#include <xe/gfx/rectangleshape.hpp>

namespace xe {

	class Particle : public RectangleShape {
	public:
		explicit Particle(const vec2 &size, float layer);

		void spawn(float maxTime);

		void update(float delta);

	private:
		float time;
		float maxTime;

		//todo: multiple states
		vec2 targetPos;
		float targetRot;
		float targetScale;
	};

}


#endif //X808_PARTICLE_HPP
