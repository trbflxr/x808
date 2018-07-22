//
// Created by FLXR on 7/12/2018.
//

#ifndef X808_TEST3D_HPP
#define X808_TEST3D_HPP


#include <gfx/layers/layer.hpp>
#include <gfx/mesh.hpp>
#include <gfx/api/shader.hpp>
#include <gfx/forwardrenderer.hpp>
#include <gfx/camera/fpscamera.hpp>
#include <gfx/lights/directionallight.hpp>
#include <gfx/lights/pointlight.hpp>
#include <gfx/lights/spotlight.hpp>
#include "dummyplayer.hpp"

using namespace xe;
using namespace gfx;
using namespace gfx::api;

class Test3D : public Layer {
public:
	explicit Test3D();
	~Test3D() override;

	void render() override;

	void tick() override;

	void update(float delta) override;
	void fixedUpdate(float delta) override;

	void input(Event &event) override;

private:
	ECS &ecs;

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

	Model *rockModel;
	Model *monkeyModel;
	Model *monkeyModel2;
	Model *stallModel;

	Model *planeModel0;
	Model *planeModel1;
	Model *planeModel2;

	AmbientLight *ambientLight;
	ForwardRenderer *renderer;

	DirectionalLight *directionalLight;

	PointLight *pointLight;
	PointLight *pointLight2;
	PointLight *pointLight3;
	PointLight *pointLight4;

	bool hookSpotLight;
	SpotLight *spotLight;

	DummyPlayer *player;
};


#endif //X808_TEST3D_HPP
