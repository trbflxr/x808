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

Test3D::Test3D(DebugUI *ui) :
		ui(ui) {

	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	TextureParameters params(TextureFilter::LINEAR);
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

	//init objects
	ModelComponent model;
	TransformComponent transform;

	camera = new Camera(mat4::perspective(80.0f, 8.0f / 6.0f, 0.1f, 1000));

	DummyPlayerComponent playerComponent(camera);
	player = ecs.makeEntity(playerComponent, transform);

	playerControlSystem = new DummyPlayerControlSystem();
	mainSystems.addSystem(*playerControlSystem);

	renderer = new ForwardRenderer(800, 600, camera);
	rendererSystem = new ForwardRendererSystem(renderer);
	renderingPipeline.addSystem(*rendererSystem);

	directionalLight = new DirectionalLight(GETSHADER("forwardDirectional"), 0.4f, color::WHITE, 10);
	directionalLight->transform.setRotation(quat(vec3::XAXIS, -45.0f));
	renderer->addLight(directionalLight);

	pointLight = new PointLight(GETSHADER("forwardPoint"), {0, 0, 1}, 0.5f, color::RED);
	pointLight->transform.setTranslation({3, 1, -5});
//	renderer->addLight(pointLight);

	pointLight2 = new PointLight(GETSHADER("forwardPoint"), {0, 0, 1}, 0.5f, color::BLUE);
	pointLight2->transform.setTranslation({1, 1, -2});
//	renderer->addLight(pointLight2);

	pointLight3 = new PointLight(GETSHADER("forwardPoint"), {0, 0, 0.5f}, 0.7f, color::PINK);
	pointLight3->transform.setTranslation({-1.5f, 3.0f, -13.0f});
//	renderer->addLight(pointLight3);

	pointLight4 = new PointLight(GETSHADER("forwardPoint"), {0, 0, 0.5f}, 0.7f, color::CYAN);
	pointLight4->transform.setTranslation({-1.5f, 3.0f, -17.0f});
//	renderer->addLight(pointLight4);

	hookSpotLight = false;
	spotLight = new SpotLight(GETSHADER("forwardSpot"), {0.0f, 0.0f, 0.02f}, 0.2f, color::WHITE, 90.0f, 7);
	spotLight->transform.setTranslation({8.142f, -3.811f, -5.968f});
	spotLight->transform.setRotation(quat(vec3::YAXIS, -90.0f));
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
	cubeMesh = new Mesh("assets/models/cube.obj");

	model.mesh = monkeyMesh;
	model.material = monkeyMaterial;
	transform.transform.setTranslation({5, 0, -5});
	transform.transform.setRotation(quat::rotationZ(30.0f));
	monkeyModel = ecs.makeEntity(model, transform);

	model.mesh = monkeyMesh;
	model.material = monkeyMaterial2;
	transform.transform.setTranslation({3, 0, -8});
	transform.transform.setRotation(quat::rotationZ(0.0f));
	monkeyModel2 = ecs.makeEntity(model, transform);

	model.mesh = rockMesh;
	model.material = rockMaterial;
	transform.transform.setTranslation({0, 0, -5});
	transform.transform.setRotation(quat::rotationZ(5.0f));
	rockModel = ecs.makeEntity(model, transform);

	model.mesh = stallMesh;
	model.material = stallMaterial;
	transform.transform.setTranslation({0, 0, -15});
	transform.transform.setRotation(quat::rotationY(-90.0f));
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


	//cube
	model.mesh = cubeMesh;
	model.material = planeMaterial2;
	transform.transform.setTranslation({10, -4.5f, -5});
	transform.transform.rotate(vec3::YAXIS, 45.0f);
	cubeModel = ecs.makeEntity(model, transform);
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
	delete cubeMesh;

	delete rockMaterial;
	delete monkeyMaterial;
	delete monkeyMaterial2;
	delete stallMaterial;
	delete planeMaterial0;
	delete planeMaterial1;
	delete planeMaterial2;

	delete renderer;
	delete rendererSystem;
	delete playerControlSystem;

	delete camera;
}

void Test3D::render() {
	renderer->begin();

	ecs.updateSystems(renderingPipeline, 0.0f);

	renderer->flush();
}

void Test3D::tick() {
//	static DummyPlayerComponent *p = ecs.getComponent<DummyPlayerComponent>(player);

//	XE_INFO("dir:", camera->transform.getRotation().getForward());
//	XE_INFO("pos:", camera->transform.getTranslation());

//	char buff[1024];
//	sprintf(buff, "fps: %u | ups: %u | frame time: %f ms | DC: %u",
//	        app.getFPS(), app.getUPS(), app.getFrameTime(), Renderer::getDC());
//
//	app.getWindow().setTitle(buff);
}

void Test3D::update(float delta) {
	static DummyPlayerComponent *p = ecs.getComponent<DummyPlayerComponent>(player);

	ecs.updateSystems(mainSystems, delta);

	if (hookSpotLight) {
		spotLight->transform.setTranslation(camera->transform.getTranslation());
		spotLight->transform.setRotation(camera->transform.getRotation());
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
		directionalLight->transform.rotate(vec3::YAXIS, 1.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
		directionalLight->transform.rotate(vec3::YAXIS, -1.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
		directionalLight->transform.rotate(vec3::XAXIS, 1.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
		directionalLight->transform.rotate(vec3::XAXIS, -1.0f);
	}
}

void Test3D::input(Event &event) {
	ecs.inputSystems(mainSystems, event);

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
