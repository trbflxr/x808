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

	camera = new Camera(mat4::perspective(80.0f, width / height, 0.1f, 1000.0f));
	camera->transform.setPosition({0.0f, 0.0f, 10.0f});

	mesh = Mesh::pointLightMesh("pl0");

	TextureParameters params;
	texture = new Texture("rock", "rock.png", params);

	shader = new Shader("mesh", {
			ShaderFile::fromFile(ShaderType::Vert, "mesh.vert"),
			ShaderFile::fromFile(ShaderType::Frag, "mesh.frag")
	});
}

Test3D::~Test3D() {
	delete camera;


	delete shader;
	delete mesh;
	delete texture;
}

void Test3D::render() {
	shader->bind();
	const uint sampler0 = shader->getSampler("sampler0");
	texture->bind(sampler0);

	shader->setUniform("projection", camera->getProjection().elements, sizeof(mat4));
	shader->setUniform("view", camera->getView().elements, sizeof(mat4));

	shader->updateUniforms();

	mesh->render(BeginMode::Triangles);

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

}

void Test3D::input(Event &event) {

}
