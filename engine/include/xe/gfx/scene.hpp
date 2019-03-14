//
// Created by FLXR on 3/6/2019.
//

#ifndef X808_SCENE_HPP
#define X808_SCENE_HPP


#include <xe/gfx/model.hpp>
#include <xe/gfx/light.hpp>

namespace xe {

	class Camera;

	class XE_API Scene : NonCopyable {
	public:
		explicit Scene();
		~Scene() override;

		void add(Model *model);
		void add(Light *light);

		void updateLights(const Camera *camera);

		inline const std::vector<Model *> &getModels() const { return models; }
		inline std::vector<Model *> &getModels() { return models; }

		inline const std::vector<Light *> &getLights() const { return lights; }
		inline std::vector<Light *> &getLights() { return lights; }

		inline const std::vector<SpotLight *> &getSpotLights() const { return spotLights; }
		inline std::vector<SpotLight *> &getSpotLights() { return spotLights; }

		inline const std::vector<PointLight *> &getPointLights() const { return pointLights; }
		inline std::vector<PointLight *> &getPointLights() { return pointLights; }

		inline void setDirectionalLight(DirectionalLight *light) { directionalLight = light; }
		inline const DirectionalLight *getDirectionalLight() const { return directionalLight; }

	private:
		std::vector<Model *> models;

		std::vector<Light *> lights;
		std::vector<SpotLight *> spotLights;
		std::vector<PointLight *> pointLights;
		DirectionalLight *directionalLight;
	};

}


#endif //X808_SCENE_HPP
