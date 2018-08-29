//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_MAT4_HPP
#define X808_MAT4_HPP


#include <xe/math/vec2.hpp>
#include <xe/math/vec3.hpp>
#include <xe/math/vec4.hpp>

namespace xe {

	struct quat;

	struct XE_API mat4 {
		union {
			// [row + col * 4]
			float elements[4 * 4];
			vec4 rows[4];
		};

		explicit mat4();
		explicit mat4(float diagonal);
		explicit mat4(float *elements);
		mat4(const mat4 &other);
		explicit mat4(const vec4 &row0, const vec4 &row1, const vec4 &row2, const vec4 &row3);

		vec4 getColumn(int index) const;
		void setColumn(int index, const vec4 &column);

		vec3 transform(const vec3 &r) const;

		mat4 &invert();

		void rotateVec(float angleDeg, const vec3 &axis);

		inline vec3 getTranslation() const { return vec3(getColumn(3)); }
		vec3 getScale() const;
		quat getRotation() const;

		mat4 clearScale() const;
		mat4 clearTranslation() const;
		mat4 clearRotation() const;

		static vec3 translateVec(const mat4 &m, const vec2 &vec);
		static vec3 translateVec(const mat4 &m, const vec3 &vec);
		static vec3 translateVec(const mat4 &m, const vec2 &vec, float z);
		static mat4 rotateMatZ(float rad);

		static mat4 initRotation(const vec3 &forward, const vec3 &up);
		static mat4 initRotation(const vec3 &forward, const vec3 &up, const vec3 &right);

		static const mat4 &identity();
		static mat4 ortho(float left, float right, float bottom, float top, float near, float far);
		static mat4 ortho(float width, float height, float near, float far);
		static mat4 perspective(float fovDeg, float aspectRatio, float near, float far);
		static mat4 lookAt(const vec3 &camera, const vec3 &object, const vec3 &up);

		static mat4 translation(const vec3 &translation);
		static mat4 rotation(float angleDeg, const vec3 &axis);
		static mat4 rotation(const quat &q);
		static mat4 scale(const vec3 &scale);
		static mat4 invert(const mat4 &m);

		static mat4 transpose(const mat4 &m);

		static mat4 transform(const vec3 &translation, const quat &rotation, const vec3 &scale);
	};

	typedef mat4 mat4;

	///----- operators -----///
	mat4 XE_API &operator*=(mat4 &left, const mat4 &right);

	inline mat4 operator*(const mat4 &left, const mat4 &right) {
		mat4 r = left;
		return r *= right;
	}

	inline vec3 operator*(const mat4 &left, const vec3 &right) {
		return right * left;
	}

	inline vec4 operator*(const mat4 &left, const vec4 &right) {
		return right * left;
	}

}


#endif //X808_MAT4_HPP
