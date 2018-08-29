//
// Created by FLXR on 8/13/2018.
//

#include <xe/world/lights/pointlight.hpp>

namespace xe {

	mat4 *PointLight::rotationMatrices = nullptr;

	PointLight::PointLight(const string &id, const vec3 &color, float intensity, float falloff,
	                       bool shadow, Mesh *mesh, const mat4 &transformation) :
			Light(id, Type::Point, color, intensity, falloff, shadow, transformation, mesh) {

		if (!rotationMatrices) {
			rotationMatrices = new mat4[6];

			rotationMatrices[0] = quat::rotation(180.0f, 90.0f, 0.0f).toMatrix();
			rotationMatrices[1] = quat::rotation(180.0f, -90.0f, 0.0f).toMatrix();
			rotationMatrices[2] = quat::rotation(-90.0f, 0.0f, 0.0f).toMatrix();
			rotationMatrices[3] = quat::rotation(90.0f, 0.0f, 0.0f).toMatrix();
			rotationMatrices[4] = quat::rotation(180.0f, 0.0f, 0.0f).toMatrix();
			rotationMatrices[5] = quat::rotation(180.0f, -180.0f, 0.0f).toMatrix();
		}

		PointLight::mesh = mesh;

		const float pointRadius = falloff;
		const vec3 scaler(pointRadius, pointRadius, pointRadius);

		boundsMatrix = mat4::scale(scaler);

		perspective = mat4::perspective(90.0f, 1.0f, 0.01f, 100.0f);
	}

	std::array<mat4, 6> PointLight::getShadowViewMatrices() const {
		std::array<mat4, 6> r;

		const mat4 t = mat4::translation(-transform.getPosition());
		r[0] = t * rotationMatrices[0];
		r[1] = t * rotationMatrices[1];
		r[2] = t * rotationMatrices[2];
		r[3] = t * rotationMatrices[3];
		r[4] = t * rotationMatrices[4];
		r[5] = t * rotationMatrices[5];

		return r;
	}

	std::array<mat4, 6> PointLight::getViewRayMatrices() const {
		std::array<mat4, 6> r;
		r[0] = mat4::invert(rotationMatrices[0] * perspective);
		r[1] = mat4::invert(rotationMatrices[1] * perspective);
		r[2] = mat4::invert(rotationMatrices[2] * perspective);
		r[3] = mat4::invert(rotationMatrices[3] * perspective);
		r[4] = mat4::invert(rotationMatrices[4] * perspective);
		r[5] = mat4::invert(rotationMatrices[5] * perspective);

		return r;
	}

}