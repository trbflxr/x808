//
// Created by FLXR on 2/8/2019.
//

#include <xe/ui/imgui/imgui_impl_xe.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/texturemanager.hpp>
#include "testl2d.hpp"

using namespace xe;

TestL2D::TestL2D() {
	const float width = app.getConfig().width;
	const float height = app.getConfig().height;

	TextureParameters params;

	TextureManager::add(new Texture("0", "enemyspotted.png", params));
	TextureManager::add(new Texture("1", "jdm.png", params));
	TextureManager::add(new Texture("2", "test1.png", params));
	TextureManager::add(new Texture("3", "test6.png", params));
	TextureManager::add(new Texture("4", "test8.png", params));
	TextureManager::add(new Texture("star", "star.png", params));

	params.wrap = TextureWrap::Repeat;
	TextureManager::add(new Texture("bg0", "feelsconflictedman.jpg", params));
	TextureManager::add(new Texture("bg1", "sp0.png", params));


	lightShader = new Shader("lightShader", {
			ShaderFile::fromFile(ShaderType::Vert, "light2d.vert"),
			ShaderFile::fromFile(ShaderType::Frag, "light2d.frag")
	});

	camera = new Camera(mat4::ortho(0, width, 0, height, -1, 1000));
//	renderer = new BatchRenderer2D(width, height, camera, lightShader);
	renderer = new BatchRenderer2D(width, height, camera);


	RectangleShape *bg = new RectangleShape({width/2, height/2}, 0.5f);
	bg->setTexture(GETTEXTURE("bg0"));
	bg->transformation({width / 4.0f, height / 4.0f});
	bg->setTextureRect({0.0f, 0.0f, width, height});
	renderables.push_back(bg);

	RectangleShape *jdm = new RectangleShape({100.0f, 100.0f}, 1.0f);
	jdm->setTexture(GETTEXTURE("star"));
	jdm->transformation({800.0f, 350.0f});
	renderables.push_back(jdm);

	box0 = new RectangleShape({100.0f, 100.0f}, 2.0f);
	box0->setTexture(GETTEXTURE("0"));
	box0->transformation({640.0f, 350.0f});
	renderables.push_back(box0);

	box1 = new RectangleShape({100.0f, 100.0f}, 2.0f);
	box1->setTexture(GETTEXTURE("4"));
	box1->transformation({340.0f, 350.0f});
	box1->setColor(color::Yellow);
	renderables.push_back(box1);


	Light2D *l0 = new Light2D("l0", {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 15.0f, 100.0f);
	lights.push_back(l0);

	for (int i = 1; i < 21; ++i) {
		Light2D *l = new Light2D("l" + std::to_string(i), {i * 10.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 10.0f, 50.0f);
		lights.push_back(l);
	}
}

TestL2D::~TestL2D() {
	delete camera;
	delete renderer;

	delete lightShader;

	for (const auto &r : renderables) {
		delete r;
	}
}

void TestL2D::render() {
	//	Renderer::setClearColor(color::rgba(0.0f, 0.0f, 0.012f, 1.0f));
//	Renderer::setClearColor(color::rgba(1, 1, 1, 1.0f));

	vec2 mousePos = Mouse::getPosition(window);
//	vec4 lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	vec2 strengthDistance = vec2(15, 100);
//
//	lightShader->setUniform("lightPosition", &mousePos, sizeof(vec2));
//	lightShader->setUniform("lightColor", &lightColor, sizeof(vec4));
//	lightShader->setUniform("strengthDistance", &strengthDistance, sizeof(vec2));

	lights[0]->setPosition(mousePos);

	for (const auto &r : renderables) {
		renderer->submit(r);
	}

//	for (const auto &l : lights) {
//		renderer->submit(l);
//	}

	renderer->renderSprites();
//	renderer->renderText();

	renderer->clear();
}

void TestL2D::renderImGui() {
	ImGui::Begin("Lights", nullptr);

	ImGui::Image(reinterpret_cast<void *>(renderer->diffuse->getHandle()), {640, 360}, {0, 1}, {1, 0});

	ImGui::End();
}

void TestL2D::update(float delta) {
	///update camera
	vec3 camPos = camera->transform.getPosition();

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
	camera->transform.setPosition(camPos);

	camera->update();
}

void TestL2D::input(xe::Event &event) { }
