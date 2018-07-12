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
#include "../../engine/external/glew/include/GL/glew.h"

Test3D::Test3D() :
		ecs(app.getEcs()) {

//	glFrontFace(GL_CW);
	glCullFace(GL_BACK);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);


	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	TextureParameters params(TextureFilter::NEAREST);

	TextureManager::add(Texture2D::create("rock", "assets/textures/rock.png", params));

	FontManager::add(new Font("consolata", "assets/fonts/consolata.otf", 100));

	SoundManager::add(new Sound("orunec", "assets/sounds/orunec.wav"));


	shader = sf::forwardAmbientShader();



//	rockMesh = new Mesh("assets/models/rock.obj");
	rockMesh = new Mesh("assets/models/monkey3.obj");

}

Test3D::~Test3D() {
	delete rockMesh;
}

void Test3D::render() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);


	shader->bind();

	//temp
	mat4 projection = math::translate({0, 0, 10});
	mat4 view(1.0f);
	vec3 ambientIntensity(0.3f, 0.3f, 0.3f);

	shader->setUniform("sys_ProjectionMatrix", (byte *) &projection.elements);
	shader->setUniform("sys_ViewMatrix", (byte *) &view.elements);
	shader->setUniform("u_AmbientIntensity", (byte *) &ambientIntensity);

	static const Texture *tex = &GETTEXTURE("rock");

	tex->bind(0);

	rockMesh->render();

	tex->unbind(0);


	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
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
