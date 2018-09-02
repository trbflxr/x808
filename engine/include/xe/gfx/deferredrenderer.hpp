//
// Created by FLXR on 8/4/2018.
//

#ifndef X808_DEFERREDRENDERER_HPP
#define X808_DEFERREDRENDERER_HPP


#include <xe/common.hpp>
#include <xe/gfx/camera.hpp>
#include <xe/gfx/fx/gbuffer.hpp>
#include <xe/gfx/fx/final.hpp>
#include <xe/gfx/uniformbuffer.hpp>

namespace xe {

	class XE_API DeferredRenderer {
	public:
		explicit DeferredRenderer(uint width, uint height);
		~DeferredRenderer();

		void render(const Scene *scene, Camera *camera) const;

		inline const fx::GBuffer *getGBuffer() const { return gBuffer; }
		inline const fx::Final *getFinalFX() const { return final; }

	private:
		void updateUBO(const mat4 &view, const mat4 &proj, const vec3 &pos, const vec3 &look) const;

	private:
		fx::GBuffer *gBuffer;
		fx::Quad *quad;
		fx::Final *final;

		xe::UniformBuffer *cameraUBO;
	};

}


#endif //X808_DEFERREDRENDERER_HPP
