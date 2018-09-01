//
// Created by FLXR on 8/4/2018.
//

#include <xe/resources/texturemanager.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/shadermanager.hpp>
#include <xe/gfx/fx/gbuffer.hpp>
#include "test3d.hpp"

using namespace xe;

Test3D::Test3D(DebugUI *ui) :
		ui(ui) {

	const float width = app.getConfig().width;
	const float height = app.getConfig().height;

	TextureParameters params;

	TextureManager::add(new Texture("rock", "assets/textures/rock.png", params));
	TextureManager::add(new Texture("bgr", "assets/textures/bgr.jfif", params));

	//init objects
	TransformComponent *tc = new TransformComponent();

	//move player
	tc->transform.setPosition({0.0f, 8.0f, -95.0f});

	camera = new Camera(mat4::perspective(75.0f, width / height, 0.1f, 1000.0f));
	camera->transform = tc->transform;

	playerEntity = ecs.makeEntity(new DummyPlayerComponent(camera, 6.0f), tc);

	playerControlSystem = new DummyPlayerControlSystem();
	mainSystems.addSystem(*playerControlSystem);

	Transform *t = &ecs.getComponent<TransformComponent>(playerEntity)->transform;
	ui->trackEntity(L"player", t);

	BufferLayout cl;
	cl.push<mat4>("view");
	cl.push<mat4>("perspective");
	cl.push<vec3>("camPosition");
	cl.push<vec3>("camLook");

	cameraUBO = new UniformBuffer(BufferStorage::Dynamic, 1, cl);

//	scene = new Scene("assets/scenes/test", "test");
	scene = new Scene("assets/scenes/sponza", "sponza");

	quad = new fx::Quad(width, height);
	final = new fx::Final(width, height, false);
	gBuffer = new fx::GBuffer(width, height);

	ui->sp0->texture = gBuffer->getDiffuseTexture();
	ui->sp1->texture = gBuffer->getNormalDepthTexture();
	ui->sp2->texture = gBuffer->getSpecularTexture();
	ui->sp3->texture = gBuffer->getDepthStencilTexture();

	gBuffer->enableLightObjects(true);
}

Test3D::~Test3D() {
	delete scene;

	delete playerControlSystem;

	delete camera;


	delete quad;
	delete final;
	delete gBuffer;
}

void Test3D::render() {
	ecs.updateSystems(renderingPipeline, 0.0f);

	//test draw
	scene->update(camera->transform, 0.0f);

	const vec3 look = camera->transform.getRotation().getForward();
	const vec3 pos = -camera->transform.getPosition();
	const mat4 view = camera->getViewMatrix();
	const mat4 persp = camera->getProjection();

	updateUBO(view, persp, pos, look);

	//render
	Renderer::enableDepthMask(true);
	Renderer::enableDepthTesting(true);
	Renderer::enableCullFace(true);
	Renderer::setCullFace(CullFace::Back);

	gBuffer->passDeferredShading(scene);

	Renderer::enableDepthTesting(true);
	gBuffer->passLightAccumulation(quad, final->getFinalFBO());

	Renderer::enableCullFace(false);
	final->render(quad);
}

void Test3D::updateUBO(const mat4 &view, const mat4 &perspective, const vec3 &pos, const vec3 &look) {
	cameraUBO->update(&view, 0);
	cameraUBO->update(&perspective, 1);
	cameraUBO->update(&pos, 2);
	cameraUBO->update(&look, 3);
}


void Test3D::update(float delta) {
	ecs.updateSystems(mainSystems, delta);

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		scene->getLights()[0]->transform.rotate(scene->getLights()[0]->transform.getRotation().getUp(), 50.0f * delta);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		scene->getLights()[0]->transform.rotate(scene->getLights()[0]->transform.getRotation().getUp(), -50.0f * delta);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		scene->getLights()[0]->transform.rotate(scene->getLights()[0]->transform.getRotation().getLeft(),
		                                        50.0f * delta);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		scene->getLights()[0]->transform.rotate(scene->getLights()[0]->transform.getRotation().getLeft(),
		                                        -50.0f * delta);
	}

	if (light) {
		scene->getLights()[0]->transform.setRotation(camera->transform.getRotation());
	}


	//point
	if (Keyboard::isKeyPressed(Keyboard::X)) {
		scene->getLights()[0]->transform.move({10 * delta, 0, 0});
	}
	if (Keyboard::isKeyPressed(Keyboard::C)) {
		scene->getLights()[0]->transform.move({-10 * delta, 0, 0});
	}
}

void Test3D::input(Event &event) {
	ecs.inputSystems(mainSystems, event);

	if (event.type == Event::KeyPressed) {
		if (event.key.code == Keyboard::F1) {
			static bool enabled = false;
			enabled = !enabled;
			gBuffer->enableWireframe(enabled);
		}
		if (event.key.code == Keyboard::F2) {
			static bool enabled = false;
			enabled = !enabled;
			final->useFXAA(enabled);
		}
		if (event.key.code == Keyboard::F3) {
			static bool enabled = true;
			enabled = !enabled;
			gBuffer->enableLightObjects(enabled);
		}
		if (event.key.code == Keyboard::F4) {
			static bool enabled = false;
			enabled = !enabled;
			gBuffer->enableLightBounds(enabled);
		}
		if (event.key.code == Keyboard::T) {
			Transform *cam = &ecs.getComponent<TransformComponent>(playerEntity)->transform;
			static bool t = false;
			t = !t;
			if (t) {
				cam->setPosition({0, 0, 0});
			} else {
				cam->setPosition({0.0f, 8.0f, -95.0f});
			}
		}
		if (event.key.code == Keyboard::F) {
			light = !light;
		}
	}
}
