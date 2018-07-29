//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_BASELIGHT_HPP
#define X808_BASELIGHT_HPP


#include "gfx/forwardrenderershader.hpp"
#include "gfx/color.hpp"

namespace xe { namespace gfx {

	struct ShadowInfo {
		mat4 projection;
		float bias;
		bool flipFaces;

		inline explicit ShadowInfo(const mat4 &projection, float bias, bool flipFaces) :
				projection(projection),
				bias(bias),
				flipFaces(flipFaces) { }
	};

	class XE_API BaseLight : public GameObject, public ForwardRendererShader {
	protected:
		struct BaseLightStruct {
			vec4 color;
			float intensity;
		};

	public:
		~BaseLight();

		void setUniforms(const Material *material, const Transform &transform, const Camera *camera) override;

		void setLightMatrix(const mat4 &matrix);
		void setShadowBias(float bias);
		void setShadowTexelSize(const vec2 &texelSize);

		inline bool isEnabled() const { return enabled; }
		inline void setEnabled(bool enable) { BaseLight::enabled = enable; }

		inline vec4 getColor() const { return light.color; }
		void setColor(uint color);

		inline float getIntensity() const { return light.intensity; }
		void setIntensity(float intensity);

		inline const ShadowInfo *getShadowInfo() const { return shadowInfo; }

	protected:
		explicit BaseLight(api::Shader *shader, float intensity, uint color = color::WHITE);

		void setShadowInfo(ShadowInfo *shadowInfo);

	protected:
		bool enabled;
		BaseLightStruct light;

		ShadowInfo *shadowInfo;
	};

}}


#endif //X808_BASELIGHT_HPP
