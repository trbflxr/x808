//
// Created by FLXR on 2/19/2019.
//

#ifndef X808_PARTICLE_HPP
#define X808_PARTICLE_HPP


#include <vector>
#include <xe/xeint.hpp>
#include <xe/gfx/rectangleshape.hpp>

namespace xe {

	class ParticleEffect;

	class Particle : public RectangleShape {
	public:
		explicit Particle(ParticleEffect *effect, float layer);

		void spawn(float maxTime);

		void update(float delta);

		void setPositionStates(const std::vector<std::pair<float, vec2>> &states);
		void setRotationStates(const std::vector<std::pair<float, float>> &states);
		void setSizeStates(const std::vector<std::pair<float, vec2>> &states);
		void setColorStates(const std::vector<std::pair<float, vec4>> &states);

	private:
		ParticleEffect *effect;

		float time;
		float maxTime;

		std::vector<std::pair<float, vec2>> positionStates;
		std::vector<std::pair<float, float>> rotationStates;
		std::vector<std::pair<float, vec2>> sizeStates;
		std::vector<std::pair<float, vec4>> colorStates;

	};

}


#endif //X808_PARTICLE_HPP
