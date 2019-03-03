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
	camera->setPosition({4.0f, 3.0f, 20.0f});

	TextureParameters params;
	TextureManager::add(new Texture("diffuse", "sponza_floor_diff.jpg", params));
	TextureManager::add(new Texture("specular", "sponza_floor_spec.jpg", params));

	material = new Material("material");
	material->setDiffuse(GETTEXTURE("diffuse"));
	material->setSpecular(GETTEXTURE("specular"));

	model = new Model("tm0", "rock.obj");
	model->setMaterial(material);

	player = new DummyPlayer(camera);

	gBuffer = new GBuffer(width, height);
	gBuffer->enableLightObjects(true);

	quad = new Quad(width, height);
	final = new FinalFX(width, height);

	BufferLayout cl;
	cl.push<mat4>("view");
	cl.push<mat4>("projection");
	cl.push<vec4>("camPosition");
	cl.push<vec4>("camLook");

	cameraUBO = new UniformBuffer(BufferStorage::Dynamic, 1, cl);

	models.push_back(model);

	SpotLight *l = new SpotLight("l0", Mesh::spotLightMesh("l0_m"));
	l->setPosition({25, 3, 0});
	l->rotate(vec3::UnitY(), 90);
	l->setColor({0.5f, 0.8f, 0.1f});
	l->setIntensity(50);
	l->setFalloff(30.0f);
	l->update();
	lights.push_back(l);

	PointLight *l1 = new PointLight("l1", Mesh::pointLightMesh("l1_m"));
	l1->setPosition({0, 3, 8});
	l1->setColor({0.5f, 0.8f, 0.8f});
	l1->setIntensity(20);
	l1->setFalloff(10.0f);
	l1->update();
	lights.push_back(l1);
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
	const vec4 p = vec4(camera->getPosition(), 1.0f);
	const vec4 l = vec4(camera->getRotation().getForward(), 1.0f);

	cameraUBO->bind();
	cameraUBO->update(&camera->getView(), 0);
	cameraUBO->update(&camera->getProjection(), 1);
	cameraUBO->update(&p, 2);
	cameraUBO->update(&l, 3);
	cameraUBO->unbind();

	Renderer::enableDepthMask(true);
	Renderer::enableDepthTesting(true);
	Renderer::enableCullFace(true);
	Renderer::setCullFace(CullFace::Back);

	gBuffer->passGeometry(models, lights);

	Renderer::enableDepthTesting(false);
	gBuffer->passLightAccumulation(quad, final->getFinalFBO());

	Renderer::enableDepthMask(true);
	Renderer::enableDepthTesting(false);

	final->render(quad);
}

void Test3D::renderImGui() {
	const vec3 &cp = camera->getPosition();

	ImGui::Begin("Test3D");

	ImGui::Text("fps: %i", app.getFPS());
	ImGui::Text("frame time: %.3f", app.getFrameTime());
	ImGui::Text("draw calls: %i", Renderer::getDC());
	ImGui::Text("camera: (%.1f, %.1f, %.1f)", cp.x, cp.y, cp.z);
	ImGui::Separator();
	ImGui::Dummy({10.0f, 0.0f});

	static bool lightObjects = true;
	if (ImGui::Checkbox("Light objects", &lightObjects)) {
		gBuffer->enableLightObjects(lightObjects);
	}

	static bool lightBounds = false;
	if (ImGui::Checkbox("Light bounds", &lightBounds)) {
		gBuffer->enableLightBounds(lightBounds);
	}

	static bool wireframe = false;
	if (ImGui::Checkbox("Wireframe", &wireframe)) {
		gBuffer->enableWireframe(wireframe);
	}

	static bool cull = false;
	if (ImGui::Checkbox("Cull test", &cull)) {
		gBuffer->enableCullTest(cull);
	}

	ImGui::Separator();
	ImGui::Dummy({10.0f, 0.0f});

	ImGui::Image(reinterpret_cast<void *>(gBuffer->getDepthStencilTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::Image(reinterpret_cast<void *>(gBuffer->getDiffuseTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::Image(reinterpret_cast<void *>(gBuffer->getNormalDepthTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::Image(reinterpret_cast<void *>(gBuffer->getSpecularTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::Image(reinterpret_cast<void *>(gBuffer->getLightDiffuseTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::Image(reinterpret_cast<void *>(gBuffer->getLightSpecularTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});

	ImGui::End();
}

void Test3D::update(float delta) {
	player->update(delta);

	model->rotate(vec3::UnitY(), 30 * delta);
}

void Test3D::input(Event &event) {
	player->input(event);
}
