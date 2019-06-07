//
// Created by FLXR on 6/4/2019.
//

#include "examplesound.hpp"
#include <xe/resources/texturemanager.hpp>
#include <xe/ui/imgui/imgui.h>
#include <xe/gfx/renderer.hpp>
#include <xe/audio/audiomaster.hpp>
#include <xe/resources/soundmanager.hpp>

using namespace xe;

ExampleSound *ExampleSound::instance = nullptr;

ExampleSound::ExampleSound() {

  const float width = app.getWindowSize().x;
  const float height = app.getWindowSize().y;

  camera = new Camera(mat4::perspective(60.0f, width / height, 0.1f, 1000.0f));
  camera->setPosition({4.0f, 3.0f, 20.0f});

  player = new DummyPlayer(camera);

  ShadowParameters sp(app.getConfig(), 512, 1024);

  renderer = new DeferredRenderer(width, height, camera, sp, fx::AOType::None);
  renderer->setAmbientLight({0.10f, 0.14f, 0.25f});
  renderer->enableLightObjects(true);

  exampleScene = &ExampleScene::get();

  scene = new Scene();

  Model *m = new Model("source0", IndexedModel::getIcosphereModel());
  m->setMaterial(exampleScene->mat_cloth);
  scene->add(m);

  as0 = new AudioSource("as0", GETSOUND("orunec"));
  as0->setPosition({0.0f, 0.0f, 0.0f});
  as0->setGain(1.0f);
  as0->setRolloffFactor(1.0f);
  as0->setPitch(1.2f);
  as0->setMaxDistance(100);

  AudioMaster::setDistanceModel(DistanceModel::Linear);
}

ExampleSound::~ExampleSound() {
  delete player;
  delete camera;
  delete renderer;

  delete scene;

  delete as0;
}

void ExampleSound::init() {

}

void ExampleSound::render() {
  renderer->render(scene);
}

void ExampleSound::renderImGui() {
  const vec3 &cp = camera->getPosition();
  const vec3 &cl = camera->getRotation().getForward();

  ImGui::Begin("Example sound", nullptr);

  ImGui::Text("camera: (%.1f, %.1f, %.1f)", cp.x, cp.y, cp.z);
  ImGui::Text("look: (%.1f, %.1f, %.1f)", cl.x, cl.y, cl.z);

  if (ImGui::Button("Orunec")) {
    as0->play();
  }

  static bool looped = as0->isLooped();
  if (ImGui::Checkbox("Looped", &looped)) {
    as0->setLooping(looped);
  }

  static float gain = as0->getGain();
  if (ImGui::DragFloat("Gain", &gain, 0.1f, 0.0f, 1.0f)) {
    as0->setGain(gain);
  }

  static float rolloff = as0->getRolloffFactor();
  if (ImGui::DragFloat("Rolloff factor", &rolloff, 0.1f, 0.0f, 10.0f)) {
    as0->setRolloffFactor(rolloff);
  }

  static float pitch = as0->getPitch();
  if (ImGui::DragFloat("Pitch", &pitch, 0.03f, 0.3f, 2.0f)) {
    as0->setPitch(pitch);
  }

  static float maxDistance = as0->getMaxDistance();
  if (ImGui::DragFloat("Max distance", &maxDistance, 1.0f, 1.0f, 100.0f)) {
    as0->setMaxDistance(maxDistance);
  }

  ImGui::End();
}

void ExampleSound::update(float delta) {
  player->update(delta);

  scene->updateLights(camera);

  AudioMaster::update(camera);
}

void ExampleSound::fixedUpdate(float delta) {
  player->update(delta);
}

void ExampleSound::input(xe::Event &event) {
  player->input(event);

  if (event.type == Event::KeyPressed) {
    if (event.key.code == Keyboard::F) {
      as0->play();
    }
  }
}
