//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_SPOTLIGHT1_HPP
#define X808_SPOTLIGHT1_HPP


#include <xe/world/lights/light.hpp>

namespace xe {

	class XE_API SpotLight : public Light {
	public:
		float spotAngle;
		float spotBlur;

	public:
		explicit SpotLight(const string &id, const vec3 &color, float intensity, float falloff,
		                   float spotAngle, float spotBlur, bool shadow, Mesh *mesh, const mat4 &transformation);
		~SpotLight() override = default;

		inline const mat4 &getPerspective() const { return perspective; }

		inline mat4 getShadowViewMatrix() const {
			return mat4::translation(-transform.getPosition()) * mat4::transpose(transform.getRotation().toMatrix());
		}

		inline mat4 getViewRayMatrix() const {
			return mat4::invert(getShadowViewMatrix().clearTranslation() * perspective);
		}

	private:
		mat4 perspective;
	};

}


#endif //X808_SPOTLIGHT1_HPP
