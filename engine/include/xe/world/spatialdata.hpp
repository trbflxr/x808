//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_SPATIALDATA_HPP
#define X808_SPATIALDATA_HPP


#include <xe/common.hpp>
#include <xe/math/math.hpp>

namespace xe {

	struct XE_API SpatialData {
		vec3 position;
		vec3 look;
		vec3 up;
		vec3 strafe;
		vec3 scale;
		vec3 rotationAngles;

	public:
		explicit SpatialData();
		explicit SpatialData(const vec3 &position, const vec3 &look, const vec3 &up);
		explicit SpatialData(const mat4 &transformation);

		inline mat4 getPositionMatrix() const { return mat4::translation(position); }

		inline const mat4 &getRotationMatrix() const { return rotationMatrix; };
		void setRotationMatrix(const mat4 &matrix);

		inline mat4 getScaleMatrix() const { return mat4::scale(scale); }

		inline mat4 getTransformation() const { return positionMatrix * rotationMatrix; }
		void setTransformation(const mat4 &transformation);

		inline const mat4 &getModelView() const { return transformation; }

		inline const mat4 &getPerspective() const { return perspective; }

		void setPerspective(float fovDeg, float aspect, const vec2 &nearFar);
		void setPerspective(float fovDeg, float aspect, float near, float far);
		void setOrthographic(float left, float right, float bottom, float top, float near, float far);

	private:
		mat4 positionMatrix;
		mat4 rotationMatrix;

		mat4 transformation;
		mat4 perspective;
	};


}


#endif //X808_SPATIALDATA_HPP
