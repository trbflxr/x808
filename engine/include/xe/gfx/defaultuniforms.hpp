//
// Created by FLXR on 8/17/2018.
//

#ifndef X808_DEFAULTUNIFORMS_HPP
#define X808_DEFAULTUNIFORMS_HPP

namespace xe {

	struct uniform {
		static constexpr const char *model = "model";
		static constexpr const char *modelNormal = "modelNormal";
		static constexpr const char *modelPrevious = "modelPrevious";

		static constexpr const char *enableDiffuseTexture = "enableDiffuseTexture";
		static constexpr const char *diffuseTexture = "diffuseTexture";
		static constexpr const char *diffuseColor = "diffuseColor";
		static constexpr const char *emission = "emissionStrength";

		static constexpr const char *enableSpecularTexture = "enableSpecularTexture";
		static constexpr const char *specularTexture = "specularTexture";
		static constexpr const char *specularColor = "specularColor";
		static constexpr const char *specularShininess = "specularShininess";

		static constexpr const char *enableNormalTexture = "enableNormalTexture";
		static constexpr const char *normalTexture = "normalTexture";

		static constexpr const char *enableDispTexture = "enableDispTexture";
		static constexpr const char *dispTexture = "dispTexture";
		static constexpr const char *displacementStrength = "displacementStrength";

		static constexpr const char *enableParallaxTexture = "enableParallaxTexture";
		static constexpr const char *parallaxTexture = "parallaxTexture";

		//light
		static constexpr const char *lightPosition = "lightPosition";
		static constexpr const char *lightDirection = "lightDirection";
		static constexpr const char *lightColor = "lightColor";
		static constexpr const char *lightIntensity = "lightIntensity";
		static constexpr const char *lightFalloff = "lightFalloff";
		static constexpr const char *lightSpotAngle = "lightSpotAngle";
		static constexpr const char *lightSpotBlur = "lightSpotBlur";

		// samplers
		static constexpr const char *samplerBase = "sampler";
	};

}

#endif //X808_DEFAULTUNIFORMS_HPP
