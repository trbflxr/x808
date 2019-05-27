//
// Created by FLXR on 5/19/2019.
//

#include "example3d.hpp"
#include <xe/resources/texturemanager.hpp>
#include <xe/ui/imgui/imgui.h>
#include <xe/gfx/renderer.hpp>

using namespace xe;

Example3D *Example3D::instance = nullptr;

Example3D::Example3D() :
    lightsConfig(false),
    dlHooked(false),
    slHooked(false),
    plHooked(false) {

  const float width = app.getWindowSize().x;
  const float height = app.getWindowSize().y;

  camera = new Camera(mat4::perspective(60.0f, width / height, 0.1f, 1000.0f));
  camera->setPosition({4.0f, 3.0f, 20.0f});

  player = new DummyPlayer(camera);

  ShadowParameters sp(app.getConfig(), 512, 1024);

  renderer = new DeferredRenderer(width, height, camera, sp, fx::AOType::None);
  renderer->setAmbientLight({0.010f, 0.014f, 0.025f});
  renderer->enableLightObjects(true);

  scene = &ExampleScene::get();
}

Example3D::~Example3D() {
  delete player;
  delete camera;
  delete renderer;
}

void Example3D::init() {

}

void Example3D::render() {
  renderer->render(scene->scene);
}

void Example3D::renderImGui() {
  const vec3 &cp = camera->getPosition();
  const vec3 &cl = camera->getRotation().getForward();

  ImGui::Begin("Example 3D", nullptr);

  ImGui::Text("camera: (%.1f, %.1f, %.1f)", cp.x, cp.y, cp.z);
  ImGui::Text("look: (%.1f, %.1f, %.1f)", cl.x, cl.y, cl.z);

  static bool lightObjects = true;
  if (ImGui::Checkbox("Light objects", &lightObjects)) {
    renderer->enableLightObjects(lightObjects);
  }

  static bool lightBounds = false;
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

  static const char *aoTypes[] = {"None", "SSAO", "HBAO"};
  static int32 currentAO = 0;
  if (ImGui::Combo("AO", &currentAO, aoTypes, 3)) {
    renderer->setAOType(fx::AmbientOcclusion::stringToType(aoTypes[currentAO]));
  }

  ImGui::PushItemWidth(-1.0f);
  static int32 shadows = Config::get().shadowQuality;
  ImGui::Text("Shadow quality");
  if (ImGui::SliderInt("Q", &shadows, 0, 3)) {
    renderer->setShadowQuality(shadows);
  }
  ImGui::PopItemWidth();

  ImGui::Separator();
  ImGui::Dummy({10.0f, 0.0f});
  if (ImGui::Button("Configure lights")) {
    lightsConfig = true;
  }

  drawLightsConfig();

  ImGui::End();
}

void Example3D::update(float delta) {
  scene->scene->updateLights(camera);

  player->update(delta);

  if (slHooked) {
    scene->spotLight->setRotation(camera->getRotation());
    scene->spotLight->setPosition(camera->getPosition());
  }
  if (plHooked) {
    scene->pointLight->setPosition(camera->getPosition());
  }
  if (dlHooked) {
    scene->directionalLight->setRotation(camera->getRotation());
  }
}

void Example3D::fixedUpdate(float delta) {
  scene->mod_rock->rotate(vec3::UnitY(), 30.0f * delta);
}

void Example3D::input(xe::Event &event) {
  player->input(event);

  if (event.type == Event::KeyPressed) {
    if (event.key.code == Keyboard::F) {
      slHooked = !slHooked;
    }
    if (event.key.code == Keyboard::G) {
      plHooked = !plHooked;
    }
    if (event.key.code == Keyboard::H) {
      dlHooked = !dlHooked;
    }
  }
}

void Example3D::drawLightsConfig() {
  if (!lightsConfig)return;

  ImGui::Begin("Configure lights", &lightsConfig);

  if (ImGui::BeginTabBar("LightsConfig")) {
    if (ImGui::BeginTabItem("Ambient")) {
      drawAmbientTab();
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Directional")) {
      drawDirectionalTab();
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Spot")) {
      drawSpotTab();
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Point")) {
      drawPointTab();
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }

  ImGui::End();
}

void Example3D::drawAmbientTab() {
  static vec3 ambient = renderer->getAmbientLight();
  if (ImGui::ColorEdit3("Color", reinterpret_cast<float *>(&ambient))) {
    renderer->setAmbientLight(ambient);
  }
}

void Example3D::drawDirectionalTab() {
  static vec3 color = scene->directionalLight->getColor();
  if (ImGui::ColorEdit3("Color", reinterpret_cast<float *>(&color))) {
    scene->directionalLight->setColor(color);
  }

  static float intensity = scene->directionalLight->getIntensity();
  if (ImGui::SliderFloat("Intensity", &intensity, 0.0f, 30.0f)) {
    scene->directionalLight->setIntensity(intensity);
  }

  static bool shadowed = scene->directionalLight->isShadowed();
  if (ImGui::Checkbox("Shadowed", &shadowed)) {
    scene->directionalLight->setShadowed(shadowed);
  }

  static bool enabled = scene->directionalLight->isEnabled();
  if (ImGui::Checkbox("Enabled", &enabled)) {
    scene->directionalLight->setEnabled(enabled);
  }

  ImGui::Checkbox("Hook(H)", &dlHooked);
}

void Example3D::drawSpotTab() {
  static vec3 color = scene->spotLight->getColor();
  if (ImGui::ColorEdit3("Color", reinterpret_cast<float *>(&color))) {
    scene->spotLight->setColor(color);
  }

  static float intensity = scene->spotLight->getIntensity();
  if (ImGui::SliderFloat("Intensity", &intensity, 0.0f, 30.0f)) {
    scene->spotLight->setIntensity(intensity);
  }

  static float falloff = scene->spotLight->getFalloff();
  if (ImGui::SliderFloat("Falloff", &falloff, 0.0f, 50.0f)) {
    scene->spotLight->setFalloff(falloff);
  }

  static float spotAngle = scene->spotLight->getSpotAngle();
  if (ImGui::SliderFloat("Spot angle", &spotAngle, 5.0f, 75.0f)) {
    scene->spotLight->setSpotAngle(spotAngle);
  }

  static float spotBlur = scene->spotLight->getSpotBlur();
  if (ImGui::SliderFloat("Spot blur", &spotBlur, 0.0f, 1.0f)) {
    scene->spotLight->setSpotBlur(spotBlur);
  }

  static bool shadowed = scene->spotLight->isShadowed();
  if (ImGui::Checkbox("Shadowed", &shadowed)) {
    scene->spotLight->setShadowed(shadowed);
  }

  static bool enabled = scene->spotLight->isEnabled();
  if (ImGui::Checkbox("Enabled", &enabled)) {
    scene->spotLight->setEnabled(enabled);
  }

  ImGui::Checkbox("Hook(F)", &slHooked);
}

void Example3D::drawPointTab() {
  static vec3 color = scene->pointLight->getColor();
  if (ImGui::ColorEdit3("Color", reinterpret_cast<float *>(&color))) {
    scene->pointLight->setColor(color);
  }

  static float intensity = scene->pointLight->getIntensity();
  if (ImGui::SliderFloat("Intensity", &intensity, 0.0f, 30.0f)) {
    scene->pointLight->setIntensity(intensity);
  }

  static float falloff = scene->pointLight->getFalloff();
  if (ImGui::SliderFloat("Falloff", &falloff, 0.0f, 50.0f)) {
    scene->pointLight->setFalloff(falloff);
  }

  static bool enabled = scene->pointLight->isEnabled();
  if (ImGui::Checkbox("Enabled", &enabled)) {
    scene->pointLight->setEnabled(enabled);
  }

  ImGui::Checkbox("Hook(G)", &plHooked);
}
