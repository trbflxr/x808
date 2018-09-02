//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_DIRECTIONALLIGHT_HPP
#define X808_DIRECTIONALLIGHT_HPP

#include <xe/gfx/lights/light.hpp>

namespace xe {


	class XE_API DirectionalLight : public Light {
	public:
		explicit DirectionalLight(const string &id, bool shadow, const vec3 &position);
		~DirectionalLight() override = default;
	};

}

#endif //X808_DIRECTIONALLIGHT_HPP
