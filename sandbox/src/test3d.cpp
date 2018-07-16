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
	
	ambientLight = new AmbientLight(sf::forwardAmbientShader(), 0.3f, color::WHITE);
	renderer->setAmbientLight(ambientLight);

	directionalLight = new DirectionalLight(sf::forwardDirectionalShader(), {1, 0, 0}, 0.5f, color::WHITE);
	renderer->addLight(directionalLight);


	player = new DummyPlayer(new FPSCamera(mat4::perspective(80.0f, 8.0f / 6.0f, 0.1f, 1000)));

	monkeyMaterial = new Material(&GETTEXTURE("2"), color::WHITE, 1, 1);
	rockMaterial = new Material(&GETTEXTURE("rock"), color::WHITE, 2, 2);

	rockMesh = new Mesh("assets/models/rock.obj");
	monkeyMesh = new Mesh("assets/models/monkey3.obj");

	monkeyModel = new Model(monkeyMesh, monkeyMaterial);
	monkeyModel->transform.setTranslation({5, 0, -5});
	monkeyModel->transform.setRotation(quat::rotationZ(to_rad(30)));

	rockModel = new Model(rockMesh, rockMaterial);
	rockModel->transform.setTranslation({0, 0, -5});
	rockModel->transform.setRotation(quat::rotationZ(to_rad(5)));

}

Test3D::~Test3D() {
	delete renderer;
	delete ambientLight;
	delete directionalLight;

	delete rockMesh;
	delete monkeyMesh;

	delete monkeyModel;
	delete rockModel;

	delete rockMaterial;
	delete monkeyMaterial;

	delete player;
}

void Test3D::render() {
	renderer->render(monkeyModel, player->getCamera());
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
	if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::Q)) {
		float a = ambientLight->getIntensity();
		a += 0.03f;
		ambientLight->setIntensity(a);
	}
	if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::E)) {
		float a = ambientLight->getIntensity();
		a -= 0.03f;
		ambientLight->setIntensity(a);
	}

	if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::R)) {
		vec3 a = directionalLight->getDirection();
		a.y += 0.03f;
		directionalLight->setDirection(a);
	}
	if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::T)) {
		vec3 a = directionalLight->getDirection();
		a.y -= 0.03f;
		directionalLight->setDirection(a);
	}
}

void Test3D::input(xe::Event &event) {
	player->input(event);
}
