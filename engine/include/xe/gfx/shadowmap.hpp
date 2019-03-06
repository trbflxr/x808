//
// Created by FLXR on 3/5/2019.
//

#ifndef X808_SHADOWMAP_HPP
#define X808_SHADOWMAP_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/model.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

	class Scene;

	class XE_API ShadowMap : NonCopyable {
	public:
		explicit ShadowMap(uint size, uint layers);
		~ShadowMap() override;

		void render(const Scene *scene, const mat4 &view, const mat4 &projection);

		inline const Texture *getTexture() const { return texture; }

	private:
		uint size;
		uint layers;

		FrameBuffer *buffer;
		const Texture *depthTexture;
		const Texture *texture;

		const Shader *shader;
	};

}


#endif //X808_SHADOWMAP_HPP
