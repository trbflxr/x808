//
// Created by FLXR on 7/12/2018.
//

#ifndef X808_TEST3D_HPP
#define X808_TEST3D_HPP


#include <gfx/layers/layer.hpp>
#include <gfx/mesh.hpp>
#include <gfx/api/shader.hpp>
#include <gfx/forwardrenderer.hpp>
#include <gfx/lights/directionallight.hpp>
#include <gfx/lights/pointlight.hpp>
#include <gfx/lights/spotlight.hpp>
#include <gfx/api/framebuffer.hpp>
#include <ecs/systems/forwardrenderersystem.hpp>

#include "dummyplayercomponent.hpp"
#include "debugui.hpp"
#include "dummyplayercontrolsystem.hpp"

using namespace xe;
using namespace gfx;
using namespace gfx::api;

class Test3D : public Layer {
public:
	explicit Test3D(DebugUI *ui);
	~Test3D();

	void render() override;

	void tick() override;

	void update(float delta) override;
	void fixedUpdate(float delta) override;

	void input(Event &event) override;

private:
	ECS ecs;
	ECSSystemList mainSystems;
	ECSSystemList renderingPipeline;

	DebugUI *ui;

	Camera *camera;

	ForwardRenderer *renderer;
	ForwardRendererSystem *rendererSystem;

	DummyPlayerControlSystem *playerControlSystem;
	EntityHandle player;

	Material *rockMaterial;
	Material *monkeyMaterial;
	Material *monkeyMaterial2;
	Material *stallMaterial;
	Material *planeMaterial0;
	Material *planeMaterial1;
	Material *planeMaterial2;

	Mesh *rockMesh;
	Mesh *monkeyMesh;
	Mesh *stallMesh;
	Mesh *planeMesh0;
	Mesh *planeMesh1;
	Mesh *cubeMesh;

	EntityHandle rockModel;
	EntityHandle monkeyModel;
	EntityHandle monkeyModel2;
	EntityHandle stallModel;
	EntityHandle planeModel0;
	EntityHandle planeModel1;
	EntityHandle planeModel2;
	EntityHandle cubeModel;

	DirectionalLight *directionalLight;
	PointLight *pointLight;
	PointLight *pointLight2;
	PointLight *pointLight3;
	PointLight *pointLight4;
	bool hookSpotLight;
	SpotLight *spotLight;
};


#endif //X808_TEST3D_HPP
