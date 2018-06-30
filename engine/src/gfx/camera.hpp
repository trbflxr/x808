//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_CAMERA_HPP
#define X808_CAMERA_HPP


#include "common.hpp"
#include "math/math.hpp"

namespace xe {namespace gfx {

	class XE_API Camera {
	public:
		explicit Camera(const mat4 &projection) : projectionMatrix(projection), viewMatrix(1.0f) { }

		virtual void focus() { }
		virtual void update() { }

		inline const vec3 &getPosition() const { return position; }
		inline void setPosition(const vec3 &position) { Camera::position = position; }

		inline const vec3 &getRotation() const { return rotation; }
		inline void setRotation(const vec3 &rotation) { Camera::rotation = rotation; }

		inline const mat4 &getProjectionMatrix() const { return projectionMatrix; }
		inline void setProjectionMatrix(const mat4 &matrix) { Camera::projectionMatrix = matrix; }

		inline const vec3 &getFocalPoint() const { return focalPoint; }
		inline const mat4 &getViewMatrix() const { return viewMatrix; }

		inline void translate(const vec3 &translation) { position += translation; }
		inline void translate(float x, float y, float z) { position += {x, y, z}; }

		inline void rotate(const vec3 &rotation) { Camera::rotation += rotation; }
		inline void rotate(float x, float y, float z) { rotation += {x, y, z}; }

	protected:
		mat4 projectionMatrix;
		mat4 viewMatrix;

		vec3 position;
		vec3 rotation;
		vec3 focalPoint;
	};

}}


#endif //X808_CAMERA_HPP
