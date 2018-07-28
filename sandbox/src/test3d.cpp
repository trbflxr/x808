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
#include <gfx/lights/shadowmapshader.hpp>
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

	camera = new Camera(mat4::perspective(80.0f, 8.0f / 6.0f, 0.1f, 1000));

	player = new DummyPlayer(camera);

	renderer = new ForwardRenderer(800, 600, camera, 2048);
	rendererSystem = new ForwardRendererSystem(renderer);
	renderingPipeline.addSystem(*rendererSystem);

	directionalLight = new DirectionalLight(GETSHADER("forwardDirectional"), 0.4f, color::WHITE);
	directionalLight->transform.setRotation(quat(vec3::XAXIS, to_rad(-45)));
	renderer->addLight(directionalLight);

	pointLight = new PointLight(GETSHADER("forwardPoint"), {3, 1, -5}, {0, 0, 1}, 0.5f, color::RED);
	renderer->addLight(pointLight);

	pointLight2 = new PointLight(GETSHADER("forwardPoint"), {1, 1, -2}, {0, 0, 1}, 0.5f, color::BLUE);
	renderer->addLight(pointLight2);

	pointLight3 = new PointLight(GETSHADER("forwardPoint"), {-1.5f, 3.0f, -13.0f}, {0, 0, 0.5f}, 0.7f,
	                             color::PINK);
	renderer->addLight(pointLight3);

	pointLight4 = new PointLight(GETSHADER("forwardPoint"), {-1.5f, 3.0f, -17.0f}, {0, 0, 0.5f}, 0.7f,
	                             color::CYAN);
	renderer->addLight(pointLight4);

	hookSpotLight = false;
	spotLight = new SpotLight(GETSHADER("forwardSpot"), {2.789f, 0.350f, -5.662f},
	                          {0.107f, -0.132f, -0.986f}, 0.95f, {0.1f, 0.1f, 0.02f}, 0.3f, color::WHITE);
	renderer->addLight(spotLight);


	monkeyMaterial = new Material(GETTEXTURE("2"), 50, 2.2f);
	monkeyMaterial2 = new Material(GETTEXTURE("4"), 1, 0.2f);
	rockMaterial = new Material(GETTEXTURE("rock"), 2, 0.2f);
	stallMaterial = new Material(GETTEXTURE("stall"), 2, 0.2f);

	planeMaterial0 = new Material(GETTEXTURE("bgr"), 3, 0.1f);

	planeMaterial1 = new Material(GETTEXTURE("bricks"), 4, 0.5f,
	                              GETTEXTURE("bricksNormal"), GETTEXTURE("bricksDisp"), 0.03f, -0.5f);

	planeMaterial2 = new Material(GETTEXTURE("bricks2"), 8, 1.0f,
	                              GETTEXTURE("bricksNormal2"), GETTEXTURE("bricksDisp2"), 0.02f, -0.5f);

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
	transform.transform.setRotation(quat::rotationZ(to_rad(0)));
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
	transform.transform.setTranslation({0, -5, -9});
	transform.transform.setScale({3.4f, 3.4f, 3.4f});
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
//	SpriteComponent *s = ecs.getComponent<SpriteComponent>(ui->spriteHandle);

	renderer->begin();

	ecs.updateSystems(renderingPipeline, 0.0f);

	renderer->flush();
}

void Test3D::tick() {
//	XE_INFO("dir:", player->getCamera()->transform.getRotation().getForward());

	char buff[1024];
	sprintf(buff, "fps: %u | ups: %u | frame time: %f ms | DC: %u",
	        app.getFPS(), app.getUPS(), app.getFrameTime(), Renderer::getDC());

	app.getWindow().setTitle(buff);
}

void Test3D::update(float delta) {
	player->update(delta);

	ecs.updateSystems(mainSystems, delta);

	if (hookSpotLight) {
		spotLight->setPosition(camera->transform.getTranslation());
		spotLight->setDirection(player->getCamera()->transform.getRotation().getForward());
	}
}

void Test3D::fixedUpdate(float delta) {
	if (Keyboard::isKeyPressed(Keyboard::Key::Q)) {
		float a = renderer->getAmbientLight()->getIntensity();
		a += 1 * delta;
		renderer->getAmbientLight()->setIntensity(a);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
		float a = renderer->getAmbientLight()->getIntensity();
		if ((a -= 1 * delta) < 0) a = 0;
		renderer->getAmbientLight()->setIntensity(a);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Z)) {
		float a = directionalLight->getIntensity();
		a += 1 * delta;
		directionalLight->setIntensity(a);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::X)) {
		float a = directionalLight->getIntensity();
		if ((a -= 1 * delta) < 0) a = 0;
		directionalLight->setIntensity(a);
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
		directionalLight->transform.rotate(vec3::YAXIS, to_rad(1));
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
		directionalLight->transform.rotate(vec3::YAXIS, to_rad(-1));
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
		directionalLight->transform.rotate(vec3::XAXIS, to_rad(1));
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
		directionalLight->transform.rotate(vec3::XAXIS, to_rad(-1));
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
