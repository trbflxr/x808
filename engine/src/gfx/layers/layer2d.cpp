//
// Created by FLXR on 6/29/2018.
//

#include "layer2d.hpp"
#include "application/application.hpp"

xe::gfx::Layer2D::Layer2D(const xe::mat4 &projectionMatrix) {
	const uint width = Application::getApplication().getWindowWidth();
	const uint height = Application::getApplication().getWindowHeight();
}

xe::gfx::Layer2D::~Layer2D() {

}

void xe::gfx::Layer2D::init() {

}

void xe::gfx::Layer2D::render() {

}

bool xe::gfx::Layer2D::resize(uint width, uint height) {
	return false;
}
