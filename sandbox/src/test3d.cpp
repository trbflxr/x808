//
// Created by FLXR on 3/1/2019.
//

#include "test3d.hpp"
#include <xe/gfx/renderer.hpp>
#include <xe/resources/texturemanager.hpp>
#include <xe/ui/imgui/imgui.h>

using namespace xe;

Test3D::Test3D() {
	const float width = app.getWindowSize().x;
	const float height = app.getWindowSize().y;

	camera = new Camera(mat4::perspective(60.0f, width / height, 0.1f, 1000.0f));
	camera->setPosition({0.0f, 0.0f, 10.0f});

	shader = new Shader("mesh", {
			ShaderFile::fromFile(ShaderType::Vert, "mesh.vert"),
			ShaderFile::fromFile(ShaderType::Frag, "mesh.frag")
	});

	TextureParameters params;
	TextureManager::add(new Texture("diffuse", "bricks.jpg", params));
	TextureManager::add(new Texture("disp", "bricksDisp.png", params));
	TextureManager::add(new Texture("normal", "bricksNormal.jpg", params));

	material = new Material("material");
	material->diffuse = GETTEXTURE("diffuse");
	material->normal = GETTEXTURE("normal");
	material->displacement = GETTEXTURE("disp");

	model = new Model("tm0", "rock.obj");
	model->setMaterial(material);

	player = new DummyPlayer(camera);
}

Test3D::~Test3D() {
	delete player;
	delete camera;

	delete shader;

	delete model;
	delete material;
}

void Test3D::render() {
	shader->bind();
	const uint sampler0 = shader->getSampler("sampler0");
	model->getMaterial()->diffuse->bind(sampler0);

	shader->setUniform("model", model->toMatrix().elements, sizeof(mat4));
	shader->setUniform("view", camera->getView().elements, sizeof(mat4));
	shader->setUniform("projection", camera->getProjection().elements, sizeof(mat4));

	shader->updateUniforms();

	model->render(BeginMode::Triangles);

	model->getMaterial()->diffuse->unbind(sampler0);
	shader->unbind();
}

void Test3D::renderImGui() {
	ImGui::Begin("Test3D");

	ImGui::Text("fps: %i", app.getFPS());
	ImGui::Text("frame time: %.3f", app.getFrameTime());
	ImGui::Text("draw calls: %i", Renderer::getDC());
	ImGui::Separator();
	ImGui::Dummy({10.0f, 0.0f});

	ImGui::End();
}

void Test3D::update(float delta) {
	player->update(delta);

	model->rotate(vec3::UnitY(), 30 * delta);
}

void Test3D::input(Event &event) {
	player->input(event);
}
