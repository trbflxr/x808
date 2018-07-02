//
// Created by FLXR on 6/28/2018.
//

#include <cstring>
#include "mat4.hpp"
#include "math.hpp"

xe::math::mat4::mat4() {
	memset(elements, 0, 4 * 4 * sizeof(float));
}

xe::math::mat4::mat4(float diagonal) {
	memset(elements, 0, 4 * 4 * sizeof(float));
	elements[0 + 0 * 4] = diagonal;
	elements[1 + 1 * 4] = diagonal;
	elements[2 + 2 * 4] = diagonal;
	elements[3 + 3 * 4] = diagonal;
}

xe::math::mat4::mat4(float *elements) {
	memcpy(this->elements, elements, 4 * 4 * sizeof(float));
}

xe::math::mat4::mat4(const xe::mat4 &other) {
	memcpy(this->elements, other.elements, 4 * 4 * sizeof(float));
}

xe::math::mat4::mat4(const vec4 &row0, const vec4 &row1, const vec4 &row2, const vec4 &row3) {
	rows[0] = row0;
	rows[1] = row1;
	rows[2] = row2;
	rows[3] = row3;
}

xe::math::vec4 xe::mat4::getColumn(int index) const {
	return vec4(elements[index + 0 * 4], elements[index + 1 * 4], elements[index + 2 * 4],
	            elements[index + 3 * 4]);
}

void xe::math::mat4::setColumn(int index, const vec4 &column) {
	elements[index + 0 * 4] = column.x;
	elements[index + 1 * 4] = column.y;
	elements[index + 2 * 4] = column.z;
	elements[index + 3 * 4] = column.w;
}

xe::mat4 &xe::math::mat4::invert() {
	float temp[16];

	temp[0] = elements[5] * elements[10] * elements[15] -
	          elements[5] * elements[11] * elements[14] -
	          elements[9] * elements[6] * elements[15] +
	          elements[9] * elements[7] * elements[14] +
	          elements[13] * elements[6] * elements[11] -
	          elements[13] * elements[7] * elements[10];

	temp[4] = -elements[4] * elements[10] * elements[15] +
	          elements[4] * elements[11] * elements[14] +
	          elements[8] * elements[6] * elements[15] -
	          elements[8] * elements[7] * elements[14] -
	          elements[12] * elements[6] * elements[11] +
	          elements[12] * elements[7] * elements[10];

	temp[8] = elements[4] * elements[9] * elements[15] -
	          elements[4] * elements[11] * elements[13] -
	          elements[8] * elements[5] * elements[15] +
	          elements[8] * elements[7] * elements[13] +
	          elements[12] * elements[5] * elements[11] -
	          elements[12] * elements[7] * elements[9];

	temp[12] = -elements[4] * elements[9] * elements[14] +
	           elements[4] * elements[10] * elements[13] +
	           elements[8] * elements[5] * elements[14] -
	           elements[8] * elements[6] * elements[13] -
	           elements[12] * elements[5] * elements[10] +
	           elements[12] * elements[6] * elements[9];

	temp[1] = -elements[1] * elements[10] * elements[15] +
	          elements[1] * elements[11] * elements[14] +
	          elements[9] * elements[2] * elements[15] -
	          elements[9] * elements[3] * elements[14] -
	          elements[13] * elements[2] * elements[11] +
	          elements[13] * elements[3] * elements[10];

	temp[5] = elements[0] * elements[10] * elements[15] -
	          elements[0] * elements[11] * elements[14] -
	          elements[8] * elements[2] * elements[15] +
	          elements[8] * elements[3] * elements[14] +
	          elements[12] * elements[2] * elements[11] -
	          elements[12] * elements[3] * elements[10];

	temp[9] = -elements[0] * elements[9] * elements[15] +
	          elements[0] * elements[11] * elements[13] +
	          elements[8] * elements[1] * elements[15] -
	          elements[8] * elements[3] * elements[13] -
	          elements[12] * elements[1] * elements[11] +
	          elements[12] * elements[3] * elements[9];

	temp[13] = elements[0] * elements[9] * elements[14] -
	           elements[0] * elements[10] * elements[13] -
	           elements[8] * elements[1] * elements[14] +
	           elements[8] * elements[2] * elements[13] +
	           elements[12] * elements[1] * elements[10] -
	           elements[12] * elements[2] * elements[9];

	temp[2] = elements[1] * elements[6] * elements[15] -
	          elements[1] * elements[7] * elements[14] -
	          elements[5] * elements[2] * elements[15] +
	          elements[5] * elements[3] * elements[14] +
	          elements[13] * elements[2] * elements[7] -
	          elements[13] * elements[3] * elements[6];

	temp[6] = -elements[0] * elements[6] * elements[15] +
	          elements[0] * elements[7] * elements[14] +
	          elements[4] * elements[2] * elements[15] -
	          elements[4] * elements[3] * elements[14] -
	          elements[12] * elements[2] * elements[7] +
	          elements[12] * elements[3] * elements[6];

	temp[10] = elements[0] * elements[5] * elements[15] -
	           elements[0] * elements[7] * elements[13] -
	           elements[4] * elements[1] * elements[15] +
	           elements[4] * elements[3] * elements[13] +
	           elements[12] * elements[1] * elements[7] -
	           elements[12] * elements[3] * elements[5];

	temp[14] = -elements[0] * elements[5] * elements[14] +
	           elements[0] * elements[6] * elements[13] +
	           elements[4] * elements[1] * elements[14] -
	           elements[4] * elements[2] * elements[13] -
	           elements[12] * elements[1] * elements[6] +
	           elements[12] * elements[2] * elements[5];

	temp[3] = -elements[1] * elements[6] * elements[11] +
	          elements[1] * elements[7] * elements[10] +
	          elements[5] * elements[2] * elements[11] -
	          elements[5] * elements[3] * elements[10] -
	          elements[9] * elements[2] * elements[7] +
	          elements[9] * elements[3] * elements[6];

	temp[7] = elements[0] * elements[6] * elements[11] -
	          elements[0] * elements[7] * elements[10] -
	          elements[4] * elements[2] * elements[11] +
	          elements[4] * elements[3] * elements[10] +
	          elements[8] * elements[2] * elements[7] -
	          elements[8] * elements[3] * elements[6];

	temp[11] = -elements[0] * elements[5] * elements[11] +
	           elements[0] * elements[7] * elements[9] +
	           elements[4] * elements[1] * elements[11] -
	           elements[4] * elements[3] * elements[9] -
	           elements[8] * elements[1] * elements[7] +
	           elements[8] * elements[3] * elements[5];

	temp[15] = elements[0] * elements[5] * elements[10] -
	           elements[0] * elements[6] * elements[9] -
	           elements[4] * elements[1] * elements[10] +
	           elements[4] * elements[2] * elements[9] +
	           elements[8] * elements[1] * elements[6] -
	           elements[8] * elements[2] * elements[5];

	float determinant =
			elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[8] + elements[3] * temp[12];
	determinant = 1.0f / determinant;

	for (int i = 0; i < 4 * 4; i++) {
		elements[i] = temp[i] * determinant;
	}

	return *this;
}

xe::vec3 xe::math::mat4::transform(const vec3 &r) const {
	return vec3(rows[0].x * r.x + rows[0].y * r.y + rows[0].z * r.z + rows[0].w,
	            rows[1].x * r.x + rows[1].y * r.y + rows[1].z * r.z + rows[1].w,
	            rows[2].x * r.x + rows[2].y * r.y + rows[2].z * r.z + rows[2].w);
}

xe::vec3 xe::math::translateVec(const mat4 &m, const vec2 &vec) {
	return vec3(m.rows[0].x * vec.x + m.rows[1].x * vec.y + m.rows[3].x,
	            m.rows[0].y * vec.x + m.rows[1].y * vec.y + m.rows[3].y,
	            m.rows[0].z * vec.x + m.rows[1].z * vec.y + m.rows[3].z);
}

xe::vec3 xe::math::translateVec(const mat4 &m, const vec3 &vec) {
	return vec3(m.rows[0].x * vec.x + m.rows[1].x * vec.y + m.rows[2].x * vec.z + m.rows[3].x,
	            m.rows[0].y * vec.x + m.rows[1].y * vec.y + m.rows[2].y * vec.z + m.rows[3].y,
	            m.rows[0].z * vec.x + m.rows[1].z * vec.y + m.rows[2].z * vec.z + m.rows[3].z);
}

xe::mat4 xe::math::rotateMatZ(float rad) {
	mat4 m(1.0f);

	const float s = sinf(rad);
	const float c = cosf(rad);

	m.rows[0].x = c;
	m.rows[0].y = -s;

	m.rows[1].x = s;
	m.rows[1].y = c;

	return m;
}

xe::math::mat4 xe::math::initRotation(const vec3 &forward, const vec3 &up) {
	vec3 f = math::normalize(forward);
	vec3 r = math::normalize(up);
	r = math::cross(r, f);

	vec3 u = math::cross(f, r);


	return initRotation(f, u, r);
}

xe::math::mat4 xe::math::initRotation(const vec3 &forward, const vec3 &up, const vec3 &right) {
	mat4 res(1.0f);

	res.rows[0].x = right.x;
	res.rows[0].y = right.y;
	res.rows[0].z = right.z;

	res.rows[1].x = up.x;
	res.rows[1].y = up.y;
	res.rows[1].z = up.z;

	res.rows[2].x = forward.x;
	res.rows[2].y = forward.y;
	res.rows[2].z = forward.z;

	return res;
}

xe::mat4 xe::math::ortho(float left, float right, float bottom, float top, float near, float far) {
	mat4 m(1.0f);

	m.elements[0 + 0 * 4] = 2.0f / (right - left);
	m.elements[1 + 1 * 4] = 2.0f / (top - bottom);
	m.elements[2 + 2 * 4] = 2.0f / (near - far);

	m.elements[3 + 0 * 4] = (left + right) / (left - right);
	m.elements[3 + 1 * 4] = (bottom + top) / (bottom - top);
	m.elements[3 + 2 * 4] = (far + near) / (far - near);

	return m;
}

xe::mat4 xe::math::perspective(float fov, float aspectRatio, float near, float far) {
	mat4 m(1.0f);

	float q = 1.0f / tanf(to_rad(0.5f * fov));
	float a = q / aspectRatio;

	float b = (near + far) / (near - far);
	float c = (2.0f * near * far) / (near - far);

	m.elements[0 + 0 * 4] = a;
	m.elements[1 + 1 * 4] = q;
	m.elements[2 + 2 * 4] = b;
	m.elements[2 + 3 * 4] = -1.0f;
	m.elements[3 + 2 * 4] = c;

	return m;
}

xe::mat4 xe::math::lookAt(const xe::vec3 &camera, const xe::vec3 &object, const xe::vec3 &up) {
	mat4 m(1.0f);
	vec3 f = normalize((object - camera));
	vec3 s = cross(f, normalize(up));;
	vec3 u = cross(s, f);

	m.elements[0 + 0 * 4] = s.x;
	m.elements[0 + 1 * 4] = s.y;
	m.elements[0 + 2 * 4] = s.z;

	m.elements[1 + 0 * 4] = u.x;
	m.elements[1 + 1 * 4] = u.y;
	m.elements[1 + 2 * 4] = u.z;

	m.elements[2 + 0 * 4] = -f.x;
	m.elements[2 + 1 * 4] = -f.y;
	m.elements[2 + 2 * 4] = -f.z;

	return m * translate(vec3(-camera.x, -camera.y, -camera.z));
}

xe::mat4 xe::math::translate(const xe::vec3 &translation) {
	mat4 m(1.0f);

	m.elements[3 + 0 * 4] = translation.x;
	m.elements[3 + 1 * 4] = translation.y;
	m.elements[3 + 2 * 4] = translation.z;

	return m;
}

xe::mat4 xe::math::rotate(float angle, const xe::vec3 &axis) {
	mat4 m(1.0f);

	const float r = to_rad(angle);
	const float c = cosf(r);
	const float s = sinf(r);
	const float omc = 1.0f - c;

	const float x = axis.x;
	const float y = axis.y;
	const float z = axis.z;

	m.elements[0 + 0 * 4] = x * x * omc + c;
	m.elements[0 + 1 * 4] = y * x * omc + z * s;
	m.elements[0 + 2 * 4] = x * z * omc - y * s;

	m.elements[1 + 0 * 4] = x * y * omc - z * s;
	m.elements[1 + 1 * 4] = y * y * omc + c;
	m.elements[1 + 2 * 4] = y * z * omc + x * s;

	m.elements[2 + 0 * 4] = x * z * omc + y * s;
	m.elements[2 + 1 * 4] = y * z * omc - x * s;
	m.elements[2 + 2 * 4] = z * z * omc + c;

	return m;
}

xe::mat4 xe::math::rotate(const xe::quat &q) {
	mat4 m(1.0f);

	float qx, qy, qz, qw, qx2, qy2, qz2, qxqx2, qyqy2, qzqz2, qxqy2, qyqz2, qzqw2, qxqz2, qyqw2, qxqw2;
	qx = q.x;
	qy = q.y;
	qz = q.z;
	qw = q.w;
	qx2 = (qx + qx);
	qy2 = (qy + qy);
	qz2 = (qz + qz);
	qxqx2 = (qx * qx2);
	qxqy2 = (qx * qy2);
	qxqz2 = (qx * qz2);
	qxqw2 = (qw * qx2);
	qyqy2 = (qy * qy2);
	qyqz2 = (qy * qz2);
	qyqw2 = (qw * qy2);
	qzqz2 = (qz * qz2);
	qzqw2 = (qw * qz2);

	m.rows[0] = vec4(((1.0f - qyqy2) - qzqz2), (qxqy2 - qzqw2), (qxqz2 + qyqw2), 0.0f);
	m.rows[1] = vec4((qxqy2 + qzqw2), ((1.0f - qxqx2) - qzqz2), (qyqz2 - qxqw2), 0.0f);
	m.rows[2] = vec4((qxqz2 - qyqw2), (qyqz2 + qxqw2), ((1.0f - qxqx2) - qyqy2), 0.0f);

	return m;
}

xe::mat4 xe::math::scale(const xe::vec3 &scale) {
	mat4 m(1.0f);

	m.elements[0 + 0 * 4] = scale.x;
	m.elements[1 + 1 * 4] = scale.y;
	m.elements[2 + 2 * 4] = scale.z;

	return m;
}

xe::mat4 xe::math::invert(const xe::mat4 &m) {
	mat4 result = m;
	return result.invert();
}

xe::mat4 xe::math::transpose(const xe::mat4 &m) {
	return mat4(
			vec4(m.rows[0].x, m.rows[1].x, m.rows[2].x, m.rows[3].x),
			vec4(m.rows[0].y, m.rows[1].y, m.rows[2].y, m.rows[3].y),
			vec4(m.rows[0].z, m.rows[1].z, m.rows[2].z, m.rows[3].z),
			vec4(m.rows[0].w, m.rows[1].w, m.rows[2].w, m.rows[3].w));
}


xe::mat4 &xe::math::operator*=(mat4 &left, const mat4 &right) {
	float data[16];
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			float sum = 0.0f;
			for (int e = 0; e < 4; e++) {
				sum += left.elements[e + row * 4] * right.elements[col + e * 4];
			}
			data[col + row * 4] = sum;
		}
	}
	memcpy(left.elements, data, 4 * 4 * sizeof(float));
	return left;
}

xe::mat4 xe::math::operator*(const xe::mat4 &left, const xe::mat4 &right) {
	mat4 r = left;
	return r *= right;
}

xe::vec3 xe::math::operator*(const xe::mat4 &left, const xe::vec3 &right) {
	return right * left;
}

xe::vec4 xe::math::operator*(const xe::mat4 &left, const xe::vec4 &right) {
	return right * left;
}

