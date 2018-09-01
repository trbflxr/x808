//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_LIGHTMANAGER_HPP
#define X808_LIGHTMANAGER_HPP


#include <xe/common.hpp>
#include <xe/world/lights/light.hpp>

namespace xe {

	class XE_API LightManager {
	public:
		explicit LightManager();
		~LightManager();

		void addLight(Light *light);
		void addLights(std::vector<Light *> lights);

		void update(const vec3 &cameraPos, float delta) { }

		const std::vector<Light *> &getLights() const { return lights; }
		std::vector<Light *> &getLights() { return lights; }

	private:
		int32 lightCount;

		std::vector<Light *> lights;
	};

}


#endif //X808_LIGHTMANAGER_HPP
