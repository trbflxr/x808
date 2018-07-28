//
// Created by FLXR on 7/24/2018.
//

#include <resources/texturemanager.hpp>
#include <gfx/renderer.hpp>
#include "testui.hpp"

TestUI::TestUI() :
		ecs(app.getEcs()) {

	//render system
	spriteRenderer = new SpriteRendererSystem(renderer);

	renderingPipeline.addSystem(*spriteRenderer);

	//main systems
	cameraSystem = new OrthoCameraSystem(renderer);

	mainSystems.addSystem(*cameraSystem);

	//create camera
	CameraComponent camera(mat4::ortho(-80.0f, 80.0f, -60.0f, 60.0f, -1, 1000));
	cameraEntity = ecs.makeEntity(camera);

	//sprite components
	SpriteComponent sprite;
	Transform2DComponent transform;


	sprite.texture = GETTEXTURE("default");

	transform.zIndex = 0;
	transform.bounds.setPosition(40, 25);
	transform.bounds.setSize(30, 30);

	spriteHandle = ecs.makeEntity(sprite, transform);
}

TestUI::~TestUI() {
	delete spriteRenderer;
	delete cameraSystem;
}

void TestUI::render() {
	Renderer::clear(RendererBufferType::RENDERER_BUFFER_DEPTH);

	renderer->begin();

	ecs.updateSystems(renderingPipeline, 0.0f);

	renderer->flush();
}

void TestUI::tick() { }

void TestUI::update(float delta) {
	ecs.updateSystems(mainSystems, delta);
}

void TestUI::fixedUpdate(float delta) { }

void TestUI::input(Event &event) { }
