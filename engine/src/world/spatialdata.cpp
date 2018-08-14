//
// Created by FLXR on 8/13/2018.
//

#include "spatialdata.hpp"

namespace xe {

	SpatialData::SpatialData() :
			scale(vec3(1.0f, 1.0f, 1.0f)) { }

	SpatialData::SpatialData(const vec3 &position, const vec3 &look, const vec3 &up) :
			position(position),
			look(look),
			up(up),
			scale(vec3(1.0f, 1.0f, 1.0f)) { }

	SpatialData::SpatialData(const mat4 &transformation) {
		setTransformation(transformation);
	}

	void SpatialData::setRotationMatrix(const mat4 &matrix) {
		rotationMatrix = matrix;

		look = vec3(rotationMatrix.rows[2]);
		up = vec3(rotationMatrix.rows[1]);
		strafe = vec3(rotationMatrix.rows[0]);
	}

	void SpatialData::setTransformation(const mat4 &transformation) {
		position = transformation.getTranslation();
		scale = transformation.getScale();
		rotationMatrix = quat(transformation).toRotationMatrix();
	}

	void SpatialData::setPerspective(float fovDeg, float aspect, const vec2 &nearFar) {
		perspective = mat4::perspective(fovDeg, aspect, nearFar.x, nearFar.y);
	}

	void SpatialData::setPerspective(float fovDeg, float aspect, float near, float far) {
		perspective = mat4::perspective(fovDeg, aspect, near, far);
	}

	void SpatialData::setOrthographic(float left, float right, float bottom, float top, float near, float far) {
		perspective = mat4::ortho(left, right, bottom, top, near, far);
	}

}