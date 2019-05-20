//
// Created by FLXR on 5/19/2019.
//

#ifndef X808_EXAMPLESCENE_HPP
#define X808_EXAMPLESCENE_HPP


#include <xe/gfx/model.hpp>
#include <xe/gfx/light.hpp>
#include <xe/gfx/scene.hpp>
#include <xe/utils/singleton.hpp>

struct ExampleScene : xe::Singleton<ExampleScene> {
  xe::Scene *scene;

  xe::IndexedModel *im_suzanne;
  xe::IndexedModel *im_plane;
  xe::IndexedModel *im_rock;

  xe::Material *mat_pebble;
  xe::Material *mat_rock;
  xe::Material *mat_cloth;
  xe::Material *mat_bricks0;
  xe::Material *mat_bricks1;
  xe::Material *mat_bricks2;

  xe::Model *mod_rock;
  xe::Model *mod_monkey0;
  xe::Model *mod_monkey1;
  xe::Model *mod_monkey2;
  xe::Model *mod_plane0;
  xe::Model *mod_plane1;
  xe::Model *mod_plane2;
  xe::Model *mod_plane3;
  xe::Model *mod_plane4;
  xe::Model *mod_planeBot;
  xe::Model *mod_planeTop;
  xe::Model *mod_planeBack;
  xe::Model *mod_planeRight;
  xe::Model *mod_planeLeft;

  xe::SpotLight *spotLight;
  xe::PointLight *pointLight;
  xe::DirectionalLight *directionalLight;

  void create();
  void dispose();

private:
  void createModels();

  void createMaterials();

  void loadTextures();
  void loadModels();
};


#endif //X808_EXAMPLESCENE_HPP
