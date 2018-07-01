//
// Created by FLXR on 6/30/2018.
//

#include "renderable2d.hpp"
#include "renderer2d.hpp"

xe::gfx::Renderable2D::Renderable2D() :
		texture(nullptr) {

	UVs = getDefaultUVs();
}


xe::gfx::Renderable2D::Renderable2D(const vec2 &size, uint color) :
		size(size),
		color(color),
		visible(true),
		texture(nullptr) {

	UVs = getDefaultUVs();
}

void xe::gfx::Renderable2D::submit(xe::gfx::Renderer2D *renderer) {
	renderer->submit(this);
}

const std::vector<xe::vec2> &xe::gfx::Renderable2D::getDefaultUVs() {
	static std::vector<vec2> UVs;
	if (UVs.empty()) {
		UVs.emplace_back(0, 1);
		UVs.emplace_back(1, 1);
		UVs.emplace_back(1, 0);
		UVs.emplace_back(0, 0);
	}
	return UVs;
}