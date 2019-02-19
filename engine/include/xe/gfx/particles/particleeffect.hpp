//
// Created by FLXR on 2/19/2019.
//

#ifndef X808_PARTICLEEFFECT_HPP
#define X808_PARTICLEEFFECT_HPP


#include <vector>
#include <xe/xeint.hpp>
#include <xe/common.hpp>
#include <xe/gfx/2d/itransformable2d.hpp>
#include <xe/gfx/particles/particle.hpp>

namespace xe {

	class XE_API ParticleEffect : public ITransformable2D {
	public:
		explicit ParticleEffect(uint count, float z);
		virtual ~ParticleEffect();

		void generate();

		void update(float delta);

		inline float getZ() const { return z; }

		inline const std::vector<IRenderable2D *> &getRenderables() const { return particles; }

	private:
		uint count;
		float z;

		std::vector<IRenderable2D *> particles;
	};

}


#endif //X808_PARTICLEEFFECT_HPP
