//
// Created by FLXR on 9/11/2018.
//

#include <xe/resources/texturemanager.hpp>
#include "testb2d.hpp"

using namespace xe;

TestB2D::TestB2D() {
	const float width = app.getConfig().width;
	const float height = app.getConfig().height;

	TextureParameters params;

	TextureManager::add(new Texture("0", "assets/textures/enemyspotted.png", params));
	TextureManager::add(new Texture("1", "assets/textures/enemyspotted.png", params));
	TextureManager::add(new Texture("2", "assets/textures/enemyspotted.png", params));
	TextureManager::add(new Texture("3", "assets/textures/jdm.png", params));
	TextureManager::add(new Texture("4", "assets/textures/star.png", params));
	TextureManager::add(new Texture("5", "assets/textures/cosmic.png", params));
	TextureManager::add(new Texture("6", "assets/textures/test7.png", params));
	TextureManager::add(new Texture("7", "assets/textures/test8.png", params));

	uint texCount = 7;


	//create camera
	camera = new Camera(mat4::ortho(-width, width, -height, height, -1, 1000));

	renderer = new BatchRenderer2D(width, height, camera);

	//render system
	spriteRendererSystem = new SpriteRendererSystem(renderer);
	textRendererSystem = new TextRendererSystem(renderer);

	renderingPipeline.addSystem(*spriteRendererSystem);
	renderingPipeline.addSystem(*textRendererSystem);


	SpriteComponent *s0 = new SpriteComponent(GETTEXTURE("1"), true, color::WHITE);
	SpriteComponent *s1 = new SpriteComponent(GETTEXTURE("2"), true, color::WHITE);
	SpriteComponent *s2 = new SpriteComponent(GETTEXTURE("3"), true, color::WHITE);

	Transform2DComponent *t0 = new Transform2DComponent(vec2(-20, -200), vec2(500, 5), 1.0f);
	Transform2DComponent *t1 = new Transform2DComponent(vec2(-10.0f, -10.0f), vec2(50.0f), 2.0f);
	Transform2DComponent *t2 = new Transform2DComponent(vec2(-10.0f, -10.0f), vec2(50.0f), 3.0f);

	sprite1 = ecs.makeEntity(s0, t0);
	sprite = ecs.makeEntity(s1, t1);
	ecs.makeEntity(s2, t2);

	world = new PhysicsWorld2D(vec2(0.0f, -9.8f));

	world->test({20, 20}, {50, 50}, false);

	world->test({-20, -200}, {500, 5}, true);
}

TestB2D::~TestB2D() {
	delete camera;
	delete renderer;

	delete spriteRendererSystem;
	delete textRendererSystem;

	delete world;
}

void TestB2D::render() {
	ecs.updateSystems(renderingPipeline, 0.0f);

	renderer->renderSprites();
	renderer->renderText();

	renderer->clear();
}

void TestB2D::update(float delta) {
	static Transform2DComponent *t = ecs.getComponent<Transform2DComponent>(sprite);
	static Transform2DComponent *t1 = ecs.getComponent<Transform2DComponent>(sprite1);

	world->update(1.0f / 60.0f, 8, 3);


	t->bounds.setPosition(world->getPos(false) - t->bounds.getSize() / 2.0f);
	t->bounds.setRotation(world->getRot(false));

	t1->bounds.setPosition(world->getPos(true) - t1->bounds.getSize() / 2.0f);
	t1->bounds.setRotation(world->getRot(true));


	ecs.updateSystems(mainSystems, delta);
}

void TestB2D::input(xe::Event &event) {

}
