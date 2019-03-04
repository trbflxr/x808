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
		explicit Material(const string &name) :
				name(name),
				diffuseColor(0.5f),
				emission(1.0f),
				specularColor(0.1f),
				specularShininess(0.2f),
				displacementStrength(0.5f),
				diffuse(nullptr),
				specular(nullptr),
				normal(nullptr),
				displacement(nullptr),
				parallax(nullptr) { }


		inline const string &getName() const { return name; }

		inline const vec3 &getDiffuseColor() const { return diffuseColor; }
		inline void setDiffuseColor(const vec3 &color) { diffuseColor = color; }

		inline float getEmission() const { return emission; }
		inline void setEmission(float emission) { Material::emission = emission; }

		inline const vec3 &getSpecularColor() const { return specularColor; }
		inline void setSpecularColor(const vec3 &color) { specularColor = color; }

		inline float getSpecularShininess() const { return specularShininess; }
		inline void setSpecularShininess(float shininess) { specularShininess = shininess; }

		inline float getDisplacementStrength() const { return displacementStrength; }
		inline void setDisplacementStrength(float strength) { displacementStrength = strength; }

		inline const Texture *getDiffuse() const { return diffuse; }
		inline void setDiffuse(const Texture *texture) { diffuse = texture; }

		inline const Texture *getSpecular() const { return specular; }
		inline void setSpecular(const Texture *texture) { specular = texture; }

		inline const Texture *getNormal() const { return normal; }
		inline void setNormal(const Texture *texture) { normal = texture; }

		inline const Texture *getDisplacement() const { return displacement; }
		inline void setDisplacement(const Texture *texture) { displacement = texture; }

		inline const Texture *getParallax() const { return parallax; }
		inline void setParallax(const Texture *texture) { parallax = texture; }

	private:
		string name;

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
	};

}


#endif //X808_MATERIAL_HPP
