//
// Created by FLXR on 8/4/2018.
//

#include <resources/texturemanager.hpp>
#include <gfx/api/texture.hpp>
#include <ecs/components/modelcomponent.hpp>
#include <ecs/components/transformcomponent.hpp>
#include "test3ddeferred.hpp"

#include <resources/shaderfile.hpp>

using namespace xe;
using namespace xe::api;

Test3DDeferred::Test3DDeferred() {
	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	TextureParameters params(TextureTarget::TEX2D, TextureFilter::AF16);
	TextureManager::add(Texture::create("rock", "assets/textures/rock.png", params));
//	TextureManager::add(Texture2D::create("2", "assets/textures/test3.png", params));
//	TextureManager::add(Texture2D::create("4", "assets/textures/test5.png", params));
//	TextureManager::add(Texture2D::create("stall", "assets/textures/stall.png", params));
//	TextureManager::add(Texture2D::create("bricks", "assets/textures/bricks.jpg", params));
//	TextureManager::add(Texture2D::create("bricks2", "assets/textures/bricks2.jpg", params));
//	TextureManager::add(Texture2D::create("bricksNormal", "assets/textures/bricksNormal.jpg", params));
//	TextureManager::add(Texture2D::create("bricksNormal2", "assets/textures/bricksNormal2.png", params));
//	TextureManager::add(Texture2D::create("bricksDisp", "assets/textures/bricksDisp.png", params));
//	TextureManager::add(Texture2D::create("bricksDisp2", "assets/textures/bricksDisp2.jpg", params));
//	TextureManager::add(Texture2D::create("bgr", "assets/textures/bgr.jfif", params));

//	//init objects
//	ModelComponent model;
//	TransformComponent transform;
//
//	camera = new Camera(mat4::perspective(80.0f, 8.0f / 6.0f, 0.1f, 1000));
//
//	DummyPlayerComponent playerComponent(camera);
//	player = ecs.makeEntity(playerComponent, transform);
//
////	renderer = new ForwardRenderer(800, 600, camera, true);
////	rendererSystem = new ForwardRendererSystem(renderer);
////	renderingPipeline.addSystem(*rendererSystem);
//
//	//materials
//	monkeyMaterial = new Material(GETTEXTURE("2"), 50, 2.2f);
//	monkeyMaterial2 = new Material(GETTEXTURE("4"), 1, 0.2f);
//	rockMaterial = new Material(GETTEXTURE("rock"), 2, 0.2f);
//	stallMaterial = new Material(GETTEXTURE("stall"), 2, 0.2f);
//
//	planeMaterial0 = new Material(GETTEXTURE("bgr"), 3, 0.1f);
//
//	planeMaterial1 = new Material(GETTEXTURE("bricks"), 4, 0.5f,
//	                              GETTEXTURE("bricksNormal"), GETTEXTURE("bricksDisp"), 0.03f, -0.5f);
//
//	planeMaterial2 = new Material(GETTEXTURE("bricks2"), 2, 0.5f,
//	                              GETTEXTURE("bricksNormal2"), GETTEXTURE("bricksDisp2"), 0.02f, -0.5f);
//
//	//meshes
//	rockMesh = new Mesh("assets/models/rock.obj");
//	monkeyMesh = new Mesh("assets/models/monkey3.obj");
//	stallMesh = new Mesh("assets/models/stall.obj");
//	planeMesh0 = new Mesh("assets/models/plane0.obj");
//	planeMesh1 = new Mesh("assets/models/plane1.obj");
//	cubeMesh = new Mesh("assets/models/cube.obj");
//
//
//	//models
//	model.mesh = monkeyMesh;
//	model.material = monkeyMaterial;
//	transform.transform.setTranslation({5, 0, -5});
//	transform.transform.setRotation(quat::rotationZ(30.0f));
//	monkeyModel = ecs.makeEntity(model, transform);
//
//	model.mesh = monkeyMesh;
//	model.material = monkeyMaterial2;
//	transform.transform.setTranslation({3, 0, -8});
//	transform.transform.setRotation(quat::rotationZ(0.0f));
//	monkeyModel2 = ecs.makeEntity(model, transform);
//
//	model.mesh = rockMesh;
//	model.material = rockMaterial;
//	transform.transform.setTranslation({0, 0, -5});
//	transform.transform.setRotation(quat::rotationZ(5.0f));
//	rockModel = ecs.makeEntity(model, transform);
//
//	model.mesh = stallMesh;
//	model.material = stallMaterial;
//	transform.transform.setTranslation({0, 0, -15});
//	transform.transform.setRotation(quat::rotationY(-90.0f));
//	stallModel = ecs.makeEntity(model, transform);
//
////	planes
//	model.mesh = planeMesh0;
//	model.material = planeMaterial0;
//	transform.transform.setTranslation({0, -5, -9});
//	transform.transform.setScale({3.4f, 3.4f, 3.4f});
//	planeModel0 = ecs.makeEntity(model, transform);
//
//	model.mesh = planeMesh0;
//	model.material = planeMaterial1;
//	transform.transform.setTranslation({22, -3, -5});
//	transform.transform.setScale({0.4f, 0.4f, 0.4f});
//	planeModel1 = ecs.makeEntity(model, transform);
//
//	model.mesh = planeMesh0;
//	model.material = planeMaterial2;
//	transform.transform.setTranslation({29, -3, -5});
//	transform.transform.setScale({0.4f, 0.4f, 0.4f});
//	planeModel2 = ecs.makeEntity(model, transform);
//
//
//	//cube
//	model.mesh = cubeMesh;
//	model.material = planeMaterial2;
//	transform.transform.setTranslation({10, -4.5f, -5});
//	transform.transform.rotate(vec3::YAXIS, 45.0f);
//	cubeModel = ecs.makeEntity(model, transform);

//	ShaderFile *f = ShaderFile::createFromFile(ShaderType::TESS_EVAL, "s1.txt", {"s2.txt"},
//	                                          {"#extension GL_ARB_bindless_texture : require"});
//	f->compile(450);

//	delete f;
}

Test3DDeferred::~Test3DDeferred() {
//	delete rockMesh;
//	delete monkeyMesh;
//	delete stallMesh;
//	delete planeMesh0;
//	delete planeMesh1;
//	delete cubeMesh;
//
//	delete rockMaterial;
//	delete monkeyMaterial;
//	delete monkeyMaterial2;
//	delete stallMaterial;
//	delete planeMaterial0;
//	delete planeMaterial1;
//	delete planeMaterial2;
//
//	delete playerControlSystem;
//
//	delete camera;
}

void Test3DDeferred::render() {
//	ecs.updateSystems(renderingPipeline, 0.0f);
}

void Test3DDeferred::update(float delta) {
//	ecs.updateSystems(mainSystems, delta);
}

void Test3DDeferred::fixedUpdate(float delta) {

}

void Test3DDeferred::input(Event &event) {
//	ecs.inputSystems(mainSystems, event);
}

