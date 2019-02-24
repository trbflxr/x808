//
// Created by FLXR on 2/19/2019.
//

#ifndef X808_PARTICLE_HPP
#define X808_PARTICLE_HPP


#include <vector>
#include <xe/xeint.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>
#include <xe/timeline/ramp.hpp>

namespace xe {

	class ParticleEffect;

	class Particle : public RectangleShape {
	public:
		explicit Particle(ParticleEffect *effect);
		~Particle() override;

		void spawn(float lifeTime);

		void update(float delta);

		inline void setRotationRamp(Ramp<float> *ramp) { rotationRamp = ramp; }
		inline void setTranslationRamp(Ramp<vec2> *ramp) { translationRamp = ramp; }
		inline void setSizeRamp(Ramp<vec2> *ramp) { sizeRamp = ramp; }
		inline void setColorRamp(Ramp<vec4> *ramp) { colorRamp = ramp; }

	private:
		ParticleEffect *effect;

		float time;
		float lifeTime;

		Ramp<float> *rotationRamp;
		Ramp<vec2> *translationRamp;
		Ramp<vec2> *sizeRamp;
		Ramp<vec4> *colorRamp;
	};

}


#endif //X808_PARTICLE_HPP
