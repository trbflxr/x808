//
// Created by FLXR on 3/1/2019.
//

#ifndef X808_TEST3D_HPP
#define X808_TEST3D_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/camera.hpp>
#include <xe/gfx/mesh.hpp>
#include <xe/gfx/shader.hpp>

class Test3D : public xe::Layer {
public:
	explicit Test3D();
	~Test3D() override;

	void render() override;
	void renderImGui() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

private:
	xe::Camera *camera;

	//test
	xe::Mesh *mesh;
	xe::Shader *shader;
	xe::Texture *texture;
};


#endif //X808_TEST3D_HPP
