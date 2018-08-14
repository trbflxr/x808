//
// Created by FLXR on 8/13/2018.
//

#include "directionallight1.hpp"

namespace xe {

	DirectionalLight1::DirectionalLight1(const std::string_view &id, bool shadow, const vec3 &position,
	                                     const std::array<float, CASCADES + 1> &cascadeSplits) :
			Light(id, Type::Directional, vec3(1.0f), 1.0, 0.0, shadow, mat4(1.0f)) {

		spatial.position = position;

		DirectionalLight1::cascadeSplits = cascadeSplits;

		float defaultFov = 90.0f;
		float defaultAspect = 1.0f;

		for (uint i = 0; i < CASCADES; ++i) {
			float near = cascadeSplits[i];
			float far = cascadeSplits[i + 1];

			cascadePerspective[i] = mat4::perspective(defaultFov, defaultAspect, near, far);
		}
	}

	void DirectionalLight1::updateCascades(const SpatialData &cameraSpatial, const vec3 &direction) {
		std::array<mat4, CASCADES> tempView;
		std::array<mat4, CASCADES> tempOrtho;

		float cascadeBackupDistance = 20.0f;
		float shadowTextureWidth = 840.0f;

		for (uint cascade = 0; cascade < CASCADES; ++cascade) {
			float near = cascadeSplits[cascade];
			float far = cascadeSplits[cascade + 1];

			//create frustum
			float frustumNear = -1.0f;
			float frustumFar = 1.0f;

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
						cameraSpatial.getModelView() * cascadePerspective[cascade]));
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
			tempView[cascade] = mat4::lookAt(eye, frustumCenter, vec3::YAXIS);
			tempOrtho[cascade] = mat4::ortho(radius, radius, cascadeSplits[0], radius * cascadeBackupDistance);
		}

		shadowView = tempView;
		shadowOrtho = tempOrtho;
	}

}
