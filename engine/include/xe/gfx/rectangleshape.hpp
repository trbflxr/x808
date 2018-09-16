//
// Created by FLXR on 9/13/2018.
//

#ifndef X808_RECTANGLESHAPE_HPP
#define X808_RECTANGLESHAPE_HPP


#include <xe/gfx/2d/irenderable2d.hpp>
#include <xe/gfx/2d/itransformable2d.hpp>

namespace xe {

	class XE_API RectangleShape : public IRenderable2D, public ITransformable2D {
	public:
		explicit RectangleShape(const vec2 &size);
		~RectangleShape() override;

		inline const vec2 &getSize() const { return size; }
		inline void setSize(const vec2 &size) { RectangleShape::size = size; }

		inline uint getVerticesSize() const override { return 4; }
		const Vertex2D *getVertices() const override;

		inline uint getIndicesSize() const override { return 6; }
		inline const uint *getIndices() const override { return indices; }

		inline float getZ() const override { return getPosition().z; }

	private:
		vec2 size;

		mutable Vertex2D *vertices;
		uint *indices;
	};

}


#endif //X808_RECTANGLESHAPE_HPP
