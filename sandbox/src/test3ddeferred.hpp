//
// Created by FLXR on 8/4/2018.
//

#ifndef X808_TEST3DDEFERRED_HPP
#define X808_TEST3DDEFERRED_HPP


#include <gfx/layers/layer.hpp>
#include "dummyplayercontrolsystem.hpp"

class Test3DDeferred : public xe::gfx::Layer {
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

	xe::gfx::Camera *camera;

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
	xe::gfx::Mesh *rockMesh;
	xe::gfx::Mesh *monkeyMesh;
	xe::gfx::Mesh *stallMesh;
	xe::gfx::Mesh *planeMesh0;
	xe::gfx::Mesh *planeMesh1;
	xe::gfx::Mesh *cubeMesh;

	//materials
	xe::gfx::Material *rockMaterial;
	xe::gfx::Material *monkeyMaterial;
	xe::gfx::Material *monkeyMaterial2;
	xe::gfx::Material *stallMaterial;
	xe::gfx::Material *planeMaterial0;
	xe::gfx::Material *planeMaterial1;
	xe::gfx::Material *planeMaterial2;
};


#endif //X808_TEST3DDEFERRED_HPP
