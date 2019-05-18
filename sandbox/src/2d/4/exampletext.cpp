//
// Created by FLXR on 5/18/2019.
//

#include "exampletext.hpp"
#include <xe/resources/texturemanager.hpp>
#include <xe/ui/imgui/imgui.h>
#include <xe/gfx/renderer.hpp>

using namespace xe;

ExampleText *ExampleText::instance = nullptr;

ExampleText::ExampleText() :
    scale(1.0f),
    textColor(1.0f),
    outlineColor(0.0f) {

  const float width = app.getWindowSize().x;
  const float height = app.getWindowSize().y;

  camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f));
  renderer = new Renderer2D(width, height, camera);

  float y = height - 85.0f;
  text0 = new Text("consolata72", GETFONT("consolata72"));
  text0->setTextColor(color::White);
  text0->setOutlineColor(color::Black);
  text0->setOutlineThickness(3.0f);
  text0->setPosition({300.0f, y});
  y -= 75.0f;

  text1 = new Text("fogsans42", GETFONT("fogsans42"));
  text1->setTextColor(color::White);
  text1->setOutlineColor(color::Black);
  text1->setOutlineThickness(2.5f);
  text1->setPosition({300.0f, y});
  y -= 55.0f;

  text2 = new Text("robotobold22", GETFONT("robotobold22"));
  text2->setTextColor(color::White);
  text2->setOutlineColor(color::Black);
  text2->setOutlineThickness(1.5f);
  text2->setPosition({300.0f, y});
  y -= 95.0f;

  text3 = new Text("fogsansit72", GETFONT("fogsansit72"));
  text3->setTextColor(color::White);
  text3->setOutlineColor(color::Black);
  text3->setOutlineThickness(3.0f);
  text3->setPosition({300.0f, y});
  y -= 95.0f;

  text4 = new Text("robotoregular72", GETFONT("robotoregular72"));
  text4->setTextColor(color::White);
  text4->setOutlineColor(color::Black);
  text4->setOutlineThickness(3.0f);
  text4->setPosition({300.0f, y});
  y -= 200.0f;

  text = new Text("Input text:", GETFONT("fogsansit72"));
  text->setTextColor(color::White);
  text->setOutlineColor(color::Black);
  text->setOutlineThickness(3.0f);
  text->setPosition({30.0f, y});

}

ExampleText::~ExampleText() {
  delete camera;
  delete renderer;
  delete text;
  delete text0;
  delete text1;
  delete text2;
  delete text3;
  delete text4;
}

void ExampleText::init() {
  Renderer::setClearColor(0x70997E);
}

void ExampleText::render() {
  renderer->begin();

  renderer->submit(text);
  renderer->submit(text0);
  renderer->submit(text1);
  renderer->submit(text2);
  renderer->submit(text3);
  renderer->submit(text4);

  renderer->end();
  renderer->flush();
}

void ExampleText::renderImGui() {
  ImGui::Begin("Text", nullptr);

  if (ImGui::ColorEdit3("Text color", reinterpret_cast<float *>(&textColor))) {
    text->setTextColor(color::encode(vec4(textColor, 1.0f)));
  }
  if (ImGui::ColorEdit3("Outline color", reinterpret_cast<float *>(&outlineColor))) {
    text->setOutlineColor(color::encode(vec4(outlineColor, 1.0f)));
  }

  static const char *fonts[] = {"fogsansit72", "consolata72", "robotoregular72", "fogsans42"};
  static int32 selectedFont = 0;
  if (ImGui::Combo("Font", &selectedFont, fonts, 4)) {
    text->setFont(GETFONT(fonts[selectedFont]));
  }

  if (ImGui::SliderFloat("Scale", &scale, 0.5f, 3.0f)) {
    text->setScale(vec2(scale));
  }

  ImGui::End();
}

void ExampleText::input(xe::Event &event) {
  if (event.type == Event::TextEntered) {
    if (event.text.unicode == 8) {
      if (!inputString.empty()) {
        char *cp = inputString.data() + inputString.size();
        while (--cp >= inputString.data() && ((*cp & 0b10000000) && !(*cp & 0b01000000)));
        if (cp >= inputString.data()) {
          inputString.resize(cp - inputString.data());
        }
      }
    } else {
      inputString += reinterpret_cast<const char *>(&event.text.unicode);
    }
    text->setString("Input text:" + inputString);
  }
}