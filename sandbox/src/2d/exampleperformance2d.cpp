//
// Created by FLXR on 6/3/2019.
//

#include "exampleperformance2d.hpp"
#include <xe/resources/texturemanager.hpp>
#include <xe/utils/random.hpp>

using namespace xe;

ExamplePerformance2D *ExamplePerformance2D::instance = nullptr;

ExamplePerformance2D::ExamplePerformance2D() :
    sprites(0) {

  const float width = app.getWindowSize().x;
  const float height = app.getWindowSize().y;

  camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f));
  renderer = new Renderer2D(width, height, camera);

  std::vector<rect> rects;
  for (const auto &a : GETATLAS("atlas")->getAreas()) {
    rects.push_back(a.second);
  }

  uint texCount = rects.size();

  /// 1 - 2304
  /// 2 - 14400
  /// 3 - 60865
  /// 4 - 102480
#define sp_size 3

#if sp_size == 4
  for (float x = 0.0f; x < 1280; x += 3.0f) {
    for (float y = 0.0f; y < 720; y += 3.0f) {
      RectangleShape *s = new RectangleShape({2.5f, 2.5f});
      s->setTexture(GETATLAS("atlas")->getTexture());
      s->setTextureRect(rects[random::next<uint>(0, texCount - 1)]);
      s->transformation({x, y});

      renderables.push_back(s);

      ++sprites;
    }
  }
#elif sp_size == 3
  for (float x = 0.0f; x < 1280; x += 3.9f) {
    for (float y = 0.0f; y < 720; y += 3.9f) {
      RectangleShape *s = new RectangleShape({3.4f, 3.4f});
      s->setTexture(GETATLAS("atlas")->getTexture());
      s->setTextureRect(rects[random::next<uint>(0, texCount - 1)]);
      s->transformation({x, y});

      renderables.push_back(s);

      ++sprites;
    }
  }
#elif sp_size == 2
  for (uint x = 0; x < 1280; x += 8) {
    for (uint y = 0; y < 720; y += 8) {
      RectangleShape *s = new RectangleShape({6.0f, 6.0f});
      s->setTexture(GETATLAS("atlas")->getTexture());
      s->setTextureRect(rects[random::next<uint>(0, texCount - 1)]);
      s->transformation(vec2(x + 3.0f, y + 3.0f));

      renderables.push_back(s);

      ++sprites;
    }
  }
#elif sp_size == 1
  for (int32 x = 0; x < 1280; x += 20) {
    for (int32 y = 0; y < 720; y += 20) {
      RectangleShape *s = new RectangleShape({15.0f, 15.0f});
      s->setTexture(GETATLAS("atlas")->getTexture());
      s->setTextureRect(rects[random::next<uint>(0, texCount - 1)]);
      s->transformation(vec2(x + 7.5f, y + 7.5f));

      renderables.push_back(s);

      ++sprites;
    }
  }
#endif

  string s = std::to_string(sprites) + " sprites drawn at 0 fps";
  text = new Text(s, GETFONT("fogsans42"));
  text->setTextColor(color::White);
  text->setOutlineColor(color::Black);
  text->setOutlineThickness(3.0f);
  text->setPosition({10.0f, 50.0f});
}

ExamplePerformance2D::~ExamplePerformance2D() {
  delete camera;
  delete renderer;

  delete text;

  for (auto &&r : renderables) {
    delete r;
  }
}

void ExamplePerformance2D::render() {
  renderer->begin();

  for (auto &&r : renderables) {
    renderer->submit(r);
  }

  renderer->submit(text);

  renderer->end();
  renderer->flush();
}

void ExamplePerformance2D::update(float delta) {
  const string s = std::to_string(sprites) + " sprites drawn at " + std::to_string(app.getFPS()) + " fps";
  text->setString(s);
}
