//
// Created by FLXR on 8/13/2018.
//

#include <xe/world/lights/directionallight.hpp>

namespace xe {

	DirectionalLight::DirectionalLight(const string &id, bool shadow, const vec3 &position) :
			Light(id, Type::Directional, vec3(1.0f), 1.0, 0.0, shadow, mat4::identity(), nullptr) {

		transform.setPosition(position);
	}

}
