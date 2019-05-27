//
// Created by FLXR on 5/27/2019.
//

#include "exampleparticles.hpp"
#include <xe/resources/texturemanager.hpp>
#include <xe/ui/imgui/imgui.h>

using namespace xe;

ExampleParticles *ExampleParticles::instance = nullptr;

ExampleParticles::ExampleParticles() :
    renderBg(true),
    updateRS(true),
    updateTS(true),
    updateSS(true),
    updateCS(true),
    e0Hooked(false),
    e1Hooked(false) {

  const float width = app.getWindowSize().x;
  const float height = app.getWindowSize().y;

  camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f));
  renderer = new Renderer2D(width, height, camera);

  bg = new RectangleShape({1920 * 2.0f, 1080 * 2.0f});

  rs.emplace_back(0.0f, 45.0f, 10.0f);
  rs.emplace_back(0.5f, 90.0f, 20.0f);
  rs.emplace_back(1.0f, -90.0f, 10.0f);

  ts.emplace_back(0.0f, vec2(0.0f, 0.0f), vec2(5.0f, 10.0f));
  ts.emplace_back(1.0f, vec2(0.0f, 100.0f), vec2(20.0f, 50.0f));

  ss.emplace_back(0.0f, vec2(10.0f, 10.0f), vec2(1.0f, 1.0f));
  ss.emplace_back(1.0f, vec2(5.0f, 5.0f), vec2(0.5f, 0.5f));

  cs.emplace_back(0.0f, vec4(0.0f, 0.1f, 1.0f, 1.0f), vec4(0.0f));
  cs.emplace_back(1.0f, vec4(0.0f, 0.8f, 1.0f, 0.95f), vec4(0.0f));

  effect0 = new ParticleEffect(1.0f, 0.3f, 100, true);
  effect0->setPosition({width / 2, height / 3});
  effect0->setColorChange(false);
  effect0->create();


  //flame effect
  effect1 = new ParticleEffect(1.0f, 0.5f, 100, true);
  effect1->setPosition({1000, 250});

  effect1->setRotationStates({std::make_tuple(0.0f, 45.0f, 10.0f),
                              std::make_tuple(0.5f, 90.0f, 20.0f),
                              std::make_tuple(1.0f, -90.0f, 10.0f)});

  effect1->setTranslationStates({std::make_tuple(0.0f, vec2(0.0f, 0.0f), vec2(5.0f, 10.0f)),
                                 std::make_tuple(1.0f, vec2(0.0f, 100.0f), vec2(20.0f, 50.0f))});

  effect1->setSizeStates({std::make_tuple(0.0f, vec2(10.0f, 10.0f), vec2(1.0f, 1.0f)),
                          std::make_tuple(1.0f, vec2(5.0f, 5.0f), vec2(0.5f, 0.5f))});

  effect1->setColorStates({std::make_tuple(0.0f, vec4(1.0f, 0.1f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f)),
                           std::make_tuple(1.0f, vec4(1.0f, 0.8f, 0.0f, 0.95f), vec4(0.0f, 0.2f, 0.0f, 0.0f))});
  effect1->create();
}

ExampleParticles::~ExampleParticles() {
  delete camera;
  delete renderer;
  delete effect0;
  delete effect1;
  delete bg;
}

void ExampleParticles::init() {
  bg->setTexture(GETTEXTURE("bg"));
  bg->move(app.getWindowSize() / 2.0f);

  effect0->play();
  effect1->play();
}

void ExampleParticles::render() {
  renderer->begin();

  if (renderBg) {
    renderer->submit(bg);
  }

  effect1->render(renderer);
  effect0->render(renderer);

  renderer->end();
  renderer->flush();
}

void ExampleParticles::renderImGui() {
  ImGui::Begin("Particles 2D", nullptr);

  ImGui::Checkbox("Render BG", &renderBg);
  ImGui::Separator();

  ImGui::Text("LMB - move effect0\nRMB - move effect1");

  ImGui::Separator();
  if (ImGui::Button("Play")) {
    effect0->play();
  }

  ImGui::SameLine();
  if (ImGui::Button("Stop")) {
    effect0->stop();
  }

  ImGui::SameLine();
  static bool looped = true;
  if (ImGui::Button("Toggle loop")) {
    looped = !looped;
    effect0->setLooped(looped);
  }

  ImGui::Separator();
  static float d = effect0->getDuration();
  if (ImGui::SliderFloat("Duration", &d, 0.3f, 10.0f)) {
    effect0->setDuration(d);
  }

  static float c = effect0->getChange();
  if (ImGui::SliderFloat("Change", &c, 0.0f, 10.0f)) {
    effect0->setChange(c);
  }

  drawRotationStates();
  drawTranslationStates();
  drawSizeStates();
  drawColorStates();

  ImGui::End();
}

void ExampleParticles::drawRotationStates() {
  if (ImGui::CollapsingHeader("Rotation")) {
    ImGui::Separator();
    static bool rc = effect0->hasRotationChange();
    if (ImGui::Checkbox("Rotation change", &rc)) {
      effect0->setRotationChange(rc);
    }

    for (size_t i = 0; i < rs.size(); ++i) {
      const string t = "time##r" + std::to_string(i);
      const string v = "value##r" + std::to_string(i);
      const string c = "change##r" + std::to_string(i);
      const string b = "-##r" + std::to_string(i);

      if (ImGui::SliderFloat(t.c_str(), &std::get<0>(rs[i]), 0.0f, 1.0f)) updateRS = true;
      if (i != 0) {
        ImGui::SameLine();
        if (ImGui::Button(b.c_str())) {
          if (rs.size() == 1) continue;
          rs.erase(rs.begin() + i);
          updateRS = true;
          continue;
        }
      }
      if (ImGui::InputFloat(v.c_str(), &std::get<1>(rs[i]), 0.0f, 0.0f, "%.1f")) updateRS = true;
      if (ImGui::InputFloat(c.c_str(), &std::get<2>(rs[i]), 0.0f, 0.0f, "%.1f")) updateRS = true;
      ImGui::Separator();
    }
    if (ImGui::Button("+##r")) {
      rs.emplace_back(1.0f, 0.0f, 0.0f);
    }
  }
}

void ExampleParticles::drawTranslationStates() {
  if (ImGui::CollapsingHeader("Translation")) {
    ImGui::Separator();
    static bool tc = effect0->hasTranslationChange();
    if (ImGui::Checkbox("Translation change", &tc)) {
      effect0->setTranslationChange(tc);
    }

    for (size_t i = 0; i < ts.size(); ++i) {
      const string t = "time##t" + std::to_string(i);
      const string v = "value##t" + std::to_string(i);
      const string c = "change##t" + std::to_string(i);
      const string b = "-##t" + std::to_string(i);

      if (ImGui::SliderFloat(t.c_str(), &std::get<0>(ts[i]), 0.0f, 1.0f)) updateTS = true;
      if (i != 0) {
        ImGui::SameLine();
        if (ImGui::Button(b.c_str())) {
          if (ts.size() == 1) continue;
          ts.erase(ts.begin() + i);
          updateTS = true;
          continue;
        }
      }
      if (ImGui::SliderFloat2(v.c_str(), reinterpret_cast<float *>(&std::get<1>(ts[i])), -300.0f, 300.0f, "%.1f"))
        updateTS = true;
      if (ImGui::SliderFloat2(c.c_str(), reinterpret_cast<float *>(&std::get<2>(ts[i])), 0.0f, 300.0f, "%.1f"))
        updateTS = true;
      ImGui::Separator();
    }
    if (ImGui::Button("+##t")) {
      ts.emplace_back(1.0f, 0.0f, 0.0f);
    }
  }
}

void ExampleParticles::drawSizeStates() {
  if (ImGui::CollapsingHeader("Size")) {
    ImGui::Separator();
    static bool sc = effect0->hasSizeChange();
    if (ImGui::Checkbox("Size change", &sc)) {
      effect0->setSizeChange(sc);
    }

    for (size_t i = 0; i < ss.size(); ++i) {
      const string t = "time##s" + std::to_string(i);
      const string v = "value##s" + std::to_string(i);
      const string c = "change##s" + std::to_string(i);
      const string b = "-##s" + std::to_string(i);

      if (ImGui::SliderFloat(t.c_str(), &std::get<0>(ss[i]), 0.0f, 1.0f)) updateSS = true;
      if (i != 0) {
        ImGui::SameLine();
        if (ImGui::Button(b.c_str())) {
          if (ss.size() == 1) continue;
          ss.erase(ss.begin() + i);
          updateSS = true;
          continue;
        }
      }
      if (ImGui::SliderFloat2(v.c_str(), reinterpret_cast<float *>(&std::get<1>(ss[i])), 0.0f, 100.0f, "%.1f")) {
        updateSS = true;
      }
      if (ImGui::SliderFloat2(c.c_str(), reinterpret_cast<float *>(&std::get<2>(ss[i])), 0.0f, 100.0f, "%.1f")) {
        updateSS = true;
      }
      ImGui::Separator();
    }
    if (ImGui::Button("+##s")) {
      ss.emplace_back(1.0f, 0.0f, 0.0f);
    }
  }
}

void ExampleParticles::drawColorStates() {
  if (ImGui::CollapsingHeader("Color")) {
    ImGui::Separator();
    for (size_t i = 0; i < cs.size(); ++i) {
      const string t = "time##c" + std::to_string(i);
      const string v = "value##c" + std::to_string(i);
      const string b = "-##c" + std::to_string(i);

      if (ImGui::SliderFloat(t.c_str(), &std::get<0>(cs[i]), 0.0f, 1.0f)) updateCS = true;
      if (i != 0) {
        ImGui::SameLine();
        if (ImGui::Button(b.c_str())) {
          if (cs.size() == 1) continue;
          cs.erase(cs.begin() + i);
          updateCS = true;
          continue;
        }
      }
      if (ImGui::ColorEdit4(v.c_str(), reinterpret_cast<float *>(&std::get<1>(cs[i])))) updateCS = true;
      ImGui::Separator();
    }
    if (ImGui::Button("+##c")) {
      cs.emplace_back(1.0f, vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(0.0f));
    }
    ImGui::Separator();
  }
}

void ExampleParticles::update(float delta) {
  effect0->update(delta);
  effect1->update(delta);

  if (updateRS) {
    effect0->setRotationStates(rs);
  }
  if (updateTS) {
    effect0->setTranslationStates(ts);
  }
  if (updateSS) {
    effect0->setSizeStates(ss);
  }
  if (updateCS) {
    effect0->setColorStates(cs);
  }

  if (e0Hooked) {
    effect0->setPosition(Mouse::getPosition(window));
  }
  if (e1Hooked) {
    effect1->setPosition(Mouse::getPosition(window));
  }
}

void ExampleParticles::fixedUpdate(float delta) {
  effect0->fixedUpdate(delta);
  effect1->fixedUpdate(delta);
}

void ExampleParticles::input(xe::Event &event) {
  if (event.type == Event::MouseButtonPressed) {
    if (event.mouseButton.button == Mouse::Left) {
      e0Hooked = true;
    }
    if (event.mouseButton.button == Mouse::Right) {
      e1Hooked = true;
    }
  } else if (event.type == Event::MouseButtonReleased) {
    if (event.mouseButton.button == Mouse::Left) {
      e0Hooked = false;
    }
    if (event.mouseButton.button == Mouse::Right) {
      e1Hooked = false;
    }
  }
}
