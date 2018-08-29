//
// Created by FLXR on 8/13/2018.
//

#include <xe/world/lights/directionallight.hpp>

namespace xe {

	DirectionalLight::DirectionalLight(const string &id, bool shadow, const vec3 &position,
	                                   const std::array<float, CASCADES + 1> &cascadeSplits) :
			Light(id, Type::Directional, vec3(1.0f), 1.0, 0.0, shadow, mat4::identity(), nullptr) {

		transform.setPosition(position);

		DirectionalLight::cascadeSplits = cascadeSplits;

		float defaultFov = 90.0f;
		float defaultAspect = 1.0f;

		for (uint i = 0; i < CASCADES; ++i) {
			float near = cascadeSplits[i];
			float far = cascadeSplits[i + 1];

			cascadePerspective[i] = mat4::perspective(defaultFov, defaultAspect, near, far);
		}
	}

	void DirectionalLight::updateCascades(const Transform &cameraTransform, const vec3 &direction) {
		std::array<mat4, CASCADES> tempView;
		std::array<mat4, CASCADES> tempOrtho;

		float cascadeBackupDistance = 20.0f;
		float shadowTextureWidth = 840.0f;

		for (uint cascade = 0; cascade < CASCADES; ++cascade) {
			const float near = cascadeSplits[cascade];
			const float far = cascadeSplits[cascade + 1];

			//create frustum
			const float frustumNear = -1.0f;
			const float frustumFar = 1.0f;

			std::array<vec3, 8> frustumCorners;
			//near
			frustumCorners[0] = vec3(-1.0f, 1.0f, frustumNear);
			frustumCorners[1] = vec3(1.0f, 1.0f, frustumNear);
			frustumCorners[2] = vec3(1.0f, -1.0f, frustumNear);
			frustumCorners[3] = vec3(-1.0f, -1.0f, frustumNear);
			//far
			frustumCorners[4] = vec3(-1.0f, 1.0f, frustumFar);
			frustumCorners[5] = vec3(1.0f, 1.0f, frustumFar);
			frustumCorners[6] = vec3(1.0f, -1.0f, frustumFar);
			frustumCorners[7] = vec3(-1.0f, -1.0f, frustumFar);

			for (auto &&c : frustumCorners) {
				c = vec3::transformPerspective(c, mat4::invert(
						cameraTransform.toMatrix() * cascadePerspective[cascade]));
			}
			//frustum corner and radius
			vec3 frustumCenter(0.0f);
			for (auto &&corner : frustumCorners) {
				frustumCenter += corner;
			}
			frustumCenter /= 8.0f;

			float radius = 0.0f;
			for (auto &&corner : frustumCorners) {
				radius = __max(vec3::length(frustumCenter - corner), radius);
			}
			radius *= 2.0f;

			//shimmering fix
			radius = floorf(radius * shadowTextureWidth) / shadowTextureWidth;

			float scaler = shadowTextureWidth / (radius * (shadowTextureWidth / 5.0f));
			frustumCenter *= scaler;
			frustumCenter.x = floorf(frustumCenter.x);
			frustumCenter.y = floorf(frustumCenter.y);
			frustumCenter.z = floorf(frustumCenter.z);
			frustumCenter /= scaler;

			//matrices
			vec3 eye = frustumCenter + (direction * (radius / 2.0f * cascadeBackupDistance));
			tempView[cascade] = mat4::lookAt(eye, frustumCenter, vec3::UnitY);
			tempOrtho[cascade] = mat4::ortho(radius, radius, cascadeSplits[0], radius * cascadeBackupDistance);
		}

		shadowView = tempView;
		shadowOrtho = tempOrtho;
	}

}
