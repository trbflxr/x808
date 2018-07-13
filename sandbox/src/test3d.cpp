//
// Created by FLXR on 7/12/2018.
//

#include <gfx/renderer.hpp>
#include <gfx/api/texture2d.hpp>
#include <resources/texturemanager.hpp>
#include <resources/fontmanager.hpp>
#include <resources/soundmanager.hpp>
#include <resources/shaderfactory.hpp>
#include "test3d.hpp"

Test3D::Test3D() :
		ecs(app.getEcs()) {

	renderer = new ForwardRenderer();

	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	TextureParameters params(TextureFilter::NEAREST);

	TextureManager::add(Texture2D::create("rock", "assets/textures/rock.png", params));

	FontManager::add(new Font("consolata", "assets/fonts/consolata.otf", 100));

	SoundManager::add(new Sound("orunec", "assets/sounds/orunec.wav"));



//	rockMesh = new Mesh("assets/models/rock.obj");
	rockMesh = new Mesh("assets/models/monkey3.obj");

}

Test3D::~Test3D() {
	delete rockMesh;
	delete renderer;
}

void Test3D::render() {
	renderer->render(rockMesh);
}

void Test3D::tick() {
	char buff[1024];
	sprintf(buff, "fps: %u | ups: %u | frame time: %f ms | DC: %u",
	        app.getFPS(), app.getUPS(), app.getFrameTime(), Renderer::getDC());

	app.getWindow().setTitle(buff);
}

void Test3D::update(float delta) {

}

void Test3D::onEvent(xe::Event &event) {

}
