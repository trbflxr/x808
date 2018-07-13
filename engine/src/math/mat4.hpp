//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_MAT4_HPP
#define X808_MAT4_HPP


#include "common.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

namespace xe {
	namespace math {

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

			inline vec3 getPosition() const { return vec3(getColumn(3)); }
			inline void setPosition(const vec3 &position) { setColumn(3, vec4(position, 1.0f)); }

			vec3 transform(const vec3 &r) const;

			mat4 &invert();

			static inline mat4 transform(const vec3 &translation, const quat &rotation, const vec3 &scale);
		};

		XE_API vec3 translateVec(const mat4 &m, const vec2 &vec);
		XE_API vec3 translateVec(const mat4 &m, const vec3 &vec);
		XE_API vec3 translateVec(const mat4 &m, const vec2 &vec, float z);
		XE_API mat4 rotateMatZ(float rad);

		XE_API mat4 initRotation(const vec3 &forward, const vec3 &up);
		XE_API mat4 initRotation(const vec3 &forward, const vec3 &up, const vec3 &right);

		XE_API mat4 ortho(float left, float right, float bottom, float top, float near, float far);
		XE_API mat4 perspective(float fov, float aspectRatio, float near, float far);
		XE_API mat4 lookAt(const vec3 &camera, const vec3 &object, const vec3 &up);

		XE_API mat4 translate(const vec3 &translation);
		XE_API mat4 rotate(float angle, const vec3 &axis);
		XE_API mat4 rotate(const quat &q);
		XE_API mat4 scale(const vec3 &scale);
		XE_API mat4 invert(const mat4 &m);

		XE_API mat4 transpose(const mat4 &m);

		XE_API mat4 &operator*=(mat4 &left, const mat4 &right);
		XE_API mat4 operator*(const mat4 &left, const mat4 &right);
		XE_API vec3 operator*(const mat4 &left, const vec3 &right);
		XE_API vec4 operator*(const mat4 &left, const vec4 &right);

		inline mat4 math::mat4::transform(const vec3 &translation, const quat &rotation, const vec3 &scale) {
			mat4 t = math::translate(translation);
			mat4 r = math::rotate(rotation);
			mat4 s = math::scale(scale);

			return t * r * s;
		}
	}
	typedef math::mat4 mat4;
}


#endif //X808_MAT4_HPP
