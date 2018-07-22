//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_MATERIAL_HPP
#define X808_MATERIAL_HPP


#include "gfx/api/texture.hpp"
#include "math/math.hpp"

namespace xe { namespace gfx {

	class Material {
	public:
		explicit Material(const api::Texture *texture, uint color,
		                  float specularIntensity = 2.0f, float specularPower = 0.5f) :
				texture(texture),
				color(color),
				specularIntensity(specularIntensity),
				specularPower(specularPower) { }

		inline void bind(uint slot = 0) const { texture->bind(slot); }
		inline void unbind(uint slot = 0) const { texture->unbind(slot); }

		inline const api::Texture *getTexture() const { return texture; }
		inline void setTexture(const api::Texture *texture) { Material::texture = texture; }

		inline uint getColor() const { return color; }
		inline void setColor(uint color) { Material::color = color; }

		inline float getSpecularIntensity() const { return specularIntensity; }
		inline void setSpecularIntensity(float value) { Material::specularIntensity = value; }

		inline float getSpecularPower() const { return specularPower; }
		inline void setSpecularPower(float value) { Material::specularPower = value; }

	private:
		const api::Texture *texture;
		uint color;
		float specularIntensity;
		float specularPower;
	};

}}


#endif //X808_MATERIAL_HPP
