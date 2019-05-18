//
// Created by FLXR on 5/18/2019.
//

#include "examplebox2d.hpp"
#include <xe/resources/texturemanager.hpp>
#include <xe/ui/imgui/imgui.h>

using namespace xe;

ExampleBox2D *ExampleBox2D::instance = nullptr;

ExampleBox2D::ExampleBox2D() :
    density(130.0f),
    friction(0.2f),
    restitution(0.5f),
    boxHooked(false) {

  const float width = app.getWindowSize().x;
  const float height = app.getWindowSize().y;

  camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f));
  renderer = new Renderer2D(width, height, camera);

  contactListener = new MyListener();
  world = new PhysicsWorld2D({0.0f, -9.8f});
  world->setContactListener(contactListener);

  box = new RectangleShape({50.0f, 50.0f});
  box->transformation({400.0f, 400.0f});
  boxCollider = new BoxCollider2D(world, ColliderType::Dynamic, box);
  boxCollider->setDensity(density);
  boxCollider->setFriction(friction);
  boxCollider->setRestitution(restitution);
  boxCollider->setCategoryBits(BOX);
  boxCollider->setMask(GROUND | CIRCLE0 | CIRCLE2);
  boxCollider->setUserData((void *) "box");

  ground0 = new RectangleShape({500.0f, 5.0f});
  ground0->transformation({400.0f, 50.0f}, 20.0f);
  groundCollider0 = new BoxCollider2D(world, ColliderType::Static, ground0);
  groundCollider0->setCategoryBits(GROUND);
  groundCollider0->setMask(BOX | CIRCLE1 | CIRCLE2);

  ground1 = new RectangleShape({500.0f, 5.0f});
  ground1->transformation({850.0f, 165.0f}, 10.0f);
  groundCollider1 = new BoxCollider2D(world, ColliderType::Static, ground1);
  groundCollider1->setCategoryBits(GROUND);
  groundCollider1->setMask(BOX | CIRCLE1 | CIRCLE2);

  circle0 = new CircleShape(100.0f);
  circle0->transformation({370.0f, 200.0f});
  circleCollider0 = new CircleCollider2D(world, ColliderType::Static, circle0);
  circleCollider0->setCategoryBits(CIRCLE0);
  circleCollider0->setMask(BOX | CIRCLE1 | CIRCLE2);

  circle1 = new CircleShape(50.0f);
  circle1->transformation({470.0f, 500.0f});
  circleCollider1 = new CircleCollider2D(world, ColliderType::Dynamic, circle1);
  circleCollider1->setCategoryBits(CIRCLE1);
  circleCollider1->setMask(GROUND | CIRCLE0);

  circle2 = new CircleShape(100.0f);
  circle2->transformation({530.0f, 600.0f});
  circleCollider2 = new CircleCollider2D(world, ColliderType::Dynamic, circle2);
  circleCollider2->setDensity(10.5f);
  circleCollider2->setFriction(0.2f);
  circleCollider2->setRestitution(0.5f);
  circleCollider2->setCategoryBits(CIRCLE2);
  circleCollider2->setMask(GROUND | CIRCLE0 | BOX);
}

ExampleBox2D::~ExampleBox2D() {
  delete camera;
  delete renderer;
  delete box;
  delete ground0;
  delete ground1;
  delete circle0;
  delete circle1;
  delete circle2;

  delete boxCollider;
  delete groundCollider0;
  delete groundCollider1;
  delete circleCollider0;
  delete circleCollider1;
  delete circleCollider2;

  delete contactListener;
  delete world;
}

void ExampleBox2D::init() {
  box->setColor(color::Red);
  ground0->setTexture(GETTEXTURE("grass"));
  ground1->setTexture(GETTEXTURE("grass"));
  circle0->setTexture(GETTEXTURE("test1"));
  circle1->setTexture(GETTEXTURE("test2"));
  circle2->setTexture(GETTEXTURE("test3"));
}

void ExampleBox2D::render() {
  renderer->begin();

  renderer->submit(ground0);
  renderer->submit(ground1);
  renderer->submit(circle0);
  renderer->submit(circle1);
  renderer->submit(circle2);
  renderer->submit(box);

  renderer->end();
  renderer->flush();
}

void ExampleBox2D::renderImGui() {
  ImGui::Begin("Physics 2D", nullptr);

  static bool fixedRot = false;
  if (ImGui::Checkbox("Box fixedRotation", &fixedRot)) {
    boxCollider->setFixedRotation(fixedRot);
  }

  if (ImGui::DragFloat("Box density", &density, 0.1f, 0.1f, 300.0f)) {
    boxCollider->setDensity(density);
    boxCollider->recreate();
  }

  if (ImGui::DragFloat("Box friction", &friction, 0.001f, 0.0f, 1.0f)) {
    boxCollider->setFriction(friction);
    boxCollider->recreate();
  }

  if (ImGui::DragFloat("Box restitution", &restitution, 0.001f, 0.0f, 1.0f)) {
    boxCollider->setRestitution(restitution);
    boxCollider->recreate();
  }

  ImGui::End();
}

void ExampleBox2D::update(float delta) {
  if (boxHooked) {
    boxCollider->set(mousePos, boxCollider->getRotation());
    boxCollider->setAwake(true);
    boxCollider->setAngularVelocity(0.0f);
    boxCollider->setLinearVelocity({0.0f, 0.0f});
  }
}

void ExampleBox2D::fixedUpdate(float delta) {
  world->update(delta, 6, 3);
}

void ExampleBox2D::input(xe::Event &event) {
  if (event.type == Event::MouseButtonPressed) {
    if (event.mouseButton.button == Mouse::Left) {
      boxHooked = true;
      mousePos = Mouse::getPosition(window);
    }
  }
  if (event.type == Event::MouseButtonReleased) {
    if (event.mouseButton.button == Mouse::Left) {
      boxHooked = false;
    }
  }
  if (event.type == Event::MouseMoved) {
    if (boxHooked) {
      mousePos = vec2(event.mouseMove.x, event.mouseMove.y);
    }
  }
}

//contact listner
void MyListener::beginContact(b2Contact *contact) {
//  XE_TRACE("begin contact");
}

void MyListener::endContact(b2Contact *contact) {
//  XE_TRACE("end contact");
}

void MyListener::preSolve(b2Contact *contact, const b2Manifold *oldManifold) {
//  XE_TRACE("presolve contact");
}

void MyListener::postSolve(b2Contact *contact, const b2ContactImpulse *impulse) {
//  XE_TRACE("postsolve contact");
}
