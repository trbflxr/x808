//
// Created by FLXR on 7/12/2018.
//

#ifndef X808_FORWARDRENDERER_HPP
#define X808_FORWARDRENDERER_HPP


#include <gfx/camera/fpscamera.hpp>

#include "gfx/api/texture.hpp"
#include "gfx/lights/baselight.hpp"
#include "mesh.hpp"

namespace xe { namespace gfx {

	class XE_API ForwardRenderer {
	public:
		explicit ForwardRenderer();
		~ForwardRenderer();

		void render(const Mesh *mesh);

	private:
		std::vector<BaseLight *> lights;

		//temp
		FPSCamera *camera;
		const api::Texture *texture;
	};

}}


#endif //X808_FORWARDRENDERER_HPP
