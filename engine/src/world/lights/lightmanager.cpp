//
// Created by FLXR on 8/13/2018.
//

#include <xe/gfx/uniformbuffer.hpp>
#include <xe/world/lights/lightmanager.hpp>

namespace xe {

	LightManager::LightManager() :
			lightCount(0) {

		BufferLayout shadowLayout;
		shadowLayout.push<vec4>("info");
		shadowManifest = new UniformBuffer(BufferStorage::Dynamic, 3, shadowLayout, 32);

		BufferLayout shadowSpotLayout;
		shadowSpotLayout.push<mat4>("view");
		shadowSpotLayout.push<mat4>("perspective");
		shadowSpotLayout.push<mat4>("viewray");
		shadowSpotLayout.push<vec4>("pos-falloff");
		shadowSpotLayout.push<vec4>("color-intensity");
		shadowSpotLayout.push<vec4>("direction");
		shadowSpotLayout.push<vec4>("spotAngle-spotBlur");
		shadowSpot = new UniformBuffer(BufferStorage::Dynamic, 4, shadowSpotLayout, 32);

		BufferLayout shadowPointLayout;
		shadowPointLayout.push<mat4>("view0");
		shadowPointLayout.push<mat4>("view1");
		shadowPointLayout.push<mat4>("view2");
		shadowPointLayout.push<mat4>("view3");
		shadowPointLayout.push<mat4>("view4");
		shadowPointLayout.push<mat4>("view5");
		shadowPointLayout.push<mat4>("perspective");
		shadowPointLayout.push<mat4>("viewray0");
		shadowPointLayout.push<mat4>("viewray1");
		shadowPointLayout.push<mat4>("viewray2");
		shadowPointLayout.push<mat4>("viewray3");
		shadowPointLayout.push<mat4>("viewray4");
		shadowPointLayout.push<mat4>("viewray5");
		shadowPointLayout.push<vec4>("pos-falloff");
		shadowPointLayout.push<vec4>("color-intensity");
		shadowPoint = new UniformBuffer(BufferStorage::Dynamic, 5, shadowPointLayout, 32);

		BufferLayout shadowDirectionalLayout;
		shadowDirectionalLayout.push<mat4>("view0");
		shadowDirectionalLayout.push<mat4>("view1");
		shadowDirectionalLayout.push<mat4>("view2");
		shadowDirectionalLayout.push<mat4>("view3");
		shadowDirectionalLayout.push<mat4>("perspective0");
		shadowDirectionalLayout.push<mat4>("perspective1");
		shadowDirectionalLayout.push<mat4>("perspective2");
		shadowDirectionalLayout.push<mat4>("perspective3");
		shadowDirectionalLayout.push<vec4>("lightPos");
		shadowDirectional = new UniformBuffer(BufferStorage::Dynamic, 6, shadowDirectionalLayout, 1);
	}

	LightManager::~LightManager() {
		delete shadowManifest;
		delete shadowSpot;
		delete shadowPoint;
		delete shadowDirectional;

		for (auto &&light : lights) {
			delete light;
		}
	}

	void LightManager::addLight(Light *light) {
		light->id = lightCount;
		light->enabled = true;

		lights.push_back(light);
		++lightCount;
	}

	void LightManager::addLights(std::vector<Light *> lights) {
		for (auto &&light : lights) {
			addLight(light);
		}
	}

	void LightManager::update(const vec3 &cameraPos, float delta) {
		lightsShadowedManifest.clear();
		updateShadowUBO();
	}

	void LightManager::updateShadowSpotUBO(SpotLight *light, int32 shadowId) {
		mat4 svm = light->getShadowViewMatrix();
		mat4 spm = light->getShadowPerspectiveMatrix();
		mat4 vrm = light->getViewRayMatrix();

		vec4 pf(light->spatial.position, light->falloff);
		vec4 ci(light->color, light->intensity);
		vec4 look(light->spatial.look, 0.0f);
		vec4 sasb(light->spotAngle, light->spotBlur, 0.0f, 0.0f);

		shadowSpot->update(&svm, 0, 0);
		shadowSpot->update(&spm, 1, 0);
		shadowSpot->update(&vrm, 2, 0);
		shadowSpot->update(&pf, 3, 0);
		shadowSpot->update(&ci, 4, 0);
		shadowSpot->update(&look, 5, 0);
		shadowSpot->update(&sasb, 6, 0);

		light->shadowId = shadowId;
	}

	void LightManager::updateShadowPointUBO(PointLight *light, int32 shadowId) {
		for (uint i = 0; i < 6; ++i) {
			shadowPoint->update(&light->getShadowViewMatrices()[i], i, 0);
			shadowPoint->update(&light->getViewRayMatrices()[i], i + 7, 0);
		}
		vec4 pf(light->spatial.position, light->falloff);
		vec4 ci(light->color, light->intensity);

		shadowPoint->update(&light->spatial.getPerspective(), 6, 0);
		shadowPoint->update(&pf, 13, 0);
		shadowPoint->update(&ci, 14, 0);

		light->shadowId = shadowId;
	}

	void LightManager::updateShadowDirectionalUBO(DirectionalLight1 *light, int32 shadowId) {
		for (uint i = 0; i < 4; ++i) {
			shadowDirectional->update(&light->getShadowViewMatrices()[i], i, 0);
			shadowDirectional->update(&light->getShadowOrthoMatrices()[i], i + 4, 0);
		}
		shadowDirectional->update(&light->spatial.position, 8, 0);

		light->shadowId = shadowId;
	}

	void LightManager::updateShadowUBO() {
		uint numShadowsSpot = 0;
		uint numShadowsPoint = 0;
		uint numShadowsDirectional = 0;

		for (auto &&light : lights) {
			if (!light->shadowed) continue;

			switch (light->type) {
				case Light::Type::Spot: {
					if (numShadowsSpot >= MAX_SPOT_SHADOWS) break;
					updateShadowSpotUBO(dynamic_cast<SpotLight *>(light), numShadowsSpot);
					lightsShadowedManifest.emplace_back(0, numShadowsSpot, 0, 0);
					++numShadowsSpot;
					break;
				}

				case Light::Type::Point: {
					if (numShadowsPoint >= MAX_POINT_SHADOWS) break;
					updateShadowPointUBO(dynamic_cast<PointLight *>(light), numShadowsPoint);
					lightsShadowedManifest.emplace_back(1, numShadowsPoint, 0, 0);
					lightsShadowedManifest.emplace_back(1, numShadowsPoint, 1, 0);
					lightsShadowedManifest.emplace_back(1, numShadowsPoint, 2, 0);
					lightsShadowedManifest.emplace_back(1, numShadowsPoint, 3, 0);
					lightsShadowedManifest.emplace_back(1, numShadowsPoint, 4, 0);
					lightsShadowedManifest.emplace_back(1, numShadowsPoint, 5, 0);
					++numShadowsPoint;
					break;
				}

				case Light::Type::Directional: {
					if (numShadowsDirectional >= MAX_DIRECTIONAL_SHADOWS) break;
					updateShadowDirectionalUBO(dynamic_cast<DirectionalLight1 *>(light), numShadowsDirectional);
					lightsShadowedManifest.emplace_back(2, numShadowsDirectional, 0, 0);
					++numShadowsDirectional;
					break;
				}
			}
		}

		size_t shadowManifestSize = lightsShadowedManifest.size();
		for (uint i = 0; i < 32; ++i) {
			vec4 temp(-1.0f);
			if (i < shadowManifestSize) temp = lightsShadowedManifest[i];
			shadowManifest->update(&temp, 0, i);
		}
	}

}
