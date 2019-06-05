//
// Created by FLXR on 6/4/2019.
//

#include "examplesound.hpp"
#include <xe/resources/texturemanager.hpp>
#include <xe/ui/imgui/imgui.h>
#include <xe/gfx/renderer.hpp>
#include <xe/audio/audiomaster.hpp>
#include <xe/resources/soundmanager.hpp>

using namespace xe;

ExampleSound *ExampleSound::instance = nullptr;

ExampleSound::ExampleSound() {

	const float width = app.getWindowSize().x;
	const float height = app.getWindowSize().y;

	camera = new Camera(mat4::perspective(60.0f, width / height, 0.1f, 1000.0f));
	camera->setPosition({4.0f, 3.0f, 20.0f});

	player = new DummyPlayer(camera);

	ShadowParameters sp(app.getConfig(), 512, 1024);

	renderer = new DeferredRenderer(width, height, camera, sp, fx::AOType::None);
	renderer->setAmbientLight({0.10f, 0.14f, 0.25f});
	renderer->enableLightObjects(true);

	exampleScene = &ExampleScene::get();

	scene = new Scene();

	Model *m = new Model("source0", IndexedModel::getIcosphereModel());
	m->setMaterial(exampleScene->mat_cloth);
	scene->add(m);

	as0 = new AudioSource("as0", GETSOUND("orunec"));
	as0->setPosition({0.0f, 0.0f, 0.0f});
	as0->setGain(200);
	as0->setRolloffFactor(1.0f);
	as0->setPitch(1.2f);
	as0->setMaxDistance(100);

	AudioMaster::setDistanceModel(DistanceModel::Exponent);
}

ExampleSound::~ExampleSound() {
	delete player;
	delete camera;
	delete renderer;

	delete scene;

	delete as0;
}

void ExampleSound::init() {

}

void ExampleSound::render() {
	renderer->render(scene);
}

void ExampleSound::renderImGui() {
	const vec3 &cp = camera->getPosition();
	const vec3 &cl = camera->getRotation().getForward();

	ImGui::Begin("Example sound", nullptr);

	ImGui::Text("camera: (%.1f, %.1f, %.1f)", cp.x, cp.y, cp.z);
	ImGui::Text("look: (%.1f, %.1f, %.1f)", cl.x, cl.y, cl.z);

	if (ImGui::Button("Orunec")) {
		as0->play();
	}

	ImGui::End();
}

void ExampleSound::update(float delta) {
	player->update(delta);

	scene->updateLights(camera);

	as0->setPosition(-camera->getPosition());
}

void ExampleSound::fixedUpdate(float delta) {
	player->update(delta);
}

void ExampleSound::input(xe::Event &event) {
	player->input(event);

	if (event.type == Event::KeyPressed) {
		if (event.key.code == Keyboard::F) {
			as0->play();
		}
	}
}
