//
// Created by FLXR on 7/12/2018.
//

#include <gfx/renderer.hpp>
#include <gfx/api/texture2d.hpp>
#include <resources/texturemanager.hpp>
#include <resources/shadermanager.hpp>
#include <gfx/color.hpp>
#include <ecs/components/modelcomponent.hpp>
#include <ecs/components/transformcomponent.hpp>
#include "test3d.hpp"

Test3D::Test3D(TestUI *ui) :
		ecs(app.getEcs()),
		ui(ui) {

	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	TextureParameters params(TextureFilter::NEAREST);
	TextureManager::add(Texture2D::create("rock", "assets/textures/rock.png", params));
	TextureManager::add(Texture2D::create("2", "assets/textures/test3.png", params));
	TextureManager::add(Texture2D::create("4", "assets/textures/test5.png", params));
	TextureManager::add(Texture2D::create("stall", "assets/textures/stall.png", params));
	TextureManager::add(Texture2D::create("bricks", "assets/textures/bricks.jpg", params));
	TextureManager::add(Texture2D::create("bricks2", "assets/textures/bricks2.jpg", params));
	TextureManager::add(Texture2D::create("bricksNormal", "assets/textures/bricksNormal.jpg", params));
	TextureManager::add(Texture2D::create("bricksNormal2", "assets/textures/bricksNormal2.png", params));
	TextureManager::add(Texture2D::create("bricksDisp", "assets/textures/bricksDisp.png", params));
	TextureManager::add(Texture2D::create("bricksDisp2", "assets/textures/bricksDisp2.jpg", params));
	TextureManager::add(Texture2D::create("bgr", "assets/textures/bgr.jfif", params));

	camera = new FPSCamera(mat4::perspective(80.0f, 8.0f / 6.0f, 0.1f, 1000));

	player = new DummyPlayer(camera);

	renderer = new ForwardRenderer(800, 600, 2048, camera);
	rendererSystem = new ForwardRendererSystem(renderer);
	renderingPipeline.addSystem(*rendererSystem);

	ambientLight = new AmbientLight(GETSHADER("forwardAmbient"), 0.05f, color::WHITE);
	renderer->setAmbientLight(ambientLight);

	directionalLight = new DirectionalLight(GETSHADER("forwardDirectional"), true,
	                                        {-0.665f, -0.745f, -0.053f}, 0.4f, color::WHITE);
	renderer->addLight(directionalLight);

	pointLight = new PointLight(GETSHADER("forwardPoint"), false, {3, 1, -5}, {0, 0, 1}, 0.5f, color::RED);
	renderer->addLight(pointLight);

	pointLight2 = new PointLight(GETSHADER("forwardPoint"), false, {1, 1, -2}, {0, 0, 1}, 0.5f, color::BLUE);
	renderer->addLight(pointLight2);

	pointLight3 = new PointLight(GETSHADER("forwardPoint"), false, {-1.5f, 3.0f, -13.0f}, {0, 0, 0.5f}, 0.7f,
	                             color::PINK);
	renderer->addLight(pointLight3);

	pointLight4 = new PointLight(GETSHADER("forwardPoint"), false, {-1.5f, 3.0f, -17.0f}, {0, 0, 0.5f}, 0.7f,
	                             color::CYAN);
	renderer->addLight(pointLight4);

	hookSpotLight = false;
	spotLight = new SpotLight(GETSHADER("forwardSpot"), false, {2.789f, 0.350f, -5.662f},
	                          {0.107f, -0.132f, -0.986f}, 0.95f, {0.1f, 0.1f, 0.02f}, 0.3f, color::WHITE);
	renderer->addLight(spotLight);


	monkeyMaterial = new Material(GETTEXTURE("2"), 50, 2.2f);
	monkeyMaterial2 = new Material(GETTEXTURE("4"), 1, 0.2f);
	rockMaterial = new Material(GETTEXTURE("rock"), 2, 0.2f);
	stallMaterial = new Material(GETTEXTURE("stall"), 2, 0.2f);

	planeMaterial0 = new Material(GETTEXTURE("bgr"), 3, 0.1f);

	planeMaterial1 = new Material(GETTEXTURE("bricks"), 3, 0.1f,
	                              GETTEXTURE("bricksNormal"), GETTEXTURE("bricksDisp"), 0.02f, -0.5f);

	planeMaterial2 = new Material(GETTEXTURE("bricks2"), 3, 0.1f,
	                              GETTEXTURE("bricksNormal2"));

	rockMesh = new Mesh("assets/models/rock.obj");
	monkeyMesh = new Mesh("assets/models/monkey3.obj");
	stallMesh = new Mesh("assets/models/stall.obj");
	planeMesh0 = new Mesh("assets/models/plane0.obj");
	planeMesh1 = new Mesh("assets/models/plane1.obj");

	ModelComponent model;
	TransformComponent transform;

	model.mesh = monkeyMesh;
	model.material = monkeyMaterial;
	transform.transform.setTranslation({5, 0, -5});
	transform.transform.setRotation(quat::rotationZ(to_rad(30)));
	monkeyModel = ecs.makeEntity(model, transform);

	model.mesh = monkeyMesh;
	model.material = monkeyMaterial2;
	transform.transform.setTranslation({3, 0, -8});
	monkeyModel2 = ecs.makeEntity(model, transform);

	model.mesh = rockMesh;
	model.material = rockMaterial;
	transform.transform.setTranslation({0, 0, -5});
	transform.transform.setRotation(quat::rotationZ(to_rad(5)));
	rockModel = ecs.makeEntity(model, transform);

	model.mesh = stallMesh;
	model.material = stallMaterial;
	transform.transform.setTranslation({0, 0, -15});
	transform.transform.setRotation(quat::rotationY(to_rad(-90)));
	stallModel = ecs.makeEntity(model, transform);

//	planes
	model.mesh = planeMesh0;
	model.material = planeMaterial0;
	transform.transform.setTranslation({15, -3, -5});
	transform.transform.setScale({0.4f, 0.4f, 0.4f});
	planeModel0 = ecs.makeEntity(model, transform);

	model.mesh = planeMesh0;
	model.material = planeMaterial1;
	transform.transform.setTranslation({22, -3, -5});
	transform.transform.setScale({0.4f, 0.4f, 0.4f});
	planeModel1 = ecs.makeEntity(model, transform);

	model.mesh = planeMesh0;
	model.material = planeMaterial2;
	transform.transform.setTranslation({29, -3, -5});
	transform.transform.setScale({0.4f, 0.4f, 0.4f});
	planeModel2 = ecs.makeEntity(model, transform);
}

Test3D::~Test3D() {
	delete renderer;
	delete ambientLight;
	delete directionalLight;
	delete pointLight;
	delete pointLight2;
	delete pointLight3;
	delete pointLight4;
	delete spotLight;

	delete rockMesh;
	delete monkeyMesh;
	delete stallMesh;
	delete planeMesh0;
	delete planeMesh1;

	delete rockMaterial;
	delete monkeyMaterial;
	delete monkeyMaterial2;
	delete stallMaterial;
	delete planeMaterial0;
	delete planeMaterial1;
	delete planeMaterial2;

	delete renderer;
	delete rendererSystem;

	delete camera;

	delete player;
}

void Test3D::render() {
	SpriteComponent *s = ecs.getComponent<SpriteComponent>(ui->spriteHandle);

	renderer->begin();

	ecs.updateSystems(renderingPipeline, 0.0f);

	renderer->flush(s);

//	frameBuffer->bind();
//	frameBuffer->clear();
////
//	frameBuffer->unbind();
//
//
//	Renderer::setViewport(0, 0, 800, 600);
//	Renderer::setClearColor(color::BLACK);
//
//	//draw framebuffer to ui
//	SpriteComponent *s = ecs.getComponent<SpriteComponent>(ui->spriteHandle);
//	s->texture = frameBuffer->getTexture();
//
//	renderer->render(monkeyModel, player->getCamera());
//	renderer->render(monkeyModel2, player->getCamera());
//	renderer->render(stallModel, player->getCamera());
//	renderer->render(rockModel, player->getCamera());
//
//	renderer->render(planeModel0, player->getCamera());
//	renderer->render(planeModel1, player->getCamera());
//	renderer->render(planeModel2, player->getCamera());
}

void Test3D::tick() {
//	XE_INFO("dir:", player->getCamera()->getForwardDirection(player->getCamera()->getOrientation()));

	char buff[1024];
	sprintf(buff, "fps: %u | ups: %u | frame time: %f ms | DC: %u",
	        app.getFPS(), app.getUPS(), app.getFrameTime(), Renderer::getDC());

	app.getWindow().setTitle(buff);
}

void Test3D::update(float delta) {
	player->update(delta);

	ecs.updateSystems(mainSystems, delta);

	if (hookSpotLight) {
		spotLight->setPosition(camera->getPosition());
		spotLight->setDirection(camera->getForwardDirection(camera->getOrientation()));
	}
}

void Test3D::fixedUpdate(float delta) {
	if (Keyboard::isKeyPressed(Keyboard::Key::Q)) {
		float a = ambientLight->getIntensity();
		a += 1 * delta;
		ambientLight->setIntensity(a);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
		float a = ambientLight->getIntensity();
		if ((a -= 1 * delta) < 0) a = 0;
		ambientLight->setIntensity(a);
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::R)) {
		vec3 a = directionalLight->getDirection();
		a.y += 0.03f;
		directionalLight->setDirection(a);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::T)) {
		vec3 a = directionalLight->getDirection();
		a.y -= 0.03f;
		directionalLight->setDirection(a);
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Y)) {
		float a = planeMaterial2->getDispMapBias();
		a += 0.005f;
		planeMaterial2->setDispMapBias(a);
		XE_INFO(a);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::U)) {
		float a = planeMaterial2->getDispMapBias();
		a -= 0.005f;
		planeMaterial2->setDispMapBias(a);
		XE_INFO(a);
	}
}

void Test3D::input(Event &event) {
	player->input(event);

	if (event.type == Event::KeyPressed) {
		if (event.key.code == Keyboard::Key::Num1) {
			static bool enabled = true;
			enabled = !enabled;
			directionalLight->setEnabled(enabled);
		}
		if (event.key.code == Keyboard::Key::Num2) {
			static bool enabled = true;
			enabled = !enabled;
			pointLight->setEnabled(enabled);
		}
		if (event.key.code == Keyboard::Key::Num3) {
			static bool enabled = true;
			enabled = !enabled;
			pointLight2->setEnabled(enabled);
		}
		if (event.key.code == Keyboard::Key::H) {
			hookSpotLight = !hookSpotLight;
		}
	}
}
