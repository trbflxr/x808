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

	ambientLight = new AmbientLight(sf::forwardAmbientShader(), {0.3f, 0.3f, 0.3f});
	renderer = new ForwardRenderer();
	renderer->setAmbientLight(ambientLight);

	camera = new FPSCamera(math::perspective(80.0f, 8.0f / 6.0f, 0.1f, 1000));

//	rockMesh = new Mesh("assets/models/rock.obj");
	rockMesh = new Mesh("assets/models/monkey3.obj");
	material = new Material(&GETTEXTURE("2"), color::WHITE);

	model = new Model(rockMesh, material);
	model->transform.setTranslation({0, 0, -5});
	model->transform.setRotation(math::rotationZ(to_rad(5)));

}

Test3D::~Test3D() {
	delete rockMesh;
	delete renderer;
	delete model;
	delete ambientLight;
}

void Test3D::render() {
	renderer->render(model, camera);
}

void Test3D::tick() {
	char buff[1024];
	sprintf(buff, "fps: %u | ups: %u | frame time: %f ms | DC: %u",
	        app.getFPS(), app.getUPS(), app.getFrameTime(), Renderer::getDC());

	app.getWindow().setTitle(buff);
}

void Test3D::update(float delta) {
	camera->update();


	vec3 a = ambientLight->getAmbientIntensity();
	if (Input::isKeyPressed(XE_KEY_Q)) {
		a += 0.03f;
	}
	if (Input::isKeyPressed(XE_KEY_E)) {
		a -= 0.03f;
	}

	ambientLight->setAmbientIntensity(a);
}

void Test3D::onEvent(xe::Event &event) {

}
