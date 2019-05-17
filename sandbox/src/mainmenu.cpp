//
// Created by FLXR on 5/17/2019.
//

#include "mainmenu.hpp"
#include "2d/0/test0.hpp"
#include <xe/ui/imgui/imgui.h>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/texturemanager.hpp>

using namespace xe;

MainMenu::MainMenu() :
    current(nullptr) {

  const float width = app.getWindowSize().x;
  const float height = app.getWindowSize().y;

  camera = new Camera(mat4::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, -1.0f, 1.0f));
  renderer = new Renderer2D(width, height, camera);

  bg = new RectangleShape({1920 * 2.0f, 1080 * 2.0f});
  bg->setTexture(GETTEXTURE("bg"));
}

MainMenu::~MainMenu() {
  popTest();

  delete bg;
}

void MainMenu::render() {
  if (current) return;

  renderer->begin();

  renderer->submit(bg);

  renderer->end();
  renderer->flush();
}

void MainMenu::renderImGui() {
//  static bool open = true;
//  ImGui::ShowDemoWindow(&open);

  static const uint flags = ImGuiWindowFlags_NoDocking |
                            ImGuiWindowFlags_MenuBar |
                            ImGuiWindowFlags_NoTitleBar |
                            ImGuiWindowFlags_NoResize |
                            ImGuiWindowFlags_NoCollapse |
                            ImGuiWindowFlags_AlwaysAutoResize |
                            ImGuiWindowFlags_NoSavedSettings |
                            ImGuiWindowFlags_NoFocusOnAppearing |
                            ImGuiWindowFlags_NoNav;


  const float DISTANCE = 10.0f;
  static int32 corner = 0;

  if (corner != -1) {
    const ImGuiViewport *viewport = ImGui::GetMainViewport();
    const ImVec2 windowPos = ImVec2(
        (corner & 1) ? (viewport->Pos.x + viewport->Size.x - DISTANCE) : (viewport->Pos.x + DISTANCE),
        (corner & 2) ? (viewport->Pos.y + viewport->Size.y - DISTANCE) : (viewport->Pos.y + DISTANCE));

    const ImVec2 windowPosPivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPosPivot);
    ImGui::SetNextWindowViewport(viewport->ID);
  }

  ImGui::SetNextWindowBgAlpha(0.3f);
  if (ImGui::Begin("MainMenu", nullptr, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | flags)) {
    if (ImGui::BeginMenuBar()) {
      if (ImGui::BeginMenu("Examples")) {
        if (ImGui::MenuItem("Layers", nullptr)) {
          showTest(Test0::create());
        }
        ImGui::EndMenu();
      }

      if (ImGui::MenuItem("Close all", nullptr)) {
        popTest();
      }
      ImGui::EndMenuBar();
    }
  }

  ImGui::Text("Right-click to change position");
  if (ImGui::BeginPopupContextWindow()) {
    if (ImGui::MenuItem("Custom", nullptr, corner == -1)) corner = -1;
    if (ImGui::MenuItem("Top-left", nullptr, corner == 0)) corner = 0;
    if (ImGui::MenuItem("Top-right", nullptr, corner == 1)) corner = 1;
    if (ImGui::MenuItem("Bottom-left", nullptr, corner == 2)) corner = 2;
    if (ImGui::MenuItem("Bottom-right", nullptr, corner == 3)) corner = 3;
    ImGui::EndPopup();
  }
  ImGui::End();
}

void MainMenu::update(float delta) {

}

void MainMenu::fixedUpdate(float delta) {

}

void MainMenu::input(Event &event) {

}

void MainMenu::showTest(ITestLayer *layer) {
  if (current == layer) return;

  if (current) {
    popTest();
  }
  current = layer;

  app.pushLayer(layer);
  layer->init();
}

void MainMenu::popTest() {
  if (current) {
    app.popLayer();
    current->destroyInstance();
    current = nullptr;
  }
}

void MainMenu::resize(int32 width, int32 height) {
  camera->setProjection(mat4::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, -1.0f, 1.0f));
  renderer->setWidth(width);
  renderer->setHeight(height);
}