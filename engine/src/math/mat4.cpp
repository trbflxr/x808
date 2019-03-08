//
// Created by FLXR on 6/28/2018.
//

#include <cstring>
#include <xe/math/mat4.hpp>
#include <xe/math/math.hpp>

namespace xe {

	mat4::mat4() {
		memset(elements, 0, 4 * 4 * sizeof(float));
	}

	mat4::mat4(float diagonal) {
		memset(elements, 0, 4 * 4 * sizeof(float));
		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	mat4::mat4(float *elements) {
		memcpy(this->elements, elements, 4 * 4 * sizeof(float));
	}

	mat4::mat4(const mat4 &other) {
		memcpy(this->elements, other.elements, 4 * 4 * sizeof(float));
	}

	mat4::mat4(const vec4 &row0, const vec4 &row1, const vec4 &row2, const vec4 &row3) {
		rows[0] = row0;
		rows[1] = row1;
		rows[2] = row2;
		rows[3] = row3;
	}

	vec4 mat4::getColumn(int index) const {
		return vec4(elements[index + 0 * 4], elements[index + 1 * 4], elements[index + 2 * 4], elements[index + 3 * 4]);
	}

	void mat4::setColumn(int index, const vec4 &column) {
		elements[index + 0 * 4] = column.x;
		elements[index + 1 * 4] = column.y;
		elements[index + 2 * 4] = column.z;
		elements[index + 3 * 4] = column.w;
	}

	mat4 &mat4::invert() {
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

		float determinant = elements[0] * temp[0] + elements[1] * temp[4] +
		                    elements[2] * temp[8] + elements[3] * temp[12];

		determinant = 1.0f / determinant;

		for (int i = 0; i < 4 * 4; i++) {
			elements[i] = temp[i] * determinant;
		}

		return *this;
	}

	void mat4::rotateVec(float angleDeg, const vec3 &axis) {
		const float r = to_rad(angleDeg);
		const float c = cosf(r);
		const float s = sinf(r);
		const float omc = 1.0f - c;

		const float x = axis.x;
		const float y = axis.y;
		const float z = axis.z;

		elements[0 + 0 * 4] = x * x * omc + c;
		elements[0 + 1 * 4] = y * x * omc + z * s;
		elements[0 + 2 * 4] = x * z * omc - y * s;

		elements[1 + 0 * 4] = x * y * omc - z * s;
		elements[1 + 1 * 4] = y * y * omc + c;
		elements[1 + 2 * 4] = y * z * omc + x * s;

		elements[2 + 0 * 4] = x * z * omc + y * s;
		elements[2 + 1 * 4] = y * z * omc - x * s;
		elements[2 + 2 * 4] = z * z * omc + c;
	}

	vec3 mat4::getScale() const {
		vec3 temp = vec3(rows[0]);
		float s0 = vec3::length(temp);

		temp = vec3(rows[1]);
		float s1 = vec3::length(temp);

		temp = vec3(rows[2]);
		float s2 = vec3::length(temp);

		return vec3(s0, s1, s2);
	}

	quat mat4::getRotation() const {
		return quat(*this);
	}

	mat4 mat4::clearScale() const {
		mat4 m = *this;

		float r0w = m.rows[0].w;
		m.rows[0] = vec4(vec3::normalize(vec3(m.rows[0])), r0w);

		float r1w = m.rows[1].w;
		m.rows[1] = vec4(vec3::normalize(vec3(m.rows[1])), r1w);

		float r2w = m.rows[2].w;
		m.rows[2] = vec4(vec3::normalize(vec3(m.rows[2])), r2w);

		return m;
	}

	mat4 mat4::clearTranslation() const {
		mat4 m = *this;

		m.rows[0].w = 0;
		m.rows[1].w = 0;
		m.rows[2].w = 0;

		return m;
	}

	mat4 mat4::clearRotation() const {
		mat4 m = *this;

		const float x = vec3::length(vec3(m.rows[0]));
		const float y = vec3::length(vec3(m.rows[1]));
		const float z = vec3::length(vec3(m.rows[2]));

		m.rows[0].x = x;
		m.rows[0].y = 0;
		m.rows[0].z = 0;

		m.rows[1].x = 0;
		m.rows[1].y = y;
		m.rows[1].z = 0;

		m.rows[2].x = 0;
		m.rows[2].y = 0;
		m.rows[2].z = z;

		return m;
	}

	vec3 mat4::transform(const vec3 &r) const {
		return vec3(rows[0].x * r.x + rows[0].y * r.y + rows[0].z * r.z + rows[0].w,
		            rows[1].x * r.x + rows[1].y * r.y + rows[1].z * r.z + rows[1].w,
		            rows[2].x * r.x + rows[2].y * r.y + rows[2].z * r.z + rows[2].w);
	}

	mat4 mat4::rotateMatZ(float deg) {
		mat4 m = mat4::identity();

		const float s = sinf(to_rad(deg));
		const float c = cosf(to_rad(deg));

		m.rows[0].x = c;
		m.rows[0].y = -s;

		m.rows[1].x = s;
		m.rows[1].y = c;

		return m;
	}

	mat4 mat4::initRotation(const vec3 &forward, const vec3 &up) {
		vec3 f = vec3::normalize(forward);
		vec3 r = vec3::normalize(up);
		r = vec3::cross(r, f);

		vec3 u = vec3::cross(f, r);


		return initRotation(f, u, r);
	}

	mat4 mat4::initRotation(const vec3 &forward, const vec3 &up, const vec3 &right) {
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

	mat4 mat4::ortho(float left, float right, float bottom, float top, float near, float far) {
		mat4 m = mat4::identity();

		m.elements[0 + 0 * 4] = 2.0f / (right - left);
		m.elements[1 + 1 * 4] = 2.0f / (top - bottom);
		m.elements[2 + 2 * 4] = 2.0f / (near - far);

		m.elements[3 + 0 * 4] = (left + right) / (left - right);
		m.elements[3 + 1 * 4] = (bottom + top) / (bottom - top);
		m.elements[3 + 2 * 4] = (far + near) / (far - near);

		return m;
	}

	const mat4 &mat4::identity() {
		static mat4 m(1.0f);
		return m;
	}

	mat4 mat4::ortho(float width, float height, float near, float far) {
		return ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, near, far);
	}

	mat4 mat4::perspective(float fovDeg, float aspectRatio, float near, float far) {
		mat4 m = mat4::identity();

		float q = 1.0f / tanf(to_rad(0.5f * fovDeg));
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

	mat4 mat4::lookAt(const vec3 &camera, const vec3 &object, const vec3 &up) {
		mat4 m = mat4::identity();

		vec3 vec31 = vec3::normalize(camera - object);
		vec3 right = vec3::normalize(vec3::cross(up, vec31));
		vec3 vec32 = vec3::normalize(vec3::cross(vec31, right));

		m.rows[0].x = right.x;
		m.rows[0].y = vec32.x;
		m.rows[0].z = vec31.x;
		m.rows[0].w = 0.0f;
		m.rows[1].x = right.y;
		m.rows[1].y = vec32.y;
		m.rows[1].z = vec31.y;
		m.rows[1].w = 0.0f;
		m.rows[2].x = right.z;
		m.rows[2].y = vec32.z;
		m.rows[2].z = vec31.z;
		m.rows[2].w = 0.0f;
		m.rows[3].x = -(right.x * camera.x + right.y * camera.y + right.z * camera.z);
		m.rows[3].y = -(vec32.x * camera.x + vec32.y * camera.y + vec32.z * camera.z);
		m.rows[3].z = -(vec31.x * camera.x + vec31.y * camera.y + vec31.z * camera.z);
		m.rows[3].w = 1.0f;

		return m;
	}

	mat4 mat4::translation(const vec3 &translation) {
		mat4 m = mat4::identity();

		m.rows[0].w = translation.x;
		m.rows[1].w = translation.y;
		m.rows[2].w = translation.z;

		return m;
	}

	mat4 mat4::rotation(float angleDeg, const vec3 &axis) {
		mat4 m = mat4::identity();

		const float r = to_rad(angleDeg);
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

	mat4 mat4::rotation(const quat &q) {
		mat4 m = mat4::identity();

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

	mat4 mat4::scale(const vec3 &scale) {
		mat4 m = mat4::identity();

		m.elements[0 + 0 * 4] = scale.x;
		m.elements[1 + 1 * 4] = scale.y;
		m.elements[2 + 2 * 4] = scale.z;

		return m;
	}

	mat4 mat4::invert(const mat4 &m) {
		mat4 result = m;
		return result.invert();
	}

	mat4 mat4::transpose(const mat4 &m) {
		return mat4(vec4(m.rows[0].x, m.rows[1].x, m.rows[2].x, m.rows[3].x),
		            vec4(m.rows[0].y, m.rows[1].y, m.rows[2].y, m.rows[3].y),
		            vec4(m.rows[0].z, m.rows[1].z, m.rows[2].z, m.rows[3].z),
		            vec4(m.rows[0].w, m.rows[1].w, m.rows[2].w, m.rows[3].w));
	}

	mat4 mat4::transform(const vec3 &translation, const quat &rotation, const vec3 &scale) {
		const mat4 t = mat4::translation(translation);
		const mat4 r = mat4::rotation(rotation);
		const mat4 s = mat4::scale(scale);

		return t * r * s;
	}

	mat4 mat4::transform(const vec3 &translation, float rotationDeg) {
		const mat4 t = mat4::translation(translation);
		const mat4 r = mat4::rotation(rotationDeg, vec3::UnitZ());

		return t * r;
	}

	vec3 mat4::translateXY(const mat4 &mat, const vec3 &vec) {
		return vec3(mat.rows[0].x * vec.x + mat.rows[0].y * vec.y + mat.rows[0].z * vec.z + mat.rows[0].w,
		            mat.rows[1].x * vec.x + mat.rows[1].y * vec.y + mat.rows[1].z * vec.z + mat.rows[1].w,
		            vec.z);
	}

	vec3 mat4::translateXY(const mat4 &mat, const vec2 &vec) {
		return vec3(mat.rows[0].x * vec.x + mat.rows[0].y * vec.y + mat.rows[0].w,
		            mat.rows[1].x * vec.x + mat.rows[1].y * vec.y + mat.rows[1].w,
		            0.0f);
	}

	vec3 mat4::translateXY(const mat4 &mat, float x, float y) {
		return vec3(mat.rows[0].x * x + mat.rows[0].y * y + mat.rows[0].w,
		            mat.rows[1].x * x + mat.rows[1].y * y + mat.rows[1].w,
		            0.0f);
	}

	///----- operators -----///
	mat4 &operator*=(mat4 &left, const mat4 &right) {
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
}

