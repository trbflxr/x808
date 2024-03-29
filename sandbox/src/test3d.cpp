//
// Created by FLXR on 3/1/2019.
//

#include "test3d.hpp"
#include <xe/gfx/renderer.hpp>
#include <xe/resources/texturemanager.hpp>
#include <xe/ui/imgui/imgui.h>

using namespace xe;

Test3D::Test3D() {
  const float width = app.getWindowSize().x;
  const float height = app.getWindowSize().y;

  camera = new Camera(mat4::perspective(60.0f, width / height, 0.1f, 1000.0f));
  camera->setPosition({4.0f, 3.0f, 20.0f});

  ShadowParameters sp(app.getConfig(), 512, 1024);

  renderer = new DeferredRenderer(width, height, camera, sp, fx::AOType::Hbao);
  renderer->enableLightObjects(true);
  renderer->enableLightBounds(true);

  TextureParameters params;
  TextureManager::add(new Texture("diffuse", "sponza_floor_diff.jpg", params));
  TextureManager::add(new Texture("specular", "sponza_floor_spec.jpg", params));

  TextureManager::add(new Texture("diffuse1", "Fabric_Padded_diffuse.jpg", params));
  TextureManager::add(new Texture("normal1", "Fabric_Padded_normal.jpg", params));

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

  scene = new Scene();

  material = new Material("material");
  material->setDiffuse(GETTEXTURE("diffuse"));
  material->setSpecularMap(GETTEXTURE("specular"));
  material->setSpecularShininess(0.15f);

  material1 = new Material("material1");
  material1->setDiffuse(GETTEXTURE("diffuse1"));
  material1->setNormalMap(GETTEXTURE("normal1"));

  disp = new Material("disp");
  disp->setDiffuse(GETTEXTURE("r031_color"));
  disp->setNormalMap(GETTEXTURE("r031_norm"));
  disp->setHeightMap(GETTEXTURE("r031_disp"));

  parallax = new Material("parallax");
  parallax->setSpecularShininess(0.02f);
  parallax->setDiffuse(GETTEXTURE("brick1_d"));
  parallax->setNormalMap(GETTEXTURE("brick1_n"));
  parallax->setHeightMap(GETTEXTURE("brick1_h"));
  parallax->setSpecularMap(GETTEXTURE("brick1_s"));

  bricks = new Material("bricks");
  bricks->setDiffuse(GETTEXTURE("bricks2_d"));
  bricks->setNormalMap(GETTEXTURE("bricks2_n"));
  bricks->setHeightMap(GETTEXTURE("bricks2_h"));

  pebble = new Material("pebble");
  pebble->setHeightScale(0.03f);
  pebble->setDiffuse(GETTEXTURE("pebble_d"));
  pebble->setNormalMap(GETTEXTURE("pebble_n"));
  pebble->setHeightMap(GETTEXTURE("pebble_h"));

  model = new Model("tm", "rock.obj");
  model->setMaterial(material);
  scene->add(model);

  Model *monkey0 = new Model("m0", "monkey3.obj");
  monkey0->setMaterial(material1);
  monkey0->setPosition({-5.0f, -7, 5});
  scene->add(monkey0);

  Model *monkey1 = new Model("m1", "monkey3.obj");
  monkey1->setMaterial(material1);
  monkey1->setPosition({-2.3f, -7, 5});
  scene->add(monkey1);

  Model *monkey2 = new Model("m2", "monkey3.obj");
  monkey2->setMaterial(material1);
  monkey2->setPosition({0.6f, -7, 5});
  scene->add(monkey2);

  Model *plane = new Model("tm0", "plane0.obj");
  plane->setMaterial(parallax);
  plane->setPosition({0, -10, 0});
  plane->rotate(vec3::UnitY(), 180.0f);
//	plane->rotate(vec3::UnitZ(), 45.0f);
  scene->add(plane);

  Model *plane1 = new Model("tm0", "plane0.obj");
  plane1->setMaterial(disp);
  plane1->setPosition({16.5f, -10, 0});
  scene->add(plane1);

  Model *plane2 = new Model("tm0", "plane0.obj");
  plane2->setMaterial(bricks);
  plane2->setPosition({33, -10, 0});
  scene->add(plane2);

  Model *plane3 = new Model("tm0", "plane0.obj");
  plane3->setMaterial(pebble);
  plane3->setPosition({0, -10, 16.5f});
  scene->add(plane3);


  //bottom
  Model *plane01 = new Model("p01", "plane0.obj");
  plane01->setMaterial(material);
  plane01->setPosition({-16.5f, -10, 0});
  scene->add(plane01);

  //top
  Model *plane02 = new Model("p02", "plane0.obj");
  plane02->setMaterial(material);
  plane02->setPosition({-16.5f, 6.0f, 0});
  scene->add(plane02);

  //back
  Model *plane03 = new Model("p03", "plane0.obj");
  plane03->setMaterial(material);
  plane03->setPosition({-16.5f, -2.0f, -8.0f});
  plane03->rotate(vec3::UnitX(), 90);
  scene->add(plane03);

  //right
  Model *plane04 = new Model("p04", "plane0.obj");
  plane04->setMaterial(material);
  plane04->setPosition({-8.45f, -2.0f, 0});
  plane04->rotate(vec3::UnitZ(), 90);
  scene->add(plane04);

  //left
  Model *plane05 = new Model("p04", "plane0.obj");
  plane05->setMaterial(material);
  plane05->setPosition({-24.55f, -2.0f, 0});
  plane05->rotate(vec3::UnitZ(), 90);
  scene->add(plane05);

  player = new DummyPlayer(camera);


  sl = new SpotLight("l0");
  sl->setPosition({12, 11, 10.0});
  sl->rotate(vec3::UnitX(), -45);
  sl->rotate(vec3::UnitZ(), -10);
  sl->setColor({1.0f, 0.9f, 0.8f});
  sl->setSpotAngle(50.0f);
  sl->setIntensity(8.0f);
  sl->setFalloff(15.0f);
  sl->setShadowed(true);
//	scene->add(sl);

  SpotLight *sl1 = new SpotLight("l1");
  sl1->setPosition({-8, 8, 12.0});
  sl1->rotate(vec3::UnitX(), -50);
  sl1->rotate(vec3::UnitY(), -15);
  sl1->setColor({0.3f, 0.6f, 0.8f});
  sl1->setSpotAngle(40.0f);
  sl1->setIntensity(1.5f);
  sl1->setFalloff(20.0f);
  sl1->setShadowed(true);
//	scene->add(sl1);

  pl = new PointLight("l1");
  pl->setPosition({-10, 2, 0});
  pl->setColor({0.5f, 0.8f, 0.8f});
  pl->setIntensity(0.4f);
  pl->setFalloff(10.0f);
//	scene->add(pl);

  dl = new DirectionalLight("dl0", {15.0f, 30.0f, 50.0f, 100.0f});
  dl->rotate(vec3::UnitX(), -35.0f);
  dl->rotate(vec3::UnitY(), -10.0f);
  dl->setColor({1.0f, 1.0f, 0.7f});
  dl->setIntensity(5.0f);
  scene->setDirectionalLight(dl);
}

Test3D::~Test3D() {
  delete player;
  delete camera;
  delete renderer;

  delete material;
  delete material1;
  delete parallax;
  delete disp;
  delete bricks;
  delete pebble;

  delete scene;
}

void Test3D::render() {
  renderer->render(scene);
}

void Test3D::renderImGui() {
  const vec3 &cp = camera->getPosition();
  const vec3 &cl = camera->getRotation().getForward();

  ImGui::Begin("Test3D");

  ImGui::Text("fps: %i", app.getFPS());
  ImGui::Text("draw calls: %i", Renderer::getDC());
  ImGui::Text("camera: (%.1f, %.1f, %.1f)", cp.x, cp.y, cp.z);
  ImGui::Text("look: (%.1f, %.1f, %.1f)", cl.x, cl.y, cl.z);
  ImGui::Separator();
  ImGui::Dummy({10.0f, 0.0f});

  static bool lightObjects = true;
  if (ImGui::Checkbox("Light objects", &lightObjects)) {
    renderer->enableLightObjects(lightObjects);
  }

  static bool lightBounds = true;
  if (ImGui::Checkbox("Light bounds", &lightBounds)) {
    renderer->enableLightBounds(lightBounds);
  }

  static bool wireframe = false;
  if (ImGui::Checkbox("Wireframe", &wireframe)) {
    renderer->enableWireframe(wireframe);
  }

  static bool cull = true;
  if (ImGui::Checkbox("Cull test", &cull)) {
    renderer->enableCullTest(cull);
  }

  static const char *aoTypes[] = {"SSAO", "HBAO", "None"};
  static int32 currentAO = 1;
  if (ImGui::Combo("AO", &currentAO, aoTypes, 3)) {
    renderer->setAOType(fx::AmbientOcclusion::stringToType(aoTypes[currentAO]));
  }

  static bool m1n = true;
  if (ImGui::Checkbox("M1 normals", &m1n)) {
    if (m1n) {
      material1->setNormalMap(GETTEXTURE("normal1"));
    } else {
      material1->setNormalMap(nullptr);
    }
  }

  static bool sls = sl->isShadowed();
  if (ImGui::Checkbox("sl0 shadows", &sls)) {
    sl->setShadowed(sls);
  }

  ImGui::PushItemWidth(-1.0f);
  static int32 shadows = Config::get().shadowQuality;
  ImGui::Text("Shadow quality");
  if (ImGui::SliderInt("Q", &shadows, 0, 3)) {
    renderer->setShadowQuality(shadows);
  }

  static float intensity = pl->getIntensity();
  if (ImGui::SliderFloat("I", &intensity, 0.1f, 100.0f, "%.2f", 1.5f)) {
    pl->setIntensity(intensity);
  }

  static float spec = material->getSpecularShininess();
  ImGui::Text("Specular shininess");
  if (ImGui::SliderFloat("S", &spec, 0.0f, 1.0f, "%.3f")) {
    material->setSpecularShininess(spec);
  }

  static float ambient = 0.1f;
  ImGui::Text("Ambient");
  if (ImGui::SliderFloat("A", &ambient, 0.0f, 1.0f, "%.3f")) {
    renderer->setAmbientLight(vec3(ambient));
  }
  ImGui::PopItemWidth();


  ImGui::End();

  const GBuffer *buffer = renderer->getGBuffer();

  ImGui::Begin("Buffers");
  ImGui::Image(reinterpret_cast<void *>(buffer->getDepthStencilTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
  ImGui::SameLine();
  ImGui::Image(reinterpret_cast<void *>(buffer->getDiffuseTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
  ImGui::SameLine();
  ImGui::Image(reinterpret_cast<void *>(buffer->getPositionTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
  ImGui::SameLine();
  ImGui::Image(reinterpret_cast<void *>(buffer->getNormalTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
  ImGui::SameLine();
  ImGui::Image(reinterpret_cast<void *>(buffer->getSpecularTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
  ImGui::SameLine();
  ImGui::Image(reinterpret_cast<void *>(buffer->getLightDiffuseTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
  ImGui::SameLine();
  ImGui::Image(reinterpret_cast<void *>(buffer->getLightSpecularTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
  ImGui::SameLine();
  const Texture *ao = renderer->getAOTexture();
  if (ao) {
    ImGui::Image(reinterpret_cast<void *>(ao->getHandle()), {128, 72}, {0, 1}, {1, 0});
  }
  ImGui::End();

  ImGui::Begin("Materials");
  ImGui::Text("Parallax");
  static bool parallaxMap = true;
  if (ImGui::Checkbox("Disp0", &parallaxMap)) {
    if (parallaxMap) {
      parallax->setHeightMap(GETTEXTURE("brick1_h"));
    } else {
      parallax->setHeightMap(nullptr);
    }
  }

  ImGui::PushItemWidth(-1.0f);
  static float parallaxStrength = parallax->getHeightScale();
  if (ImGui::SliderFloat("W", &parallaxStrength, 0.0f, 0.1f, "%.3f")) {
    parallax->setHeightScale(parallaxStrength);
  }
  ImGui::PopItemWidth();

  ImGui::Text("Disp");
  static bool dispMap = true;
  if (ImGui::Checkbox("Disp1", &dispMap)) {
    if (dispMap) {
      disp->setHeightMap(GETTEXTURE("r031_disp"));
    } else {
      disp->setHeightMap(nullptr);
    }
  }

  ImGui::PushItemWidth(-1.0f);
  static float dispStrength = disp->getHeightScale();
  if (ImGui::SliderFloat("Q", &dispStrength, 0.0f, 0.1f, "%.3f")) {
    disp->setHeightScale(dispStrength);
  }
  ImGui::PopItemWidth();

  ImGui::Text("Bricks");
  static bool bricksDisp = true;
  if (ImGui::Checkbox("Disp2", &bricksDisp)) {
    if (bricksDisp) {
      bricks->setHeightMap(GETTEXTURE("bricks2_h"));
    } else {
      bricks->setHeightMap(nullptr);
    }
  }

  ImGui::PushItemWidth(-1.0f);
  static float bricksDispStrength = bricks->getHeightScale();
  if (ImGui::SliderFloat("E", &bricksDispStrength, 0.0f, 0.1f, "%.3f")) {
    bricks->setHeightScale(bricksDispStrength);
  }
  ImGui::PopItemWidth();

  ImGui::Text("Pebble");
  static bool pebbleDisp = true;
  if (ImGui::Checkbox("Disp3", &pebbleDisp)) {
    if (pebbleDisp) {
      pebble->setHeightMap(GETTEXTURE("pebble_h"));
    } else {
      pebble->setHeightMap(nullptr);
    }
  }

  ImGui::PushItemWidth(-1.0f);
  static float pebbleDispStrength = pebble->getHeightScale();
  if (ImGui::SliderFloat("R", &pebbleDispStrength, 0.0f, 0.1f, "%.3f")) {
    pebble->setHeightScale(pebbleDispStrength);
  }
  ImGui::PopItemWidth();

  ImGui::End();
}

void Test3D::update(float delta) {
  scene->updateLights(camera);

  player->update(delta);

  if (hook) {
    sl->setRotation(camera->getRotation());
    sl->setPosition(camera->getPosition());
  }
  if (hook2) {
    pl->setPosition(camera->getPosition());
  }

  if (rock) {
    model->setPosition(camera->getPosition());
  }

  if (dlr) {
    dl->setRotation(camera->getRotation());
  }
}

void Test3D::fixedUpdate(float delta) {
  model->rotate(vec3::UnitY(), 30 * delta);
}

void Test3D::input(Event &event) {
  player->input(event);

  if (event.type == Event::KeyPressed) {
    if (event.key.code == Keyboard::F) {
      hook = !hook;
    }
    if (event.key.code == Keyboard::G) {
      hook2 = !hook2;
    }
    if (event.key.code == Keyboard::R) {
      rock = !rock;
    }
    if (event.key.code == Keyboard::H) {
      dlr = !dlr;
    }
    if (event.key.code == Keyboard::J) {
//      delete scene->removeModel(model->getName());
//      scene->removeLight(sl->getName());
    }
    if (event.key.code == Keyboard::K) {
//      delete sl;
//      scene->removeModel(model->getName());
    }
  }
}
