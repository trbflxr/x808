//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_LIGHTMANAGER_HPP
#define X808_LIGHTMANAGER_HPP


#include "light.hpp"
#include "spotlight1.hpp"
#include "pointlight1.hpp"
#include "directionallight1.hpp"
#include "gfx/api/uniformbuffer.hpp"

namespace xe {

#define MAX_SPOT_SHADOWS 4
#define MAX_POINT_SHADOWS 2
#define MAX_DIRECTIONAL_SHADOWS 1

	class XE_API LightManager {
	public:
		explicit LightManager();
		~LightManager();

		void addLight(Light *light);
		void addLights(std::vector<Light *> lights);

		void update(const vec3 &cameraPos, float delta);

		const std::vector<Light *> &getLights() const { return lights; }
		std::vector<Light *> &getLights() { return lights; }

	private:
		void updateShadowSpotUBO(SpotLight1 *light, int32 shadowId);
		void updateShadowPointUBO(PointLight1 *light, int32 shadowId);
		void updateShadowDirectionalUBO(DirectionalLight1 *light, int32 shadowId);
		void updateShadowUBO();

	private:
		int32 lightCount;

		api::UniformBuffer *shadowManifest;
		api::UniformBuffer *shadowSpot;
		api::UniformBuffer *shadowPoint;
		api::UniformBuffer *shadowDirectional;

		std::vector<vec4> lightsShadowedManifest;

		std::vector<Light *> lights;
	};

}


#endif //X808_LIGHTMANAGER_HPP
