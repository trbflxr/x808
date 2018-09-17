//
// Created by FLXR on 9/17/2018.
//

#ifndef X808_CIRCLESHAPE_HPP
#define X808_CIRCLESHAPE_HPP


#include <xe/gfx/2d/irenderable2d.hpp>
#include <xe/gfx/2d/itransformable2d.hpp>

namespace xe {

	class XE_API CircleShape : public IRenderable2D, public ITransformable2D {
	public:
		explicit CircleShape(float radius, uint pointCount = 30);
		~CircleShape() override;

		inline float getRadius() const { return radius; }
		inline void setRadius(float radius);

		inline uint getVerticesSize() const override { return pointCount; }
		const Vertex2D *getVertices() const override;

		inline uint getIndicesSize() const override { return pointCount + 2; }
		inline const uint *getIndices() const override { return indices; }

		inline float getZ() const override { return getPosition().z; }

	private:
		float radius;
		uint pointCount;

		mutable Vertex2D *vertices;
		uint *indices;
	};

}


#endif //X808_CIRCLESHAPE_HPP
