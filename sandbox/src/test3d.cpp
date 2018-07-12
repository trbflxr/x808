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

	glEnable(GL_TEXTURE_2D);


	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	TextureParameters params(TextureFilter::NEAREST);

	TextureManager::add(Texture2D::create("rock", "assets/textures/rock.png", params));

	FontManager::add(new Font("consolata", "assets/fonts/consolata.otf", 100));

	SoundManager::add(new Sound("orunec", "assets/sounds/orunec.wav"));


	shader = sf::basicForwardShader();
	const api::ShaderUniformBufferVec &vssu = shader->getVSSystemUniforms();

	XE_ASSERT(vssu.size());
	const uint requiredSystemUniformsCount = 2;
	const std::string requiredSystemUniforms[requiredSystemUniformsCount] = {
			"sys_ProjectionMatrix",
			"sys_ViewMatrix"};

	systemUniforms.resize(requiredSystemUniformsCount);
	for (auto &&ub : vssu) {
		UniformBuffer buffer(new byte[ub->getSize()], ub->getSize());
		systemUniformBuffers.push_back(buffer);

		for (auto &&uniform: ub->getUniforms()) {
			for (uint j = 0; j < requiredSystemUniformsCount; j++) {
				if (uniform->getName() == requiredSystemUniforms[j]) {
					systemUniforms[j] = R2DSysUniform(buffer, uniform->getOffset());
				}
			}
		}
	}

	mat4 projection = math::translate({0, 0, 10});
	static mat4 view(1.0f);

	memcpy(systemUniforms[0].buffer.buffer + systemUniforms[0].offset, &projection.elements, sizeof(mat4));
	memcpy(systemUniforms[1].buffer.buffer + systemUniforms[1].offset, &view.elements, sizeof(mat4));



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
	for (uint i = 0; i < systemUniformBuffers.size(); i++) {
		shader->setVSSystemUniformBuffer(systemUniformBuffers[i].buffer, systemUniformBuffers[i].size, i);
	}


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
