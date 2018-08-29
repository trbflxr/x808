//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_DIRECTIONALLIGHT_HPP
#define X808_DIRECTIONALLIGHT_HPP


#include <array>
#include <vector>
#include <xe/world/lights/light.hpp>

namespace xe {

#define CASCADES 4

	class XE_API DirectionalLight : public Light {
	public:
		explicit DirectionalLight(const string &id, bool shadow, const vec3 &position,
		                           const std::array<float, CASCADES + 1> &cascadeSplits);

		void updateCascades(const Transform &cameraTransform, const vec3 &direction);

		const std::array<mat4, 4> &getShadowViewMatrices() const { return shadowView; }
		const std::array<mat4, 4> &getShadowOrthoMatrices() const { return shadowOrtho; }

	private:
		std::array<mat4, CASCADES> shadowView;
		std::array<mat4, CASCADES> shadowOrtho;

		std::array<mat4, CASCADES> cascadePerspective;
		std::array<float, CASCADES + 1> cascadeSplits;
	};

}

#endif //X808_DIRECTIONALLIGHT_HPP
