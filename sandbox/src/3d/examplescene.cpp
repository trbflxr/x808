//
// Created by FLXR on 5/19/2019.
//

#include <xe/resources/texturemanager.hpp>
#include <xe/loaders/modelloader.hpp>
#include "examplescene.hpp"

using namespace xe;

void ExampleScene::create() {
  scene = new Scene();

  loadTextures();
  loadModels();

  createMaterials();
  createModels();
}

void ExampleScene::dispose() {
  delete im_suzanne;
  delete im_rock;
  delete im_plane;

  delete scene;

  delete mat_pebble;
  delete mat_rock;
  delete mat_cloth;
  delete mat_bricks0;
  delete mat_bricks1;
  delete mat_bricks2;
}

void ExampleScene::createModels() {
  mod_rock = new Model("mod_rock", *im_rock);
  mod_rock->setMaterial(mat_bricks0);
  scene->add(mod_rock);

  mod_monkey0 = new Model("mod_monkey0", *im_suzanne);
  mod_monkey0->setMaterial(mat_cloth);
  mod_monkey0->setPosition({-5.0f, -7, 5});
  scene->add(mod_monkey0);

  mod_monkey1 = new Model("mod_monkey1", *im_suzanne);
  mod_monkey1->setMaterial(mat_cloth);
  mod_monkey1->setPosition({-2.3f, -7, 5});
  scene->add(mod_monkey1);

  mod_monkey2 = new Model("mod_monkey2", *im_suzanne);
  mod_monkey2->setMaterial(mat_cloth);
  mod_monkey2->setPosition({0.6f, -7, 5});
  scene->add(mod_monkey2);

  mod_plane0 = new Model("mod_plane0", *im_plane);
  mod_plane0->setMaterial(mat_bricks1);
  mod_plane0->setPosition({0, -10, 0});
  mod_plane0->rotate(vec3::UnitY(), 180.0f);
  scene->add(mod_plane0);

  mod_plane1 = new Model("mod_plane1", *im_plane);
  mod_plane1->setMaterial(mat_rock);
  mod_plane1->setPosition({16.5f, -10, 0});
  scene->add(mod_plane1);

  mod_plane2 = new Model("mod_plane2", *im_plane);
  mod_plane2->setMaterial(mat_bricks2);
  mod_plane2->setPosition({33, -10, 0});
  scene->add(mod_plane2);

  mod_plane3 = new Model("mod_plane3", *im_plane);
  mod_plane3->setMaterial(mat_pebble);
  mod_plane3->setPosition({0, -10, 16.5f});
  scene->add(mod_plane3);

  mod_plane4 = new Model("mod_plane4", *im_plane);
  mod_plane4->setMaterial(mat_cloth);
  mod_plane4->setPosition({16.5f, -10, 16.5f});
  scene->add(mod_plane4);

  mod_planeBot = new Model("mod_planeBot", *im_plane);
  mod_planeBot->setMaterial(mat_bricks0);
  mod_planeBot->setPosition({-16.5f, -10, 0});
  scene->add(mod_planeBot);

  mod_planeTop = new Model("mod_planeTop", *im_plane);
  mod_planeTop->setMaterial(mat_bricks0);
  mod_planeTop->setPosition({-16.5f, 6.0f, 0});
  scene->add(mod_planeTop);

  mod_planeBack = new Model("mod_planeBack", *im_plane);
  mod_planeBack->setMaterial(mat_bricks0);
  mod_planeBack->setPosition({-16.5f, -2.0f, -8.0f});
  mod_planeBack->rotate(vec3::UnitX(), 90);
  scene->add(mod_planeBack);

  mod_planeRight = new Model("mod_planeRight", *im_plane);
  mod_planeRight->setMaterial(mat_bricks0);
  mod_planeRight->setPosition({-8.45f, -2.0f, 0});
  mod_planeRight->rotate(vec3::UnitZ(), 90);
  scene->add(mod_planeRight);

  mod_planeLeft = new Model("mod_planeLeft", *im_plane);
  mod_planeLeft->setMaterial(mat_bricks0);
  mod_planeLeft->setPosition({-24.55f, -2.0f, 0});
  mod_planeLeft->rotate(vec3::UnitZ(), 90);
  scene->add(mod_planeLeft);

  //lights
  directionalLight = new DirectionalLight("directionalLight", {15.0f, 30.0f, 50.0f, 100.0f});
  directionalLight->rotate(vec3::UnitX(), -35.0f);
  directionalLight->rotate(vec3::UnitY(), -10.0f);
  directionalLight->setColor({0.068f, 0.111f, 0.190f});
  directionalLight->setIntensity(5.0f);
  scene->setDirectionalLight(directionalLight);

  spotLight = new SpotLight("spotLight");
  spotLight->setPosition({6.3f, 2.8f, -0.8});
  spotLight->rotate(vec3::UnitY(), 90);
  spotLight->setColor({0.068f, 0.111f, 0.190f});
  spotLight->setSpotAngle(48.0f);
  spotLight->setSpotBlur(0.08f);
  spotLight->setIntensity(15.5f);
  spotLight->setFalloff(22.0f);
  spotLight->setShadowed(true);
  scene->add(spotLight);

  pointLight = new PointLight("pointLight");
  pointLight->setPosition({8, -5, 8});
  pointLight->setColor({0.945f, 0.217f, 0.032f});
  pointLight->setIntensity(22.0f);
  pointLight->setFalloff(14.0f);
  scene->add(pointLight);
}

void ExampleScene::createMaterials() {
  mat_pebble = new Material("pebble");
  mat_pebble->setHeightScale(0.03f);
  mat_pebble->setDiffuse(GETTEXTURE("pebble_d"));
  mat_pebble->setNormalMap(GETTEXTURE("pebble_n"));
  mat_pebble->setHeightMap(GETTEXTURE("pebble_h"));

  mat_rock = new Material("rock");
  mat_rock->setDiffuse(GETTEXTURE("r031_color"));
  mat_rock->setNormalMap(GETTEXTURE("r031_norm"));
  mat_rock->setHeightMap(GETTEXTURE("r031_disp"));

  mat_cloth = new Material("cloth");
  mat_cloth->setDiffuse(GETTEXTURE("cloth_diffuse"));
  mat_cloth->setNormalMap(GETTEXTURE("cloth_normal"));

  mat_bricks0 = new Material("bricks0");
  mat_bricks0->setSpecularShininess(0.15f);
  mat_bricks0->setDiffuse(GETTEXTURE("diffuse"));
  mat_bricks0->setSpecularMap(GETTEXTURE("specular"));

  mat_bricks1 = new Material("bricks1");
  mat_bricks1->setSpecularShininess(0.02f);
  mat_bricks1->setDiffuse(GETTEXTURE("brick1_d"));
  mat_bricks1->setNormalMap(GETTEXTURE("brick1_n"));
  mat_bricks1->setHeightMap(GETTEXTURE("brick1_h"));
  mat_bricks1->setSpecularMap(GETTEXTURE("brick1_s"));

  mat_bricks2 = new Material("bricks2");
  mat_bricks2->setDiffuse(GETTEXTURE("bricks2_d"));
  mat_bricks2->setNormalMap(GETTEXTURE("bricks2_n"));
  mat_bricks2->setHeightMap(GETTEXTURE("bricks2_h"));
}

void ExampleScene::loadTextures() {
  TextureParameters params;
  TextureManager::add(new Texture("diffuse", "sponza_floor_diff.jpg", params));
  TextureManager::add(new Texture("specular", "sponza_floor_spec.jpg", params));

  TextureManager::add(new Texture("cloth_diffuse", "Fabric_Padded_diffuse.jpg", params));
  TextureManager::add(new Texture("cloth_normal", "Fabric_Padded_normal.jpg", params));

  TextureManager::add(new Texture("r031_color", "Rock_031_COLOR.jpg", params));
  TextureManager::add(new Texture("r031_norm", "Rock_031_NORM.jpg", params));
  TextureManager::add(new Texture("r031_disp", "Rock_031_DISP.png", params));

  TextureManager::add(new Texture("brick1_d", "brick1-d.jpg", params));
  TextureManager::add(new Texture("brick1_n", "brick1-n.jpg", params));
  TextureManager::add(new Texture("brick1_h", "brick1-h.jpg", params));
  TextureManager::add(new Texture("brick1_s", "brick1-s.jpg", params));

  TextureManager::add(new Texture("bricks2_d", "bricks.jpg", params));
  TextureManager::add(new Texture("bricks2_n", "bricksNormal.jpg", params));
  TextureManager::add(new Texture("bricks2_h", "bricksDisp.png", params));

  TextureManager::add(new Texture("pebble_d", "pebble.bmp", params));
  TextureManager::add(new Texture("pebble_n", "pebble-n.bmp", params));
  TextureManager::add(new Texture("pebble_h", "pebble-h.bmp", params));
}

void ExampleScene::loadModels() {
  im_suzanne = ModelLoader::loadIndexedModel("monkey3.obj");
  im_rock = ModelLoader::loadIndexedModel("rock.obj");
  im_plane = ModelLoader::loadIndexedModel("plane0.obj");
}
