//
// Created by FLXR on 9/18/2018.
//

#ifndef X808_SHAPE_HPP
#define X808_SHAPE_HPP


#include <xe/gfx/2d/irenderable2d.hpp>
#include <xe/gfx/2d/itransformable2d.hpp>

namespace xe {

	class XE_API Shape : public IRenderable2D, public ITransformable2D {
	public:
		inline const Texture *getTexture() const override { return texture; }
		void setTexture(const Texture *texture);

		inline const rect &getTextureRect() const { return textureRect; }
		void setTextureRect(const rect &rect);

		inline const Vertex2D *getVertices() const override { return &vertices[0]; }
		inline const uint *getIndices() const override { return &indices[0]; }
		inline uint getIndicesCount() const override { return (uint) indices.size(); }

		inline const mat4 &getTransformation() const override { return toMatrix(); };

	protected:
		explicit Shape(float layer);

		void update();

		inline void setIndices(const std::vector<uint> &indices) { Shape::indices = indices; }

		virtual vec2 getPoint(uint index) = 0;

	private:
		void updateUVs();

	private:
		rect bounds;
		rect textureRect;

		const Texture *texture;

		std::vector<Vertex2D> vertices;
		std::vector<uint> indices;
	};

}


#endif //X808_SHAPE_HPP
