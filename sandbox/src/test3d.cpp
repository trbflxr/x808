//
// Created by FLXR on 7/12/2018.
//

#include <gfx/renderer.hpp>
#include <gfx/api/texture2d.hpp>
#include <resources/texturemanager.hpp>
#include <resources/fontmanager.hpp>
#include <resources/soundmanager.hpp>
#include <resources/shaderfactory.hpp>
#include <gfx/color.hpp>
#include "test3d.hpp"

Test3D::Test3D() :
		ecs(app.getEcs()) {

	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	TextureParameters params(TextureFilter::NEAREST);
	TextureManager::add(Texture2D::create("rock", "assets/textures/rock.png", params));
	TextureManager::add(Texture2D::create("2", "assets/textures/test3.png", params));

	FontManager::add(new Font("consolata", "assets/fonts/consolata.otf", 100));
	SoundManager::add(new Sound("orunec", "assets/sounds/orunec.wav"));

	renderer = new ForwardRenderer();

	ambientLight = new AmbientLight(sf::forwardAmbientShader(), 0.1f, color::WHITE);
	renderer->setAmbientLight(ambientLight);

	directionalLight = new DirectionalLight(sf::forwardDirectionalShader(), {-0.5f, -0.5f, 0.5f}, 0.5f,
	                                        color::WHITE);
	renderer->addLight(directionalLight);

	pointLight = new PointLight(sf::forwardPointShader(), {3, 1, -5}, {0, 0, 1}, 0.5f, color::RED);
	renderer->addLight(pointLight);

	pointLight2 = new PointLight(sf::forwardPointShader(), {1, 1, -2}, {0, 0, 1}, 0.5f, color::BLUE);
	renderer->addLight(pointLight2);


	player = new DummyPlayer(new FPSCamera(mat4::perspective(80.0f, 8.0f / 6.0f, 0.1f, 1000)));

	monkeyMaterial = new Material(&GETTEXTURE("2"), color::WHITE, 50, 2.2f);
	monkeyMaterial2 = new Material(&GETTEXTURE("2"), color::WHITE, 1, 0.9f);
	rockMaterial = new Material(&GETTEXTURE("rock"), color::WHITE, 2, 0.2f);

	rockMesh = new Mesh("assets/models/rock.obj");
	monkeyMesh = new Mesh("assets/models/monkey3.obj");

	monkeyModel = new Model(monkeyMesh, monkeyMaterial);
	monkeyModel->transform.setTranslation({5, 0, -5});
	monkeyModel->transform.setRotation(quat::rotationZ(to_rad(30)));

	monkeyModel2 = new Model(monkeyMesh, monkeyMaterial2);
	monkeyModel2->transform.setTranslation({3, 0, -8});

	rockModel = new Model(rockMesh, rockMaterial);
	rockModel->transform.setTranslation({0, 0, -5});
	rockModel->transform.setRotation(quat::rotationZ(to_rad(5)));

}

Test3D::~Test3D() {
	delete renderer;
	delete ambientLight;
	delete directionalLight;
	delete pointLight;
	delete pointLight2;

	delete rockMesh;
	delete monkeyMesh;

	delete monkeyModel;
	delete monkeyModel2;
	delete rockModel;

	delete rockMaterial;
	delete monkeyMaterial;
	delete monkeyMaterial2;

	delete player;
}

void Test3D::render() {
	renderer->render(monkeyModel, player->getCamera());
	renderer->render(monkeyModel2, player->getCamera());
	renderer->render(rockModel, player->getCamera());
}

void Test3D::tick() {
	char buff[1024];
	sprintf(buff, "fps: %u | ups: %u | frame time: %f ms | DC: %u",
	        app.getFPS(), app.getUPS(), app.getFrameTime(), Renderer::getDC());

	app.getWindow().setTitle(buff);
}

void Test3D::update(float delta) {
	player->update(delta);
}

void Test3D::fixedUpdate(float delta) {
	if (Keyboard::isKeyPressed(Keyboard::Key::Q)) {
		float a = ambientLight->getIntensity();
		a += 0.03f;
		ambientLight->setIntensity(a);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
		float a = ambientLight->getIntensity();
		a -= 0.03f;
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
	}
}
