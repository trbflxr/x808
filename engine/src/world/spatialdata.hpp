//
// Created by FLXR on 8/10/2018.
//

#ifndef X808_SPATIALDATA_HPP
#define X808_SPATIALDATA_HPP


#include "common.hpp"
#include "math/math.hpp"

namespace xe {

	class XE_API SpatialData {
	public:
		explicit SpatialData();
		explicit SpatialData(const vec3 &position, const vec3 &look, const vec3 &up);
		explicit SpatialData(const mat4 &transformation);

		inline const vec3 &getPosition() const { return position; }
		inline void setPosition(const vec3 &position) { SpatialData::position = position; }
		inline void move(const vec3 &direction) { position += direction; }

		inline const vec3 &getLook() const { return look; }
		inline void setLook(const vec3 &look) { SpatialData::look = look; }

		inline const vec3 &getUp() const { return up; }
		inline void setUp(const vec3 &up) { SpatialData::up = up; }

		inline const vec3 &getStrafe() const { return strafe; }
		inline void setStrafe(const vec3 &strafe) { SpatialData::strafe = strafe; }

		inline const vec3 &getScale() const { return scale; }
		inline void setScale(const vec3 &scale) { SpatialData::scale = scale; }

		inline const vec3 &getRotationAngles() const { return rotationAngles; }
		inline void setRotationAngles(const vec3 &angles) { SpatialData::rotationAngles = angles; }

		inline const mat4 &getPositionMatrix() const { mat4::translation(position); }

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
		vec3 position;
		vec3 look;
		vec3 up;
		vec3 strafe;
		vec3 scale;
		vec3 rotationAngles;

		mat4 positionMatrix;
		mat4 rotationMatrix;

		mat4 transformation;
		mat4 perspective;
	};

}


#endif //X808_SPATIALDATA_HPP
