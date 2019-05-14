//
// Created by FLXR on 9/11/2018.
//

#ifndef X808_TESTB2D_HPP
#define X808_TESTB2D_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/physics/2d/physicsworld2d.hpp>
#include <xe/physics/2d/boxcollider2d.hpp>
#include <xe/physics/2d/circlecollider2d.hpp>
#include <xe/physics/2d/polygoncollider2d.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>
#include <xe/gfx/2d/circleshape.hpp>
#include <xe/gfx/2d/polygon.hpp>
#include <xe/gfx/2d/sprite.hpp>

class MyListener : public xe::IContactListener {
public:
	void beginContact(b2Contact *contact) override;
	void endContact(b2Contact *contact) override;
	void preSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
	void postSolve(b2Contact *contact, const b2ContactImpulse *impulse) override;
};

class TestB2D : public xe::Layer {
public:
	explicit TestB2D();
	~TestB2D() override;

	void render() override;
	void renderImGui() override;

	void update(float delta) override;
	void fixedUpdate(float delta) override;

	void input(xe::Event &event) override;

private:
	xe::Camera *camera;
	xe::Renderer2D *renderer;

	//rectangles
	MyListener *contactListener;
	xe::PhysicsWorld2D *world;
	xe::BoxCollider2D *boxCollider;
	xe::Sensor2D *boxSensor;
	xe::BoxCollider2D *groundCollider;

	xe::RectangleShape *box;
	xe::RectangleShape *sensor;
	xe::RectangleShape *ground;
	xe::RectangleShape *jdm;

	//circles
	xe::CircleShape *circle0;
	xe::CircleShape *circle1;
	xe::CircleShape *circle2;
	xe::CircleCollider2D *circleCollider0;
	xe::CircleCollider2D *circleCollider1;
	xe::CircleCollider2D *circleCollider2;

	//polygons
	xe::Polygon *poly0;
	xe::PolygonCollider2D *polyCollider0;

	std::vector<xe::IRenderable2D *> renderables;
	std::vector<xe::IRenderable2D *> points;

	std::vector<xe::vec2> polyPoints;
};

#endif //X808_TESTB2D_HPP
