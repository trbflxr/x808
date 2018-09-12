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
	camera = new Camera(mat4::ortho(0, width, 0, height, -1, 1000));

	renderer = new BatchRenderer2D(width, height, camera);


	box = new Sprite(GETTEXTURE("1"), true, color::WHITE);
	ground = new Sprite(GETTEXTURE("2"), true, color::WHITE);
	sprite = new Sprite(GETTEXTURE("3"), true, color::WHITE);

	boxTransform = new Transform2D({400.0f, 400.0f, 1.0f}, {50.0f, 50.0f});
	groundTransform = new Transform2D({400.0f, 50.0f, 2.0f}, {500.0f, 5.0f}, 20.0f);
	spriteTransform = new Transform2D({400.0f, 400.0f, 3.0f}, {50.0f, 50.0f});

	world = new PhysicsWorld2D({0.0f, -9.8f});

	boxCollider = new BoxCollider2D(world, ColliderType::Dynamic, boxTransform);
	boxCollider->setDensity(20.5f);
	boxCollider->setFriction(0.2f);
	boxCollider->setRestitution(0.5f);

	groundCollider = new BoxCollider2D(world, ColliderType::Static, groundTransform);
}

TestB2D::~TestB2D() {
	delete camera;
	delete renderer;

	delete world;

	delete boxCollider;
	delete groundCollider;

	delete box;
	delete ground;
	delete sprite;

	delete boxTransform;
	delete groundTransform;
	delete spriteTransform;
}

void TestB2D::render() {
	renderer->submit(box, boxTransform);
	renderer->submit(ground, groundTransform);
	renderer->submit(sprite, spriteTransform);

	renderer->renderSprites();
	renderer->renderText();

	renderer->clear();
}

void TestB2D::update(float delta) {
	if (Mouse::isButtonPressed(Mouse::Left)) {
		const vec2 p = Mouse::getPosition(window);
		boxCollider->set(p, boxCollider->getRotation());
		boxCollider->setLinearVelocity({0, 0});
		boxCollider->setAngularVelocity(0);
		boxCollider->setAwake(true);
	}

	world->update(1.0f / 60.0f, 8, 3);
}

void TestB2D::input(xe::Event &event) {
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
		static bool wake = false;
		boxCollider->setAwake(wake);
		wake = !wake;
	}
}

void TestB2D::tick() {

}
