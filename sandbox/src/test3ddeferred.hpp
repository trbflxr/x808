//
// Created by FLXR on 8/4/2018.
//

#ifndef X808_TEST3DDEFERRED_HPP
#define X808_TEST3DDEFERRED_HPP


#include <gfx/layers/layer.hpp>
#include "dummyplayercontrolsystem.hpp"

class Test3DDeferred : public xe::Layer {
public:
	explicit Test3DDeferred();
	~Test3DDeferred();

	void render() override;

	void update(float delta) override;
	void fixedUpdate(float delta) override;

	void input(xe::Event &event) override;

private:
	xe::ECS ecs;
	xe::ECSSystemList mainSystems;
	xe::ECSSystemList renderingPipeline;

	xe::Camera *camera;

	DummyPlayerControlSystem *playerControlSystem;
	xe::EntityHandle player;

	//models
	xe::EntityHandle rockModel;
	xe::EntityHandle monkeyModel;
	xe::EntityHandle monkeyModel2;
	xe::EntityHandle stallModel;
	xe::EntityHandle planeModel0;
	xe::EntityHandle planeModel1;
	xe::EntityHandle planeModel2;
	xe::EntityHandle cubeModel;

	//meshes
	xe::Mesh *rockMesh;
	xe::Mesh *monkeyMesh;
	xe::Mesh *stallMesh;
	xe::Mesh *planeMesh0;
	xe::Mesh *planeMesh1;
	xe::Mesh *cubeMesh;

	//materials
	xe::Material *rockMaterial;
	xe::Material *monkeyMaterial;
	xe::Material *monkeyMaterial2;
	xe::Material *stallMaterial;
	xe::Material *planeMaterial0;
	xe::Material *planeMaterial1;
	xe::Material *planeMaterial2;
};


#endif //X808_TEST3DDEFERRED_HPP
