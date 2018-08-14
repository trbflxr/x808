//
// Created by FLXR on 8/4/2018.
//

#include <resources/texturemanager.hpp>
#include <gfx/api/texture.hpp>
#include <ecs/components/modelcomponent.hpp>
#include <ecs/components/transformcomponent.hpp>
#include "test3ddeferred.hpp"

#include <resources/shaderfile.hpp>
#include <gfx/renderer.hpp>

using namespace xe;
using namespace xe::api;

Test3DDeferred::Test3DDeferred(DebugUI *ui) :
		ui(ui) {

	TextureParameters params;

	TextureManager::add(Texture::create("rock", "assets/textures/rock.png", params));
	TextureManager::add(Texture::create("bgr", "assets/textures/bgr.jfif", params));

	//init objects
	ModelComponent model;
	TransformComponent transform;

	camera = new Camera(mat4::perspective(80.0f, 8.0f / 6.0f, 0.1f, 1000));

	DummyPlayerComponent playerComponent(camera);
	player = ecs.makeEntity(playerComponent, transform);

	playerControlSystem = new DummyPlayerControlSystem();
	mainSystems.addSystem(*playerControlSystem);

//	renderer = new ForwardRenderer(800, 600, camera, true);
//	rendererSystem = new ForwardRendererSystem(renderer);
//	renderingPipeline.addSystem(*rendererSystem);

	scene = new Scene("assets/scenes/sponza", "sponza");

	XE_INFO(scene->meshes.size());

	dummyShader = new Shader(BaseShader::create("dummy", {
			ShaderFile::fromFile(ShaderType::Vert, "dummy.vert", { }),
			ShaderFile::fromFile(ShaderType::Frag, "dummy.frag", { })
	}));
}

Test3DDeferred::~Test3DDeferred() {
	delete scene;
	delete dummyShader;

	delete playerControlSystem;

	delete camera;
}

void Test3DDeferred::render() {
	ecs.updateSystems(renderingPipeline, 0.0f);

	Renderer::enableDepthTesting(true);
	Renderer::enableBlend(true);

	dummyShader->bind();

	static float intensity = 1.0f;
	static vec4 color(1.0f);

	for (auto &&mesh : scene->meshes) {
		const api::Texture *diffuse = mesh->mesh->getMaterial()->diffuse;

		if (!diffuse) continue;

		mat4 t=mesh->transformation;

		mat4 mvp = camera->getViewProjection() * t;

		dummyShader->setUniform("MVP", &mvp.elements, sizeof(mat4));
		dummyShader->setUniform("intensity", &intensity, sizeof(float));
		dummyShader->setUniform("color", &color, sizeof(vec4));

		dummyShader->updateUniforms();

		uint loc = dummyShader->getResource("diffuse");

		diffuse->bind(loc);

		mesh->mesh->getVertexArray()->bind();
		mesh->mesh->getIndexBuffer()->bind();

		mesh->mesh->getVertexArray()->drawElements(mesh->mesh->getIndexBuffer()->getCount(), BeginMode::Triangles);

		mesh->mesh->getIndexBuffer()->unbind();
		mesh->mesh->getVertexArray()->unbind();

		diffuse->unbind(loc);

		Renderer::incDC();
	}

	dummyShader->unbind();

	Renderer::enableBlend(false);
}

void Test3DDeferred::update(float delta) {
	ecs.updateSystems(mainSystems, delta);
}

void Test3DDeferred::fixedUpdate(float delta) {

}

void Test3DDeferred::input(Event &event) {
	ecs.inputSystems(mainSystems, event);
}

