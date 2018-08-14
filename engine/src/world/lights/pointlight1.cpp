//
// Created by FLXR on 8/13/2018.
//

#include "pointlight1.hpp"

namespace xe {

	mat4 *PointLight1::rotationMatrices = nullptr;

	PointLight1::PointLight1(const std::string_view &id, const vec3 &color, float intensity, float falloff,
	                         bool shadow, Mesh1 *mesh, const mat4 &transformation) :
			Light(id, Type::Point, color, intensity, falloff, shadow, transformation) {

		if (!rotationMatrices) {
			rotationMatrices = new mat4[6];

			rotationMatrices[0] = quat::rotation({180.0f, 90.0f, 0.0f}).toRotationMatrix();
			rotationMatrices[1] = quat::rotation({180.0f, -90.0f, 0.0f}).toRotationMatrix();
			rotationMatrices[2] = quat::rotation({-90.0f, 0.0f, 0.0f}).toRotationMatrix();
			rotationMatrices[3] = quat::rotation({90.0f, 0.0f, 0.0f}).toRotationMatrix();
			rotationMatrices[4] = quat::rotation({180.0f, 0.0f, 0.0f}).toRotationMatrix();
			rotationMatrices[5] = quat::rotation({180.0f, -180.0f, 0.0f}).toRotationMatrix();
		}

		PointLight1::mesh = new UniqueMesh(id, mesh, transformation);

		float pointRadius = falloff;
		vec3 scaler(pointRadius, pointRadius, pointRadius);

		boundsMatrix = mat4::scale(scaler);
		mat4 t = boundsMatrix * transformation.clearScale();

		std::string boundsId(id);
		boundsId.append("-bounds");
		boundingMesh = new UniqueMesh(boundsId, mesh, t);

		spatial.setPerspective(90.0f, 1.0f, 0.1f, 100.0f);
	}

	mat4 PointLight1::getShadowPerspectiveMatrix() const {
		return spatial.getPerspective();
	}

	std::array<mat4, 6> PointLight1::getShadowViewMatrices() const {
		std::array<mat4, 6> r;
		r[0] = mat4::translation(-spatial.position) * rotationMatrices[0];
		r[1] = mat4::translation(-spatial.position) * rotationMatrices[1];
		r[2] = mat4::translation(-spatial.position) * rotationMatrices[2];
		r[3] = mat4::translation(-spatial.position) * rotationMatrices[3];
		r[4] = mat4::translation(-spatial.position) * rotationMatrices[4];
		r[5] = mat4::translation(-spatial.position) * rotationMatrices[5];

		return r;
	}

	std::array<mat4, 6> PointLight1::getViewRayMatrices() const {
		std::array<mat4, 6> r;
		r[0] = mat4::invert(rotationMatrices[0] * getShadowPerspectiveMatrix());
		r[1] = mat4::invert(rotationMatrices[1] * getShadowPerspectiveMatrix());
		r[2] = mat4::invert(rotationMatrices[2] * getShadowPerspectiveMatrix());
		r[3] = mat4::invert(rotationMatrices[3] * getShadowPerspectiveMatrix());
		r[4] = mat4::invert(rotationMatrices[4] * getShadowPerspectiveMatrix());
		r[5] = mat4::invert(rotationMatrices[5] * getShadowPerspectiveMatrix());

		return r;
	}

}