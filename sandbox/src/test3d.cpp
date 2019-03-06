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

	ShadowParameters sp;
	renderer = new DeferredRenderer(width, height, camera, sp);
	renderer->enableLightObjects(true);
	renderer->enableLightBounds(true);

	TextureParameters params;
	TextureManager::add(new Texture("diffuse", "sponza_floor_diff.jpg", params));
	TextureManager::add(new Texture("specular", "sponza_floor_spec.jpg", params));

	TextureManager::add(new Texture("diffuse1", "Fabric_Padded_diffuse.jpg", params));
	TextureManager::add(new Texture("normal1", "Fabric_Padded_normal.jpg", params));
//	TextureManager::add(new Texture("disp1", "pebble-d.bmp", params));

	scene = new Scene();

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
	scene->add(model);

	Model *monkey = new Model("tm0", "monkey3.obj");
	monkey->setMaterial(material1);
	monkey->setPosition({-5, 2, 5});
	scene->add(monkey);

	Model *plane = new Model("tm0", "plane0.obj");
	plane->setMaterial(material);
	plane->setPosition({-10, 0, 0});
//	plane->rotate(vec3::UnitY(), 180.0f);
//	plane->rotate(vec3::UnitZ(), -45.0f);
	scene->add(plane);

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
		scene->add(m);

		x += step;
	}

	player = new DummyPlayer(camera);


	sl = new SpotLight("l0", Mesh::spotLightMesh("l0_m"));
	sl->setPosition({12, 11, 10.0});
	sl->rotate(vec3::UnitX(), -45);
	sl->rotate(vec3::UnitZ(), -10);
	sl->setColor({1.0f, 0.9f, 0.8f});
	sl->setSpotAngle(40.0f);
	sl->setIntensity(15);
	sl->setFalloff(20.0f);
	sl->setShadowed(true);
	sl->setShadowId(1);
	scene->add(sl);

	SpotLight *sl1 = new SpotLight("l0", Mesh::spotLightMesh("l0_m"));
	sl1->setPosition({-8, 8, 12.0});
	sl1->rotate(vec3::UnitX(), -50);
	sl1->rotate(vec3::UnitY(), -15);
	sl1->setColor({0.3f, 0.6f, 0.8f});
	sl1->setSpotAngle(40.0f);
	sl1->setIntensity(15);
	sl1->setFalloff(20.0f);
	sl1->setShadowed(true);
	sl1->setShadowId(0);
	scene->add(sl1);

	pl = new PointLight("l1", Mesh::pointLightMesh("l1_m"));
	pl->setPosition({-10, 2, 0});
	pl->setColor({0.5f, 0.8f, 0.8f});
	pl->setIntensity(4.0f);
	pl->setFalloff(10.0f);
	scene->add(pl);
}

Test3D::~Test3D() {
	delete player;
	delete camera;
	delete renderer;

	delete material;

	delete scene;
}

void Test3D::render() {
	renderer->render(scene);
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

	static bool fxaa = true;
	if (ImGui::Checkbox("FXAA", &fxaa)) {
		renderer->useFXAA(fxaa);
	}

	static bool lightObjects = true;
	if (ImGui::Checkbox("Light objects", &lightObjects)) {
		renderer->enableLightObjects(lightObjects);
	}

	static bool lightBounds = true;
	if (ImGui::Checkbox("Light bounds", &lightBounds)) {
		renderer->enableLightBounds(lightBounds);
	}

	static bool wireframe = false;
	if (ImGui::Checkbox("Wireframe", &wireframe)) {
		renderer->enableWireframe(wireframe);
	}

	static bool cull = true;
	if (ImGui::Checkbox("Cull test", &cull)) {
		renderer->enableCullTest(cull);
	}

	static bool m1n = true;
	if (ImGui::Checkbox("M1 normals", &m1n)) {
		if (m1n) {
			material1->setNormal(GETTEXTURE("normal1"));
		} else {
			material1->setNormal(nullptr);
		}
	}

	static bool sls = sl->isShadowed();
	if (ImGui::Checkbox("sl0 shadows", &sls)) {
		sl->setShadowed(sls);
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

	const GBuffer *buffer = renderer->getGBuffer();

	ImGui::Begin("Buffers");
	ImGui::Image(reinterpret_cast<void *>(buffer->getDepthStencilTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::SameLine();
	ImGui::Image(reinterpret_cast<void *>(buffer->getDiffuseTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::SameLine();
	ImGui::Image(reinterpret_cast<void *>(buffer->getPositionTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::SameLine();
	ImGui::Image(reinterpret_cast<void *>(buffer->getNormalTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::SameLine();
	ImGui::Image(reinterpret_cast<void *>(buffer->getSpecularTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::SameLine();
	ImGui::Image(reinterpret_cast<void *>(buffer->getLightDiffuseTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::SameLine();
	ImGui::Image(reinterpret_cast<void *>(buffer->getLightSpecularTexture()->getHandle()), {128, 72}, {0, 1}, {1, 0});
	ImGui::End();

	ImGui::Begin("Test");
//	ImGui::Image(reinterpret_cast<void *>(buffer->getNormalTexture()->getHandle()), {512, 288}, {0, 1}, {1, 0});
//	ImGui::Image(reinterpret_cast<void *>(sm->getTexture()->getHandle()), {512, 512}, {0, 1}, {1, 0});
	ImGui::End();
}

void Test3D::update(float delta) {
	scene->updateLights(camera);

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
