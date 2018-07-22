//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_MATERIAL_HPP
#define X808_MATERIAL_HPP


#include "resources/texturemanager.hpp"
#include "gfx/api/texture.hpp"
#include "math/math.hpp"

namespace xe { namespace gfx {

	class Material {
	public:
		explicit Material(const api::Texture *texture, uint color,
		                  float specularIntensity = 2.0f, float specularPower = 0.5f,
		                  const api::Texture *normalMap = GETTEXTURE("normal")) :
				texture(texture),
				normalMap(normalMap),
				color(color),
				specularIntensity(specularIntensity),
				specularPower(specularPower) { }

		inline void bind(uint slot = 0) const {
			texture->bind(slot);
			normalMap->bind(slot + 1);
		}

		inline void unbind(uint slot = 0) const {
			texture->unbind(slot);
			normalMap->unbind(slot + 1);
		}

		inline const api::Texture *getTexture() const { return texture; }
		inline void setTexture(const api::Texture *texture) { Material::texture = texture; }

		inline const api::Texture *getNormalMap() const { return normalMap; }
		inline void setNormalMap(const api::Texture *normalMap) { Material::normalMap = normalMap; }

		inline uint getColor() const { return color; }
		inline void setColor(uint color) { Material::color = color; }

		inline float getSpecularIntensity() const { return specularIntensity; }
		inline void setSpecularIntensity(float value) { Material::specularIntensity = value; }

		inline float getSpecularPower() const { return specularPower; }
		inline void setSpecularPower(float value) { Material::specularPower = value; }

	private:
		const api::Texture *texture;
		const api::Texture *normalMap;
		uint color;
		float specularIntensity;
		float specularPower;
	};

}}


#endif //X808_MATERIAL_HPP
