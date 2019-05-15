//
// Created by FLXR on 9/11/2018.
//

#include <xe/resources/texturemanager.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/ui/imgui/imgui.h>
#include "testb2d.hpp"

using namespace xe;

void MyListener::beginContact(b2Contact *contact) {
  XE_TRACE("begin contact");
}

void MyListener::endContact(b2Contact *contact) {
  XE_TRACE("end contact");
}

void MyListener::preSolve(b2Contact *contact, const b2Manifold *oldManifold) {
  XE_TRACE("presolve contact");
}

void MyListener::postSolve(b2Contact *contact, const b2ContactImpulse *impulse) {
  XE_TRACE("postsolve contact");
}

TestB2D::TestB2D() {
  const float width = app.getWindowSize().x;
  const float height = app.getWindowSize().y;

  TextureParameters params;

  TextureManager::add(new Texture("0", "enemyspotted.png", params));
  TextureManager::add(new Texture("1", "jdm.png", params));
  TextureManager::add(new Texture("2", "star.png", params));
  TextureManager::add(new Texture("3", "test1.png", params));
  TextureManager::add(new Texture("4", "test6.png", params));
  TextureManager::add(new Texture("5", "test8.png", params));

  params.wrap = TextureWrap::Repeat;
  TextureManager::add(new Texture("6", "sp0.png", params));


  //create camera
  camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1000.0f));
  renderer = new Renderer2D(width, height, camera);

  contactListener = new MyListener();
  world = new PhysicsWorld2D({0.0f, -9.8f});
  world->setContactListener(contactListener);

  //rectangles
  box = new RectangleShape({50.0f, 50.0f});
  box->setTexture(GETTEXTURE("0"));
  box->transformation({400.0f, 400.0f});
  renderables.push_back(box);

  ground = new RectangleShape({500.0f, 5.0f});
  ground->setTexture(GETTEXTURE("3"));
  ground->transformation({400.0f, 50.0f}, 20.0f);
  renderables.push_back(ground);

  jdm = new RectangleShape({50.0f, 50.0f});
  jdm->setTexture(GETTEXTURE("1"));
  jdm->transformation({400.0f, 400.0f});
  renderables.push_back(jdm);

  //filters
  static constexpr uint16 GROUND = 2;
  static constexpr uint16 BOX = 4;
  static constexpr uint16 CIRCLE0 = 8;
  static constexpr uint16 CIRCLE1 = 16;
  static constexpr uint16 CIRCLE2 = 32;

  //rect colliders
  boxCollider = new BoxCollider2D(world, ColliderType::Dynamic, box);
  boxCollider->setDensity(20.5f);
  boxCollider->setFriction(0.2f);
  boxCollider->setRestitution(0.5f);
  boxCollider->setCategoryBits(BOX);
  boxCollider->setMask(GROUND | CIRCLE0);
  boxCollider->setUserData((void *) "test");

  groundCollider = new BoxCollider2D(world, ColliderType::Static, ground);
  groundCollider->setCategoryBits(GROUND);
  groundCollider->setMask(BOX | CIRCLE1 | CIRCLE2);

  //circles
  circle0 = new CircleShape(100.0f);
  circle0->setTexture(GETTEXTURE("5"));
  circle0->setTextureRect({100, 100, 400, 400});
  circle0->transformation({370.0f, 200.0f});
  renderables.push_back(circle0);

  circle1 = new CircleShape(50.0f);
  circle1->setTexture(GETTEXTURE("4"));
  circle1->transformation({470.0f, 500.0f});
  renderables.push_back(circle1);

  circle2 = new CircleShape(50.0f);
  circle2->setTexture(GETTEXTURE("3"));
  circle2->transformation({470.0f, 600.0f});
  renderables.push_back(circle2);

  //circle colliders
  circleCollider0 = new CircleCollider2D(world, ColliderType::Static, circle0);
  circleCollider0->setCategoryBits(CIRCLE0);
  circleCollider0->setMask(BOX | CIRCLE1 | CIRCLE2);

  circleCollider1 = new CircleCollider2D(world, ColliderType::Dynamic, circle1);
  circleCollider1->setCategoryBits(CIRCLE1);
  circleCollider1->setMask(GROUND | CIRCLE0);

  circleCollider2 = new CircleCollider2D(world, ColliderType::Dynamic, circle2);
  circleCollider2->setCategoryBits(CIRCLE2);
  circleCollider2->setMask(GROUND | CIRCLE0);

  //polygons
  poly0 = new Polygon();
  poly0->setTexture(GETTEXTURE("6"));

//	polyCollider0 = new PolygonCollider2D(world, ColliderType::Static, poly0);

  //sprites
  Sprite *sp0 = new Sprite(GETTEXTURE("4"));
  sp0->transformation({20.0f, 20.0f});
  sp0->setTextureRect(rect(150, 130, 300, 320));
  sp0->setScale({0.3f, 0.3f});
  renderables.push_back(sp0);

  Renderer::setClearColor(0x007B90);
}

TestB2D::~TestB2D() {
  delete camera;
  delete renderer;

  delete boxCollider;
  delete groundCollider;
  delete circleCollider0;
  delete circleCollider1;
  delete circleCollider2;

  for (const auto &r : renderables) {
    delete r;
  }
  delete poly0;

  delete contactListener;
  delete world;
}

void TestB2D::render() {
  renderer->begin();

  for (auto &&r : renderables) {
    renderer->submit(r);
  }

  for (const auto &p : points) {
    renderer->submit(p);
  }

  renderer->submit(poly0);

  renderer->end();
  renderer->flush();
}

void TestB2D::renderImGui() {
  ImGui::Begin("Test Box2D", nullptr);

  //debug
  ImGui::Text("fps: %i", app.getFPS());
  ImGui::Text("tick rate: %i", app.getTPS());
  ImGui::Text("draw calls: %i", Renderer::getDC());
  ImGui::Separator();
  ImGui::Dummy({10.0f, 0.0f});

  ImGui::End();
}

void TestB2D::update(float delta) {
  if (Mouse::isButtonPressed(Mouse::Right)) {
    const vec2 p = Mouse::getPosition(window);
    boxCollider->set(p, boxCollider->getRotation());
    boxCollider->setAwake(true);
  }
}

void TestB2D::fixedUpdate(float delta) {
  world->update(delta, 6, 3);
}

void TestB2D::input(xe::Event &event) {
  switch (event.type) {
    case Event::KeyPressed: {
      if (event.key.code == Keyboard::F1) {
        static bool wireframe = true;
        renderer->enableWireframe(wireframe);
        wireframe = !wireframe;
      }

      if (event.key.code == Keyboard::Up) {
        box->setSize(box->getSize() + 1);
      } else if (event.key.code == Keyboard::Down) {
        box->setSize(box->getSize() - 1);
      }

      if (event.key.code == Keyboard::R) {
        poly0->setVisible(false);

        for (const auto &p : points) {
          delete p;
        }
        points.clear();
        polyPoints.clear();
      }

      if (event.key.code == Keyboard::C) {
        poly0->reshape(polyPoints);
        poly0->setVisible(true);
      }

      if (event.key.code == Keyboard::W) {
        bool wake = boxCollider->isAwake();
        boxCollider->setAwake(!wake);
      }

      if (event.key.code == Keyboard::U) {
        void *data = boxCollider->getUserData();
        const char *s = static_cast<const char *>(data);
        XE_TRACE(s);
      }
      break;
    }

    case Event::MouseButtonPressed: {
      if (event.mouseButton.button == Mouse::Left) {
        const vec2 pos = {event.mouseButton.x, event.mouseButton.y};
        polyPoints.push_back(pos);

        RectangleShape *rs = new RectangleShape({5.0f, 5.0f});
        rs->setColor(color::Green);
        rs->transformation(pos);
        points.push_back(rs);

//				XE_INFO(vec2(event.mouseButton.x, event.mouseButton.y));
      }
      break;
    }

    default: break;
  }
}
