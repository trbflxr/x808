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

	void onEvent(Event &event) override;

private:
	ECS &ecs;

	Mesh *rockMesh;
	Material *material;

	Model *model;

	AmbientLight* ambientLight;
	ForwardRenderer *renderer;

	FPSCamera *camera;
};


#endif //X808_TEST3D_HPP
