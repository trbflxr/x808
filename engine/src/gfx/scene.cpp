//
// Created by FLXR on 3/6/2019.
//

#include <algorithm>
#include <xe/gfx/scene.hpp>

namespace xe {

  Scene::Scene() :
      directionalLight(nullptr) { }

  Scene::~Scene() {
    for (const auto &m : models) {
      delete m;
    }

    for (const auto &l : lights) {
      delete l;
    }

    delete directionalLight;
  }

  void Scene::add(Model *model) {
    models.push_back(model);
  }

  void Scene::add(Light *light) {
    lights.push_back(light);

    switch (light->getType()) {
      case LightType::Spot: {
        spotLights.push_back(dynamic_cast<SpotLight *>(light));
        break;
      }

      case LightType::Point: {
        pointLights.push_back(dynamic_cast<PointLight *>(light));
        break;
      }

      default: break;
    }
  }

  Model *Scene::removeModel(const string &name) {
    auto it = std::find_if(models.begin(), models.end(), [&](const Model *x) { return x->getName() == name; });
    if (it != models.end()) {
      models.erase(it);
      return *it;
    }

    return nullptr;
  }

  Light *Scene::removeLight(const string &name) {
    auto it = std::find_if(lights.begin(), lights.end(), [&](const Light *x) { return x->getName() == name; });
    if (it != lights.end()) {
      lights.erase(it);

      if ((*it)->getType() == LightType::Spot) {
        auto s = std::find_if(spotLights.begin(), spotLights.end(),
                              [&](const Light *x) { return x->getName() == name; });
        if (s != spotLights.end()) {
          spotLights.erase(s);
        }
      } else if ((*it)->getType() == LightType::Point) {
        auto s = std::find_if(pointLights.begin(), pointLights.end(),
                              [&](const Light *x) { return x->getName() == name; });
        if (s != pointLights.end()) {
          pointLights.erase(s);
        }
      }

      return *it;
    }

    return nullptr;
  }

  void Scene::updateLights(const Camera *camera) {
    //todo: sort lights and frustum culling
  }

}
