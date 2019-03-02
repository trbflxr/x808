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

	gBuffer = new GBuffer(width, height);

	quad = new Quad(width, height);
	final = new FinalFX(width, height);

	BufferLayout cl;
	cl.push<mat4>("view");
	cl.push<mat4>("projection");
	cl.push<mat4>("invertedView");

	cameraUBO = new UniformBuffer(BufferStorage::Dynamic, 1, cl);
}

Test3D::~Test3D() {
	delete player;
	delete camera;

	delete gBuffer;
	delete cameraUBO;

	delete model;
	delete material;
}

void Test3D::render() {
	cameraUBO->bind();
	cameraUBO->update(&camera->getView(), 0);
	cameraUBO->update(&camera->getProjection(), 1);
	cameraUBO->update(&camera->getInvertedView(), 2);
	cameraUBO->unbind();

	Renderer::enableDepthTesting(true);
	Renderer::enableCullFace(true);
	Renderer::enableBlend(false);
	Renderer::setCullFace(CullFace::Back);

	gBuffer->passGeometry({model});

	gBuffer->passLightAccumulation(quad, final->getFinalFBO());

	Renderer::enableDepthTesting(false);
	Renderer::enableBlend(true);

	final->render(quad);
}

void Test3D::renderImGui() {
	ImGui::Begin("Test3D");

	ImGui::Text("fps: %i", app.getFPS());
	ImGui::Text("frame time: %.3f", app.getFrameTime());
	ImGui::Text("draw calls: %i", Renderer::getDC());
	ImGui::Separator();
	ImGui::Dummy({10.0f, 0.0f});

	ImGui::Image(reinterpret_cast<void *>(gBuffer->getDepth()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::Image(reinterpret_cast<void *>(gBuffer->getPosition()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::Image(reinterpret_cast<void *>(gBuffer->getNormals()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::Image(reinterpret_cast<void *>(gBuffer->getAlbedo()->getHandle()), {128, 72}, {0, 1}, {1, 0});

	ImGui::End();
}

void Test3D::update(float delta) {
	player->update(delta);

	model->rotate(vec3::UnitY(), 30 * delta);
}

void Test3D::input(Event &event) {
	player->input(event);
}
