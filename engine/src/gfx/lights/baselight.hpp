//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_BASELIGHT_HPP
#define X808_BASELIGHT_HPP


#include "gfx/shader.hpp"
#include "gfx/color.hpp"
#include "gfx/material.hpp"
#include "gfx/camera.hpp"
#include "gameobject.hpp"

namespace xe {

	struct ShadowInfo {
		mat4 projection;
		uint shadowMapSizePower2;
		bool flipFaces;
		float shadowSoftness;
		float lightBleedReduction;
		float minVariance;

		inline explicit ShadowInfo(const mat4 &projection, uint shadowMapSizePower2, bool flipFaces,
		                           float shadowSoftness = 1.0f,
		                           float lightBleedReduction = 0.2f,
		                           float minVariance = 0.00002f) :
				projection(projection),
				shadowMapSizePower2(shadowMapSizePower2),
				flipFaces(flipFaces),
				shadowSoftness(shadowSoftness),
				lightBleedReduction(lightBleedReduction),
				minVariance(minVariance) { }
	};

	class XE_API BaseLight : public GameObject, public Shader {
	protected:
		struct BaseLightStruct {
			vec4 color;
			float intensity;
		};

	public:
		~BaseLight() override;

		void unbind() const override;

		virtual void setUniforms(const Material *material, const Transform &transform, Camera *camera);

		inline bool isEnabled() const { return enabled; }
		inline void setEnabled(bool enable) { BaseLight::enabled = enable; }

		inline vec4 getColor() const { return light.color; }
		void setColor(uint color);

		inline float getIntensity() const { return light.intensity; }
		void setIntensity(float intensity);

		inline const ShadowInfo *getShadowInfo() const { return shadowInfo; }

		virtual void updateLightCamera(Camera *lightCamera, Camera *mainCamera);

	protected:
		explicit BaseLight(api::BaseShader *shader, float intensity, uint color = color::WHITE);

		void setShadowInfo(ShadowInfo *shadowInfo);

		void bindSamplers(const Material *material);
		void unbindSamplers() const;

	protected:
		bool enabled;
		BaseLightStruct light;

		ShadowInfo *shadowInfo;

	private:
		const api::Texture *diffuse;
		const api::Texture *normalMap;
		const api::Texture *dispMap;
	};

}


#endif //X808_BASELIGHT_HPP
