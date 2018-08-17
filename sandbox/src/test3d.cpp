//
// Created by FLXR on 8/4/2018.
//

#include <xe/resources/texturemanager.hpp>
#include <xe/gfx/renderer.hpp>
#include "test3d.hpp"

using namespace xe;

Test3D::Test3D(DebugUI *ui) :
		ui(ui) {

	TextureParameters params;

	TextureManager::add(new Texture("rock", "assets/textures/rock.png", params));
	TextureManager::add(new Texture("bgr", "assets/textures/bgr.jfif", params));

	//init objects
	TransformComponent transform;

	//move player up
	transform.transform.setTranslation({0.0f, 5.0f, -100.0f});

	camera = new Camera(mat4::perspective(80.0f, 8.0f / 6.0f, 0.1f, 1000));
	camera->transform = transform.transform;

	DummyPlayerComponent playerComponent(camera, 6.0f);
	player = ecs.makeEntity(playerComponent, transform);

	playerControlSystem = new DummyPlayerControlSystem();
	mainSystems.addSystem(*playerControlSystem);

	Transform *t = &ecs.getComponent<TransformComponent>(player)->transform;
	ui->trackEntity(L"player", t);

//	renderer = new ForwardRenderer(800, 600, camera, true);
//	rendererSystem = new ForwardRendererSystem(renderer);
//	renderingPipeline.addSystem(*rendererSystem);

//	scene = new Scene("assets/scenes/test", "test");
	scene = new Scene("assets/scenes/sponza", "sponza");

	dummyShader = new Shader(new BaseShader("dummy", {
			ShaderFile::fromFile(ShaderType::Vert, "dummy.vert", { }),
			ShaderFile::fromFile(ShaderType::Frag, "dummy.frag", { })
	}));
}

Test3D::~Test3D() {
	delete scene;
	delete dummyShader;

	delete playerControlSystem;

	delete camera;
}

void Test3D::render() {
	ecs.updateSystems(renderingPipeline, 0.0f);

	Renderer::enableDepthTesting(true);
	Renderer::enableBlend(true);
	Renderer::enableCullFace(true);
	Renderer::setCullFace(CullFace::Back);


	dummyShader->bind();

	static float intensity = 1.0f;
	static vec4 color(1.0f);

	for (auto &&mesh : scene->getMeshes()) {
		const Texture *diffuse = mesh->mesh->getMaterial()->diffuse;

		mat4 mvp = camera->getViewProjection() * mesh->transformation;
		int32 useDiffuse = diffuse ? 1 : 0;

		dummyShader->setUniform("MVP", &mvp.elements, sizeof(mat4));
		dummyShader->setUniform("intensity", &intensity, sizeof(float));
		dummyShader->setUniform("color", &color, sizeof(vec4));
		dummyShader->setUniform("useDiffuse", &useDiffuse, sizeof(int32));

		dummyShader->updateUniforms();

		uint loc = dummyShader->getSampler("diffuse");

		if (diffuse) {
			diffuse->bind(loc);
		}

		mesh->mesh->getVertexArray()->bind();
		mesh->mesh->getIndexBuffer()->bind();

		mesh->mesh->getVertexArray()->drawElements(mesh->mesh->getIndexBuffer()->getCount(), BeginMode::Triangles);

		mesh->mesh->getIndexBuffer()->unbind();
		mesh->mesh->getVertexArray()->unbind();

		if (diffuse) {
			diffuse->unbind(loc);
		}


		Renderer::incDC();
	}

	Renderer::setCullFace(CullFace::Front);
	for (auto &&light : scene->getLights()) {
		Mesh *mesh = light->getMesh()->mesh;

		mat4 mvp = camera->getViewProjection() * light->getMesh()->transformation;
		int32 useDiffuse = 0;

		dummyShader->setUniform("MVP", &mvp.elements, sizeof(mat4));
		dummyShader->setUniform("intensity", &intensity, sizeof(float));
		dummyShader->setUniform("color", &color, sizeof(vec4));
		dummyShader->setUniform("useDiffuse", &useDiffuse, sizeof(int32));

		dummyShader->updateUniforms();


		mesh->getVertexArray()->bind();
		mesh->getIndexBuffer()->bind();

		mesh->getVertexArray()->drawElements(mesh->getIndexBuffer()->getCount(), BeginMode::Triangles);

		mesh->getIndexBuffer()->unbind();
		mesh->getVertexArray()->unbind();

		Renderer::incDC();
	}

	dummyShader->unbind();


	Renderer::enableBlend(false);
	Renderer::enableCullFace(false);
}

void Test3D::update(float delta) {
	ecs.updateSystems(mainSystems, delta);
}

void Test3D::fixedUpdate(float delta) {

}

void Test3D::input(Event &event) {
	ecs.inputSystems(mainSystems, event);
}
