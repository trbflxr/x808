//
// Created by FLXR on 9/11/2018.
//

#ifndef X808_TESTB2D_HPP
#define X808_TESTB2D_HPP


#include <xe/gfx/layer2d.hpp>
#include <xe/physics/2d/physicsworld2d.hpp>
#include <xe/physics/2d/boxcollider2d.hpp>
#include <xe/physics/2d/circlecollider2d.hpp>
#include <xe/physics/2d/polygoncollider2d.hpp>
#include <xe/gfx/rectangleshape.hpp>
#include <xe/gfx/circleshape.hpp>
#include <xe/gfx/polygon.hpp>
#include <xe/gfx/sprite.hpp>

class TestB2D : public xe::Layer2D {
public:
	explicit TestB2D();
	~TestB2D() override;

	void renderScene() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

private:
	xe::Camera *camera;

	xe::BatchRenderer2D *renderer;

	//rectangles
	xe::PhysicsWorld2D *world;
	xe::BoxCollider2D *boxCollider;
	xe::BoxCollider2D *groundCollider;

	xe::RectangleShape *box;
	xe::RectangleShape *ground;
	xe::RectangleShape *jdm;

	//circles
	xe::CircleShape *circle0;
	xe::CircleCollider2D *circleCollider0;

	//polygons
	xe::Polygon *poly0;
	xe::PolygonCollider2D *polyCollider0;

	std::vector<xe::IRenderable2D *> renderables;
	std::vector<xe::IRenderable2D *> points;

	std::vector<xe::vec2> polyPoints;
};

#endif //X808_TESTB2D_HPP
