//
// Created by FLXR on 9/11/2018.
//

#ifndef X808_TESTB2D_HPP
#define X808_TESTB2D_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/camera.hpp>
#include <xe/gfx/2d/batchrenderer2d.hpp>
#include <xe/physics/2d/physicsworld2d.hpp>
#include <xe/physics/2d/boxcollider2d.hpp>
#include <xe/physics/2d/circlecollider2d.hpp>
#include <xe/gfx/rectangleshape.hpp>
#include <xe/gfx/circleshape.hpp>

class TestB2D : public xe::Layer {
public:
	explicit TestB2D();
	~TestB2D() override;

	void render() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

	void tick() override;

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
};

#endif //X808_TESTB2D_HPP
