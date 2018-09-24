//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_MATERIAL1_HPP
#define X808_MATERIAL1_HPP


#include <string>

#include <xe/common.hpp>
#include <xe/math/vec3.hpp>
#include <xe/gfx/texture.hpp>

namespace xe {

	class XE_API Material {
	public:
		vec3 diffuseColor;
		float emission;

		vec3 specularColor;
		float specularShininess;

		float displacementStrength;

		const Texture *diffuse;
		const Texture *specular;
		const Texture *normal;
		const Texture *displacement;
		const Texture *parallax;

	public:
		explicit Material(const string &id) :
				diffuseColor(0.5f),
				emission(0.0f),
				specularColor(1.0f),
				specularShininess(50.0f),
				displacementStrength(0.5f),
				diffuse(nullptr),
				specular(nullptr),
				normal(nullptr),
				displacement(nullptr),
				parallax(nullptr),
				id(id) { }

		const string &getId() const { return id; }

	private:
		string id;
	};

}


#endif //X808_MATERIAL1_HPP
