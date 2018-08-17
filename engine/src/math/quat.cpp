//
// Created by FLXR on 6/28/2018.
//

#include <xe/math/quat.hpp>
#include <xe/math/math.hpp>

namespace xe {

	float norm(const quat &q) {
		float result = (q.x * q.x);
		result = (result + (q.y * q.y));
		result = (result + (q.z * q.z));
		result = (result + (q.w * q.w));
		return result;
	}

	float length(const quat &q) {
		return sqrtf(norm(q));
	}

	quat::quat() : x(0), y(0), z(0), w(1) { }
	quat::quat(const xe::quat &q) : x(q.x), y(q.y), z(q.z), w(q.w) { }
	quat::quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
	quat::quat(const vec4 &vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) { }
	quat::quat(float scalar) : x(scalar), y(scalar), z(scalar), w(scalar) { }

	quat::quat(const vec3 &axis, float angleDeg) {
		float sinHalfAngle = sinf(to_rad(angleDeg) / 2.0f);
		float cosHalfAngle = cosf(to_rad(angleDeg) / 2.0f);

		x = axis.x * sinHalfAngle;
		y = axis.y * sinHalfAngle;
		z = axis.z * sinHalfAngle;
		w = cosHalfAngle;
	}

	quat::quat(const xe::mat4 &rot) {
		float trace = rot.rows[0].x + rot.rows[1].y + rot.rows[2].z;

		if (trace > 0) {
			float s = 0.5f / sqrtf(trace + 1.0f);
			w = 0.25f / s;
			x = (rot.rows[1].z - rot.rows[2].y) * s;
			y = (rot.rows[2].x - rot.rows[0].z) * s;
			z = (rot.rows[0].y - rot.rows[1].x) * s;
		} else {
			if (rot.rows[0].x > rot.rows[1].y && rot.rows[0].x > rot.rows[2].z) {
				float s = 2.0f * sqrtf(1.0f + rot.rows[0].x - rot.rows[1].y - rot.rows[2].z);
				w = (rot.rows[1].z - rot.rows[2].y) / s;
				x = 0.25f * s;
				y = (rot.rows[1].x + rot.rows[0].y) / s;
				z = (rot.rows[2].x + rot.rows[0].z) / s;
			} else if (rot.rows[1].y > rot.rows[2].z) {
				float s = 2.0f * sqrtf(1.0f + rot.rows[1].y - rot.rows[0].x - rot.rows[2].z);
				w = (rot.rows[2].x - rot.rows[0].z) / s;
				x = (rot.rows[1].x + rot.rows[0].y) / s;
				y = 0.25f * s;
				z = (rot.rows[2].y + rot.rows[1].z) / s;
			} else {
				float s = 2.0f * sqrtf(1.0f + rot.rows[2].z - rot.rows[0].x - rot.rows[1].y);
				w = (rot.rows[0].y - rot.rows[1].x) / s;
				x = (rot.rows[2].x + rot.rows[0].z) / s;
				y = (rot.rows[1].z + rot.rows[2].y) / s;
				z = 0.25f * s;
			}
		}

		float length = sqrtf(x * x + y * y + z * z + w * w);
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	xe::vec3 quat::getAxis() const {
		float x = 1.0f - w * w;
		if (x < 0.0000001f) return vec3::XAXIS;

		float x2 = x * x;
		return vec3(x, y, z) / x2;
	}

	xe::vec3 quat::toEulerAngles() const {
		return vec3(atan2f(2 * x * w - 2 * y * z, 1 - 2 * x * x - 2 * z * z),
		            atan2f(2 * y * w - 2 * x * z, 1 - 2 * y * y - 2 * z * z),
		            asinf(2 * x * y + 2 * z * w));
	}

	xe::mat4 quat::toRotationMatrix() const {
		vec3 forward(2.0f * (x * z - w * y), 2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
		vec3 up(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - w * x));
		vec3 right(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - w * z), 2.0f * (x * z + w * y));

		return mat4::initRotation(forward, up, right);
	}

	vec3 quat::getForward() const {
		return vec3(0, 0, -1).rotate(*this);
	}

	vec3 quat::getBackward() const {
		return vec3(0, 0, 1).rotate(*this);
	}

	vec3 quat::getUp() const {
		return vec3(0, 1, 0).rotate(*this);
	}

	vec3 quat::getDown() const {
		return vec3(0, -1, 0).rotate(*this);
	}

	vec3 quat::getRight() const {
		return vec3(1, 0, 0).rotate(*this);
	}

	vec3 quat::getLeft() const {
		return vec3(-1, 0, 0).rotate(*this);
	}

	float quat::length(const quat &q) {
		return sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	}

	quat quat::normalize(const quat &q) {
		float l = length(q);
		return quat(q.x / l, q.y / l, q.z / l, q.w / l);
	}

	float quat::dot(const quat &left, const quat &right) {
		float result = (left.x * right.x);
		result = (result + (left.y * right.y));
		result = (result + (left.z * right.z));
		result = (result + (left.w * right.w));
		return result;
	}

	quat quat::conjugate(const quat &q) {
		return quat(-q.x, -q.y, -q.z, q.w);
	}

	vec3 quat::rotate(const quat &q, const vec3 &vec) {
		const float tmpX = (((q.w * vec.x) + (q.y * vec.z)) - (q.z * vec.y));
		const float tmpY = (((q.w * vec.y) + (q.z * vec.x)) - (q.x * vec.z));
		const float tmpZ = (((q.w * vec.z) + (q.x * vec.y)) - (q.y * vec.x));
		const float tmpW = (((q.x * vec.x) + (q.y * vec.y)) + (q.z * vec.z));

		return vec3(((((tmpW * q.x) + (tmpX * q.w)) - (tmpY * q.z)) + (tmpZ * q.y)),
		            ((((tmpW * q.y) + (tmpY * q.w)) - (tmpZ * q.x)) + (tmpX * q.z)),
		            ((((tmpW * q.z) + (tmpZ * q.w)) - (tmpX * q.y)) + (tmpY * q.x)));
	}

	quat quat::rotation(const vec3 &unitVec0, const vec3 &unitVec1) {
		const float cosHalfAngleX2 = sqrtf((2.0f * (1.0f + vec3::dot(unitVec0, unitVec1))));
		const float recipCosHalfAngleX2 = (1.0f / cosHalfAngleX2);
		return quat((vec3::cross(unitVec0, unitVec1) * recipCosHalfAngleX2), (cosHalfAngleX2 * 0.5f));
	}

	quat quat::rotation(float angleDeg, const vec3 &unitVec) {
		const float angle = to_rad(angleDeg) * 0.5f;
		return quat((unitVec * sinf(angle)), cosf(angle));
	}

	quat quat::rotation(const vec3 &anglesDeg) {
		quat r;
		if (anglesDeg.x) r *= quat(vec3::XAXIS, anglesDeg.x);
		if (anglesDeg.y) r *= quat(vec3::YAXIS, anglesDeg.y);
		if (anglesDeg.z) r *= quat(vec3::ZAXIS, anglesDeg.z);

		return quat::normalize(r);
	}

	quat quat::rotationX(float angleDeg) {
		const float angle = to_rad(angleDeg) * 0.5f;
		return quat(sinf(angle), 0.0f, 0.0f, cosf(angle));
	}

	quat quat::rotationY(float angleDeg) {
		const float angle = to_rad(angleDeg) * 0.5f;
		return quat(0.0f, sinf(angle), 0.0f, cosf(angle));
	}

	quat quat::rotationZ(float angleDeg) {
		const float angle = to_rad(angleDeg) * 0.5f;
		return quat(0.0f, 0.0f, sinf(angle), cosf(angle));
	}


	///operators
	quat operator+(const quat &left, const quat &right) {
		return quat(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
	}

	quat operator-(const quat &left, const quat &right) {
		return quat(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
	}

	quat operator*(const quat &left, const quat &right) {
		const float w = (left.w * right.w) - (left.x * right.x) - (left.y * right.y) - (left.z * right.z);
		const float x = (left.x * right.w) + (left.w * right.x) + (left.y * right.z) - (left.z * right.y);
		const float y = (left.y * right.w) + (left.w * right.y) + (left.z * right.x) - (left.x * right.z);
		const float z = (left.z * right.w) + (left.w * right.z) + (left.x * right.y) - (left.y * right.x);

		return quat(x, y, z, w);
	}

	quat operator*(const quat &left, float right) {
		return quat(left.x * right, left.y * right, left.z * right, left.w * right);
	}

	quat operator*(const quat &left, const vec3 &right) {
		const float w = -(left.x * right.x) - (left.y * right.y) - (left.z * right.z);
		const float x = (left.w * right.x) + (left.y * right.z) - (left.z * right.y);
		const float y = (left.w * right.y) + (left.z * right.x) - (left.x * right.z);
		const float z = (left.w * right.z) + (left.x * right.y) - (left.y * right.x);

		return quat(x, y, z, w);
	}

	quat operator/(const quat &left, float right) {
		return quat(left.x / right, left.y / right, left.z / right, left.w / right);
	}

	quat operator+=(quat &left, const quat &right) {
		left = left + right;
		return left;
	}

	quat operator-=(quat &left, const quat &right) {
		left = left - right;
		return left;
	}

	quat operator*=(quat &left, const quat &right) {
		left = left * right;
		return left;
	}

	quat operator*=(quat &left, float right) {
		left = left * right;
		return left;
	}

	quat operator*=(quat &left, const vec3 &right) {
		left = left * right;
		return left;
	}

	quat operator/=(quat &left, float right) {
		left = left / right;
		return left;
	}

}