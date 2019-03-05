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

	TextureManager::add(new Texture("diffuse1", "Fabric_Padded_diffuse.jpg", params));
	TextureManager::add(new Texture("normal1", "Fabric_Padded_normal.jpg", params));
//	TextureManager::add(new Texture("disp1", "pebble-d.bmp", params));

	material = new Material("material");
	material->setDiffuse(GETTEXTURE("diffuse"));
	material->setSpecular(GETTEXTURE("specular"));
	material->setSpecularShininess(0.15f);

	material1 = new Material("material1");
	material1->setDiffuse(GETTEXTURE("diffuse1"));
	material1->setNormal(GETTEXTURE("normal1"));
//	material1->setDisplacement(GETTEXTURE("disp1"));

	model = new Model("tm0", "rock.obj");
	model->setMaterial(material);
	models.push_back(model);

	Model *monkey = new Model("tm0", "monkey3.obj");
	monkey->setMaterial(material1);
	monkey->setPosition({-5, 2, 5});
	models.push_back(monkey);

	Model *plane = new Model("tm0", "plane0.obj");
	plane->setMaterial(material);
	plane->setPosition({-10, 0, 0});
//	plane->rotate(vec3::UnitY(), 180.0f);
//	plane->rotate(vec3::UnitZ(), -45.0f);
	models.push_back(plane);

	float step = 6.0f;
	float z = -step;
	float x = 0.0f;
	for (int32 i = 0; i < 9; ++i) {
		if (i != 0 && i % 3 == 0) {
			z -= step;
			x = 0.0f;
		}

		Model *m = new Model("tm0", "rock.obj");
		m->setPosition({x, 0, z});
		m->setMaterial(material1);
		models.push_back(m);

		x += step;
	}

	player = new DummyPlayer(camera);

	gBuffer = new GBuffer(width, height);
	gBuffer->enableLightObjects(true);
	gBuffer->enableLightBounds(true);
	gBuffer->enableCullTest(true);

	quad = new Quad(width, height);
	final = new FinalFX(width, height);

	BufferLayout cl;
	cl.push<mat4>("view");
	cl.push<mat4>("projection");
	cl.push<vec4>("camPosition");
	cl.push<vec4>("camLook");

	cameraUBO = new UniformBuffer(BufferStorage::Dynamic, 1, cl);


	sl = new SpotLight("l0", Mesh::spotLightMesh("l0_m"));
	sl->setPosition({12, 11, 10.0});
	sl->rotate(vec3::UnitX(), -45);
	sl->rotate(vec3::UnitZ(), -10);
	sl->setColor({1.0f, 0.9f, 0.8f});
	sl->setSpotAngle(40.0f);
	sl->setIntensity(15);
	sl->setFalloff(20.0f);
	sl->update();
	lights.push_back(sl);

	pl = new PointLight("l1", Mesh::pointLightMesh("l1_m"));
	pl->setPosition({-10, 2, 0});
	pl->setColor({0.5f, 0.8f, 0.8f});
	pl->setIntensity(4.0f);
	pl->setFalloff(10.0f);
	pl->update();
	lights.push_back(pl);
}

Test3D::~Test3D() {
	delete player;
	delete camera;

	delete gBuffer;
	delete cameraUBO;

	delete material;

	for (const auto &m : models) {
		delete m;
	}

	for (const auto &l : lights) {
		delete l;
	}
}

void Test3D::render() {
	const vec4 p = vec4(camera->getPosition(), 1.0f);
	const vec4 l = vec4(camera->getRotation().getForward(), 0.0f);

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
	const vec3 &cl = camera->getRotation().getForward();

	ImGui::Begin("Test3D");

	ImGui::Text("fps: %i", app.getFPS());
	ImGui::Text("frame time: %.3f", app.getFrameTime());
	ImGui::Text("draw calls: %i", Renderer::getDC());
	ImGui::Text("camera: (%.1f, %.1f, %.1f)", cp.x, cp.y, cp.z);
	ImGui::Text("look: (%.1f, %.1f, %.1f)", cl.x, cl.y, cl.z);
	ImGui::Separator();
	ImGui::Dummy({10.0f, 0.0f});

	static bool lightObjects = true;
	if (ImGui::Checkbox("Light objects", &lightObjects)) {
		gBuffer->enableLightObjects(lightObjects);
	}

	static bool lightBounds = true;
	if (ImGui::Checkbox("Light bounds", &lightBounds)) {
		gBuffer->enableLightBounds(lightBounds);
	}

	static bool wireframe = false;
	if (ImGui::Checkbox("Wireframe", &wireframe)) {
		gBuffer->enableWireframe(wireframe);
	}

	static bool cull = true;
	if (ImGui::Checkbox("Cull test", &cull)) {
		gBuffer->enableCullTest(cull);
	}

	static bool m1n = true;
	if (ImGui::Checkbox("M1 normals", &m1n)) {
		if (m1n) {
			material1->setNormal(GETTEXTURE("normal1"));
		} else {
			material1->setNormal(nullptr);
		}
	}

	const float width = ImGui::GetContentRegionAvailWidth();
	ImGui::PushItemWidth(width);
	static float intensity = pl->getIntensity();
	if (ImGui::SliderFloat("I", &intensity, 0.1f, 100.0f, "%.2f", 1.5f)) {
		pl->setIntensity(intensity);
	}

	static float spec = material->getSpecularShininess();
	ImGui::Text("Specular shininess");
	if (ImGui::SliderFloat("S", &spec, 0.0f, 1.0f, "%.3f")) {
		material->setSpecularShininess(spec);
	}
	ImGui::PopItemWidth();


	ImGui::End();

	ImGui::Begin("Buffers");
	ImGui::Image(reinterpret_cast<void *>(gBuffer->getDepthStencilTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::SameLine();
	ImGui::Image(reinterpret_cast<void *>(gBuffer->getDiffuseTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::SameLine();
	ImGui::Image(reinterpret_cast<void *>(gBuffer->getPositionTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::SameLine();
	ImGui::Image(reinterpret_cast<void *>(gBuffer->getNormalTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::SameLine();
	ImGui::Image(reinterpret_cast<void *>(gBuffer->getSpecularTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::SameLine();
	ImGui::Image(reinterpret_cast<void *>(gBuffer->getLightDiffuseTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::SameLine();
	ImGui::Image(reinterpret_cast<void *>(gBuffer->getLightSpecularTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::End();

	ImGui::Begin("Test");
	ImGui::Image(reinterpret_cast<void *>(gBuffer->getNormalTexture()->getHandle()), {512, 288}, {0, 1}, {1, 0});
	ImGui::End();
}

void Test3D::update(float delta) {
	player->update(delta);

	model->rotate(vec3::UnitY(), 30 * delta);

	if (hook) {
		sl->setRotation(camera->getRotation());
		sl->setPosition(camera->getPosition());
	}
	if (hook2) {
		pl->setPosition(camera->getPosition());
	}

	if (rock) {
		model->setPosition(camera->getPosition());
	}
}

void Test3D::input(Event &event) {
	player->input(event);

	if (event.type == Event::KeyPressed) {
		if (event.key.code == Keyboard::F) {
			hook = !hook;
		}
		if (event.key.code == Keyboard::G) {
			hook2 = !hook2;
		}
		if (event.key.code == Keyboard::R) {
			rock = !rock;
		}
	}
}
