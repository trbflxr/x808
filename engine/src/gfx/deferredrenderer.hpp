//
// Created by FLXR on 8/4/2018.
//

#ifndef X808_DEFERREDRENDERER_HPP
#define X808_DEFERREDRENDERER_HPP


#include "common.hpp"
#include "irenderer3d.hpp"

namespace xe {

	class XE_API DeferredRenderer : public IRenderer3D {
	public:
		explicit DeferredRenderer(uint width, uint height, Camera *camera);
		~DeferredRenderer();

		void begin() override;
		void submit(const Mesh *mesh, const Material *material, const Transform &transform) override;
		void flush() override;

	};

}


#endif //X808_DEFERREDRENDERER_HPP
