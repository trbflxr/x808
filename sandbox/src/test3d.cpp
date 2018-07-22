//
// Created by FLXR on 7/12/2018.
//

#include <gfx/renderer.hpp>
#include <gfx/api/texture2d.hpp>
#include <resources/texturemanager.hpp>
#include <resources/fontmanager.hpp>
#include <resources/soundmanager.hpp>
#include <resources/shadermanager.hpp>
#include <gfx/color.hpp>
#include "test3d.hpp"

Test3D::Test3D() :
		ecs(app.getEcs()) {

	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	TextureParameters params(TextureFilter::NEAREST);
	TextureManager::add(Texture2D::create("rock", "assets/textures/rock.png", params));
	TextureManager::add(Texture2D::create("2", "assets/textures/test3.png", params));
	TextureManager::add(Texture2D::create("4", "assets/textures/test5.png", params));
	TextureManager::add(Texture2D::create("grass", "assets/textures/grass.png", params));
	TextureManager::add(Texture2D::create("stall", "assets/textures/stall.png", params));
	TextureManager::add(Texture2D::create("bricks", "assets/textures/bricks.jpg", params));
	TextureManager::add(Texture2D::create("bricks2", "assets/textures/bricks2.jpg", params));
	TextureManager::add(Texture2D::create("bricksNormal2", "assets/textures/bricksNormal2.png", params));
	TextureManager::add(Texture2D::create("defaultNormal", "assets/textures/defaultNormal.jpg", params));

	FontManager::add(new Font("consolata", "assets/fonts/consolata.otf", 100));
	SoundManager::add(new Sound("orunec", "assets/sounds/orunec.wav"));

	renderer = new ForwardRenderer();

	ambientLight = new AmbientLight(GETSHADER("forwardAmbient"), 0.05f, color::WHITE);
	renderer->setAmbientLight(ambientLight);

	directionalLight = new DirectionalLight(GETSHADER("forwardDirectional"),
	                                        {-0.665f, -0.745f, -0.053f}, 0.4f, color::WHITE);
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
	spotLight = new SpotLight(GETSHADER("forwardSpot"), {2.789f, 0.350f, -5.662f}, {0.107f, -0.132f, -0.986f},
	                          0.95f, {0.1f, 0.1f, 0.02f}, 0.3f, color::WHITE);

	renderer->addLight(spotLight);


	//todo: shader include
	player = new DummyPlayer(new FPSCamera(mat4::perspective(80.0f, 8.0f / 6.0f, 0.1f, 1000)));

	monkeyMaterial = new Material(GETTEXTURE("2"), color::WHITE, 50, 2.2f);
	monkeyMaterial2 = new Material(GETTEXTURE("4"), color::WHITE, 1, 0.2f);
	rockMaterial = new Material(GETTEXTURE("rock"), color::WHITE, 2, 0.2f);
	stallMaterial = new Material(GETTEXTURE("stall"), color::WHITE, 2, 0.2f);
	planeMaterial = new Material(GETTEXTURE("bricks"), color::WHITE, 2, 0.2f);

	rockMesh = new Mesh("assets/models/rock.obj");
	monkeyMesh = new Mesh("assets/models/monkey3.obj");
	stallMesh = new Mesh("assets/models/stall.obj");
	planeMesh0 = new Mesh("assets/models/plane0.obj");
	planeMesh1 = new Mesh("assets/models/plane1.obj");
	planeMesh2 = new Mesh("assets/models/plane2.obj");

	monkeyModel = new Model(monkeyMesh, monkeyMaterial);
	monkeyModel->transform.setTranslation({5, 0, -5});
	monkeyModel->transform.setRotation(quat::rotationZ(to_rad(30)));

	monkeyModel2 = new Model(monkeyMesh, monkeyMaterial2);
	monkeyModel2->transform.setTranslation({3, 0, -8});

	rockModel = new Model(rockMesh, rockMaterial);
	rockModel->transform.setTranslation({0, 0, -5});
	rockModel->transform.setRotation(quat::rotationZ(to_rad(5)));

	stallModel = new Model(stallMesh, stallMaterial);
	stallModel->transform.setTranslation({0, 0, -15});
	stallModel->transform.setRotation(quat::rotationY(to_rad(-90)));

//	planes
	planeModel0 = new Model(planeMesh0, planeMaterial);
	planeModel0->transform.setTranslation({15, 0, -5});
	planeModel0->transform.setRotation(quat::rotationY(to_rad(-10)));

	planeModel1 = new Model(planeMesh1, planeMaterial);
	planeModel1->transform.setTranslation({15, -3, -5});
	planeModel1->transform.setRotation(quat::rotationY(to_rad(40)));

	planeModel2 = new Model(planeMesh2, planeMaterial);
	planeModel2->transform.setTranslation({15, -5, -5});

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
	delete planeMesh2;

	delete monkeyModel;
	delete monkeyModel2;
	delete rockModel;
	delete stallModel;

	delete planeModel0;
	delete planeModel1;
	delete planeModel2;

	delete rockMaterial;
	delete monkeyMaterial;
	delete monkeyMaterial2;
	delete stallMaterial;
	delete planeMaterial;

	delete player;
}

void Test3D::render() {
	renderer->render(monkeyModel, player->getCamera());
	renderer->render(monkeyModel2, player->getCamera());
	renderer->render(rockModel, player->getCamera());
	renderer->render(stallModel, player->getCamera());

	renderer->render(planeModel0, player->getCamera());
	renderer->render(planeModel1, player->getCamera());
	renderer->render(planeModel2, player->getCamera());
}

void Test3D::tick() {
	XE_INFO(player->getCamera()->getForwardDirection(player->getCamera()->getOrientation()));

	char buff[1024];
	sprintf(buff, "fps: %u | ups: %u | frame time: %f ms | DC: %u",
	        app.getFPS(), app.getUPS(), app.getFrameTime(), Renderer::getDC());

	app.getWindow().setTitle(buff);
}

void Test3D::update(float delta) {
	player->update(delta);

	if (hookSpotLight) {
		spotLight->setPosition(player->getCamera()->getPosition());
		spotLight->setDirection(player->getCamera()->getForwardDirection(player->getCamera()->getOrientation()));
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
