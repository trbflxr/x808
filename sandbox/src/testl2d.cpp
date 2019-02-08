//
// Created by FLXR on 2/8/2019.
//

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
	TextureManager::add(new Texture("2", "star.png", params));
	TextureManager::add(new Texture("3", "test1.png", params));
	TextureManager::add(new Texture("4", "test6.png", params));
	TextureManager::add(new Texture("5", "test8.png", params));

	params.wrap = TextureWrap::Repeat;
	TextureManager::add(new Texture("bg", "sp0.png", params));


	lightShader = new Shader("lightShader", {
			ShaderFile::fromFile(ShaderType::Vert, "light2d.vert"),
			ShaderFile::fromFile(ShaderType::Frag, "light2d.frag")
	});

	camera = new Camera(mat4::ortho(0, width, 0, height, -1, 1000));
	renderer = new BatchRenderer2D(width, height, camera, lightShader);

	box0 = new RectangleShape({100.0f, 100.0f}, 1.0f);
	box0->setTexture(GETTEXTURE("0"));
	box0->transformation({640.0f, 350.0f});
	renderables.push_back(box0);

	box1 = new RectangleShape({100.0f, 100.0f}, 1.0f);
	box1->setTexture(GETTEXTURE("5"));
	box1->transformation({340.0f, 350.0f});
	renderables.push_back(box1);

	Renderer::setClearColor(color::rgba(0.0f, 0.0f, 0.012f, 1.0f));
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
	for (const auto &r : renderables) {
		renderer->submit(r);
	}

	renderer->renderSprites();
	renderer->renderText();

	renderer->clear();
}

void TestL2D::renderImGui() { }

void TestL2D::update(float delta) { }

void TestL2D::input(xe::Event &event) { }
