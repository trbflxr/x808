//
// Created by FLXR on 3/2/2019.
//

#ifndef X808_MATERIAL_HPP
#define X808_MATERIAL_HPP


#include <xe/gfx/texture.hpp>
#include <xe/math/vec3.hpp>

namespace xe {

	class Material {
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
		explicit Material(const string &name) :
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
				name(name) { }

		const string &getName() const { return name; }

	private:
		string name;
	};

}


#endif //X808_MATERIAL_HPP
