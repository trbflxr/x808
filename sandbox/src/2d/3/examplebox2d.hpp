//
// Created by FLXR on 5/18/2019.
//

#ifndef X808_EXAMPLEBOX2D_HPP
#define X808_EXAMPLEBOX2D_HPP


#include "iexamplelayer.hpp"
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>
#include <xe/gfx/2d/circleshape.hpp>
#include <xe/physics/2d/physicsworld2d.hpp>
#include <xe/physics/2d/boxcollider2d.hpp>
#include <xe/physics/2d/circlecollider2d.hpp>

class MyListener : public xe::IContactListener {
public:
  void beginContact(b2Contact *contact) override;
  void endContact(b2Contact *contact) override;
  void preSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
  void postSolve(b2Contact *contact, const b2ContactImpulse *impulse) override;
};

class ExampleBox2D : public IExampleLayer {
public:
  void init() override;

  void render() override;
  void renderImGui() override;

  void update(float delta) override;
  void fixedUpdate(float delta) override;

  void input(xe::Event &event) override;

  IEXAMPLE_LAYER_METHODS(ExampleBox2D)

protected:
  explicit ExampleBox2D();
  ~ExampleBox2D() override;

private:
  static ExampleBox2D *instance;

  xe::Camera *camera;
  xe::Renderer2D *renderer;

  xe::RectangleShape *box;
  xe::RectangleShape *ground0;
  xe::RectangleShape *ground1;
  xe::CircleShape *circle0;
  xe::CircleShape *circle1;
  xe::CircleShape *circle2;

  MyListener *contactListener;
  xe::PhysicsWorld2D *world;
  xe::BoxCollider2D *boxCollider;
  xe::BoxCollider2D *groundCollider0;
  xe::BoxCollider2D *groundCollider1;
  xe::CircleCollider2D *circleCollider0;
  xe::CircleCollider2D *circleCollider1;
  xe::CircleCollider2D *circleCollider2;

  static constexpr uint16 GROUND = BIT(1);
  static constexpr uint16 BOX = BIT(2);
  static constexpr uint16 CIRCLE0 = BIT(3);
  static constexpr uint16 CIRCLE1 = BIT(4);
  static constexpr uint16 CIRCLE2 = BIT(5);

  float density;
  float friction;
  float restitution;

  bool boxHooked;
  xe::vec2 mousePos;
};


#endif //X808_EXAMPLEBOX2D_HPP
