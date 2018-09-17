//
// Created by FLXR on 9/17/2018.
//

#include <xe/gfx/circleshape.hpp>

namespace xe {

	CircleShape::CircleShape(float radius, uint pointCount) :
			radius(radius),
			pointCount(pointCount) {

		vertices = new Vertex2D[pointCount];
		indices = new uint[pointCount + 2];
	}

	CircleShape::~CircleShape() {
		delete[] vertices;
		delete[] indices;
	}

	void CircleShape::setRadius(float radius) {
		CircleShape::radius = radius;
	}

	const Vertex2D *CircleShape::getVertices() const {
		if (isDirty()) {
			setDirty(false);

			const vec3 &pos = getPosition();

			for (uint i = 0; i < pointCount; ++i) {
				const float angle = i * 2.0f * XE_PI / pointCount - XE_PI / 2.0f;
				const float x = cosf(angle) * radius;
				const float y = sinf(angle) * radius;

				vertices[i].pos.x = radius + x;
				vertices[i].pos.y = radius + y;
				vertices[i].pos.z = pos.z;


				float tw = 0.0f;
				float th = 0.0f;

				if (texture) {
					tw = texture->getWidth();
					th = texture->getHeight();
				}

//				const float xratio = w > 0.0f ? vertices[i].pos.x / w : 0.0f;
//				const float yratio = h > 0.0f ? vertices[i].pos.y / h : 0.0f;
//				vertices[i].uv.x = 0.0f + tw * xratio;
//				vertices[i].uv.y = 0.0f + th * yratio;
			}

		}

		return vertices;
	}
}