//
// Created by FLXR on 9/18/2018.
//

#ifndef X808_POLYGON_HPP
#define X808_POLYGON_HPP


#include <xe/math/rect.hpp>
#include <xe/gfx/2d/irenderable2d.hpp>
#include <xe/math/itransformable2d.hpp>

namespace xe {

	class XE_API Polygon : public IRenderable2D, public ITransformable2D {
	public:
		explicit Polygon();
		explicit Polygon(const std::vector<vec2> &points);

		void reshape(const std::vector<vec2> &points);

		inline bool isPointsChanged() const { return pointsChanged; }
		inline void setPointsChanged(bool changed) { Polygon::pointsChanged = changed; }

		inline const rect &getTextureRect() const { return textureRect; }
		void setTextureRect(const rect &rect);

		inline const Texture *getTexture() const override { return texture; }
		void setTexture(const Texture *texture);

		inline const Vertex2D *getVertices() const override { return vertices.data(); }
		inline uint getPointCount() const override { return (uint) points.size(); }

		inline uint getIndicesCount() const override { return (uint) indices.size(); }
		inline const uint *getIndices() const override { return indices.data(); }

		inline const vec2 *getRawPoints() const { return points.data(); }

		inline const mat4 &getTransformation() const override { return toMatrix(); }

	private:
		void create();
		void updateUVs();

	private:
		std::vector<vec2> points;
		bool pointsChanged;

		const Texture *texture;
		rect textureRect;

		std::vector<Vertex2D> vertices;
		std::vector<uint> indices;
	};

}


#endif //X808_POLYGON_HPP
