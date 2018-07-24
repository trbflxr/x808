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
		explicit Material(const api::Texture *texture, float specularIntensity = 2.0f, float specularPower = 0.5f,
		                  const api::Texture *normalMap = GETTEXTURE("normal"),
		                  const api::Texture *dispMap = GETTEXTURE("disp"),
		                  float dispMapScale = 0.0f, float dispMapOffset = 0.0f) :
				texture(texture),
				normalMap(normalMap),
				dispMap(dispMap),
				specularIntensity(specularIntensity),
				specularPower(specularPower),
				dispMapScale(dispMapScale) {

			float baseBias = dispMapScale / 2.0f;
			dispMapBias = -baseBias + baseBias * dispMapOffset;
		}

		inline void bind(uint slot = 0) const {
			texture->bind(slot++);
			normalMap->bind(slot++);
			dispMap->bind(slot);
		}

		inline void unbind(uint slot = 0) const {
			texture->unbind(slot++);
			normalMap->unbind(slot++);
			dispMap->unbind(slot);
		}

		inline const api::Texture *getTexture() const { return texture; }
		inline void setTexture(const api::Texture *texture) { Material::texture = texture; }

		inline const api::Texture *getNormalMap() const { return normalMap; }
		inline void setNormalMap(const api::Texture *normalMap) { Material::normalMap = normalMap; }

		inline const api::Texture *getDispMap() const { return dispMap; }
		inline void setDispMap(const api::Texture *dispMap) { Material::dispMap = dispMap; }

		inline float getSpecularIntensity() const { return specularIntensity; }
		inline void setSpecularIntensity(float value) { Material::specularIntensity = value; }

		inline float getSpecularPower() const { return specularPower; }
		inline void setSpecularPower(float value) { Material::specularPower = value; }

		inline float getDispMapScale() const { return dispMapScale; }
		inline void setDispMapScale(float dispMapScale) { Material::dispMapScale = dispMapScale; }

		inline float getDispMapBias() const { return dispMapBias; }
		inline void setDispMapBias(float dispMapBias) { Material::dispMapBias = dispMapBias; }

	private:
		const api::Texture *texture;
		const api::Texture *normalMap;
		const api::Texture *dispMap;

		float specularIntensity;
		float specularPower;

		float dispMapScale;
		float dispMapBias;
	};

}}


#endif //X808_MATERIAL_HPP
