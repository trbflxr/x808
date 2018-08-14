//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_MATERIAL1_HPP
#define X808_MATERIAL1_HPP


#include <string>

#include "common.hpp"
#include "math/vec3.hpp"
#include "gfx/api/texture.hpp"

namespace xe {

	class XE_API Material1 {
	public:
		vec3 diffuseColor;
		float emission;

		vec3 specularColor;
		float specularShininess;

		float displacementStrength;

		const api::Texture *diffuse;
		const api::Texture *specular;
		const api::Texture *normal;
		const api::Texture *displacement;
		const api::Texture *parallax;

	public:
		explicit Material1(const std::string_view &id) :
				id(id),
				diffuseColor(0.5f),
				emission(0.0f),
				specularColor(1.0f),
				specularShininess(50.0f),
				displacementStrength(0.5f),
				diffuse(nullptr),
				specular(nullptr),
				normal(nullptr),
				displacement(nullptr),
				parallax(nullptr) { }

		const std::string &getId() const { return id; }

	private:
		std::string id;
	};

}


#endif //X808_MATERIAL1_HPP
