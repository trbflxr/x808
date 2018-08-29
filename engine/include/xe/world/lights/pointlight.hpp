//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_POINTLIGHT1_HPP
#define X808_POINTLIGHT1_HPP


#include <array>
#include <xe/world/lights/light.hpp>

namespace xe {

	class XE_API PointLight : public Light {
	public:
		explicit PointLight(const string &id, const vec3 &color, float intensity, float falloff,
		           bool shadow, Mesh *mesh, const mat4 &transformation);
		~PointLight() override = default;

		inline const mat4 &getPerspective() const { return perspective; }

		std::array<mat4, 6> getShadowViewMatrices() const;
		std::array<mat4, 6> getViewRayMatrices() const;

	private:
		static mat4 *rotationMatrices;

		mat4 perspective;
	};

}


#endif //X808_POINTLIGHT1_HPP
