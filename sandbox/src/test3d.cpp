//
// Created by FLXR on 3/1/2019.
//

#include "test3d.hpp"
#include <xe/gfx/renderer.hpp>
#include <xe/ui/imgui/imgui.h>

using namespace xe;

Test3D::Test3D() {
	const float width = app.getWindowSize().x;
	const float height = app.getWindowSize().y;

	camera = new Camera(mat4::perspective(60.0f, width / height, 0.1f, 1000.0f));
	camera->setPosition({0.0f, 0.0f, 10.0f});

	player = new DummyPlayer(camera);

	model = new Model(Mesh::spotLightMesh("sl0"));

	TextureParameters params;
	texture = new Texture("test1", "test1.png", params);

	shader = new Shader("mesh", {
			ShaderFile::fromFile(ShaderType::Vert, "mesh.vert"),
			ShaderFile::fromFile(ShaderType::Frag, "mesh.frag")
	});
}

Test3D::~Test3D() {
	delete player;
	delete camera;


	delete shader;
	delete model;
	delete texture;
}

void Test3D::render() {
	shader->bind();
	const uint sampler0 = shader->getSampler("sampler0");
	texture->bind(sampler0);

	shader->setUniform("model", model->toMatrix().elements, sizeof(mat4));
	shader->setUniform("view", camera->getView().elements, sizeof(mat4));
	shader->setUniform("projection", camera->getProjection().elements, sizeof(mat4));

	shader->updateUniforms();

	model->render(BeginMode::LineStrip);

	texture->unbind(sampler0);
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
