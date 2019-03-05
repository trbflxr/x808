//
// Created by FLXR on 2/8/2019.
//

#include <xe/ui/imgui/imgui_impl_xe.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/texturemanager.hpp>
#include <xe/resources/soundmanager.hpp>
#include <xe/audio/audiomaster.hpp>
#include <xe/utils/random.hpp>
#include "testl2d.hpp"

using namespace xe;

TestL2D::TestL2D() {
	const float width = app.getWindowSize().x;
	const float height = app.getWindowSize().y;

	TextureParameters params;

	TextureManager::add(new Texture("0", "enemyspotted.png", params));
	TextureManager::add(new Texture("jdm", "jdm.png", params));
	TextureManager::add(new Texture("2", "test1.png", params));
	TextureManager::add(new Texture("3", "test6.png", params));
	TextureManager::add(new Texture("cosm", "cosmic.png", params));
	TextureManager::add(new Texture("star", "star.png", params));
	TextureManager::add(new Texture("anim0", "anim0.png", params));

	params.wrap = TextureWrap::Repeat;
	TextureManager::add(new Texture("bg0", "feelsconflictedman.jpg", params));
	TextureManager::add(new Texture("bg1", "sp0.png", params));

	SoundManager::add(new Sound("test", "test.wav"));
	SoundManager::add(new Sound("orunec", "orunec.wav"));


	camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1000.0f));
	renderer = new Renderer2D(width, height, camera, 50);

	RectangleShape *bg = new RectangleShape({width * 4, height * 4});
	bg->setTexture(GETTEXTURE("bg0"));
	bg->transformation({width * 4 / 2.0f, height * 4 / 2.0f});
	bg->setTextureRect({0.0f, 0.0f, width * 8, height * 8});
	renderables.push_back(bg);

	RectangleShape *jdm = new RectangleShape({100.0f, 100.0f});
	jdm->setTexture(GETTEXTURE("star"));
	jdm->transformation({800.0f, 350.0f});
	renderables.push_back(jdm);

	box0 = new RectangleShape({100.0f, 100.0f});
	box0->setTexture(GETTEXTURE("jdm"));
	box0->transformation({640.0f, 350.0f});
	renderables.push_back(box0);

	box1 = new RectangleShape({100.0f, 100.0f});
	box1->setTexture(GETTEXTURE("cosm"));
	box1->transformation({340.0f, 350.0f});
	box1->setColor(color::Yellow);
	renderables.push_back(box1);

	///animation test
	playerAnimation = new SpriteAnimation(GETTEXTURE("anim0"), {4, 8}, 1.0f);

	player = new RectangleShape({150.0f, 150.0f});
	player->setTexture(GETTEXTURE("anim0"));
	player->setTextureRect(playerAnimation->getTextureRect());
	renderables.push_back(player);


	Light2D *l0 = new Light2D("l0", {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 150.0f);
	lights.push_back(l0);

	for (int i = 1; i < 50; ++i) {
		const float x = random::next<float>(50, 4000);
		const float y = random::next<float>(50, 2000);

		const float r = random::next<float>(0, 1);
		const float g = random::next<float>(0, 1);
		const float b = random::next<float>(0, 1);

		const float s = random::next<float>(50, 200);

		Light2D *l = new Light2D("l" + std::to_string(i), {x, y}, {r, g, b}, s);
		lights.push_back(l);
	}

	as0 = new AudioSource("as0", GETSOUND("test"));
	as0->setGain(10.0f);
	as0->setReferenceDistance(10.0f);
	as0->setRolloffFactor(10.0f);
//	as0->setMaxDistance(1.0f);

}

TestL2D::~TestL2D() {
	delete camera;
	delete renderer;

	for (const auto &r : renderables) {
		delete r;
	}

	for (const auto &l : lights) {
		delete l;
	}

	delete playerAnimation;

	delete as0;
}

void TestL2D::render() {
	vec2 pos = Mouse::getPosition(window) + vec2(camera->getPosition());
	lights[0]->setPosition(pos);

	for (const auto &l : lights) {
		renderer->useLight(l);
	}

	renderer->begin();

	for (auto &&r : renderables) {
		renderer->submit(r);
	}

	renderer->end();
	renderer->flush();
}

void TestL2D::renderImGui() {
	ImGui::Begin("Audio test");

	ImGui::Text("fps: %i", app.getFPS());
	ImGui::Text("frame time: %.3f", app.getFrameTime());
	ImGui::Text("draw calls: %i", Renderer::getDC());
	ImGui::Separator();
	ImGui::Dummy({10.0f, 0.0f});

	if (ImGui::Button("test")) {
		as0->play();
	}

	if (ImGui::Button("test loop")) {
		static bool l = true;
		as0->setLooping(l);
		l = !l;
		XE_TRACE(as0->isLooped());
	}

	if (ImGui::Button("test stop")) {
		as0->stop();
	}

	if (ImGui::Button("test play/pause")) {
		if (as0->isPlaying()) {
			as0->pause();
		} else {
			as0->play();
		}
	}

	if (ImGui::Button("test offset")) {
		as0->setOffset(0.1f);
	}

	static uint model = 0;
	if (ImGui::Button("distance model")) {
		if (model == 0) {
			AudioMaster::setDistanceModel(DistanceModel::Inverse);
		} else if (model == 1) {
			AudioMaster::setDistanceModel(DistanceModel::InverseClamped);
		} else if (model == 2) {
			AudioMaster::setDistanceModel(DistanceModel::Linear);
		} else if (model == 3) {
			AudioMaster::setDistanceModel(DistanceModel::LinearClamped);
		} else if (model == 4) {
			AudioMaster::setDistanceModel(DistanceModel::Exponent);
		} else if (model == 5) {
			AudioMaster::setDistanceModel(DistanceModel::ExponentClamped);
		}

		++model;
		if (model == 5) model = 0;
	}

	static float refDistance = 0.0f;
	if (ImGui::DragFloat("ref distance", &refDistance, 0.1f)) {
		if (refDistance < 0.0f) refDistance = 0.0f;
		as0->setReferenceDistance(refDistance);
	}

	static float rolloff = 0.0f;
	if (ImGui::DragFloat("rolloff", &rolloff, 0.1f)) {
		if (rolloff < 0.0f) rolloff = 0.0f;
		as0->setRolloffFactor(rolloff);
	}

	static float maxDistance = 0.0f;
	if (ImGui::DragFloat("max distance", &maxDistance, 0.1f)) {
		if (maxDistance < 0.0f) maxDistance = 0.0f;
		as0->setMaxDistance(maxDistance);
	}

	static float v[3];
	if (ImGui::DragFloat3("velocity", v, 0.1f)) {
		as0->setVelocity({v[0], v[1], v[2]});
	}

	static int32 maxLights = renderer->getMaxLights();
	if (ImGui::DragInt("max lights", &maxLights, 0.1f, 1, 50)) {
		renderer->setMaxLights(maxLights);
	}

	ImGui::End();
}

void TestL2D::update(float delta) {
	const vec2 pos = vec2(Mouse::getPosition(window) + vec2(camera->getPosition()));
	player->setPosition(pos);

	playerAnimation->update(delta, 0, true);
	player->setTextureRect(playerAnimation->getTextureRect());

	static vec2 halfScreen = app.getWindowSize() / 2.0f;
	as0->setPosition(vec3((halfScreen - pos) * -1, 150.0f));

	///update camera
	vec3 camPos = camera->getPosition();

	if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::D)) {
		camPos.x += 1000 * delta;
	}
	if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::A)) {
		camPos.x -= 1000 * delta;
	}
	if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::W)) {
		camPos.y += 1000 * delta;
	}
	if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::S)) {
		camPos.y -= 1000 * delta;
	}
	camera->setPosition(camPos);

	camera->update();
}

void TestL2D::input(xe::Event &event) { }


void TestL2D::resize(int32 width, int32 height) {
	camera->setProjection(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1000.0f));
	renderer->setWidth(width);
	renderer->setHeight(height);
}
