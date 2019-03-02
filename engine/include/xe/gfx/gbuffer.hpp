//
// Created by FLXR on 3/2/2019.
//

#ifndef X808_GBUFFER_HPP
#define X808_GBUFFER_HPP


#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/model.hpp>
#include <xe/gfx/quad.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

	class XE_API GBuffer : NonCopyable {
	public:
		explicit GBuffer(uint width, uint height);
		~GBuffer() override;

		void passGeometry(const std::vector<Model *> &models) const;
		void passLightAccumulation(const Quad *quad, const FrameBuffer *final) const;

		inline const Texture *getDepth() const { return depth; }
		inline const Texture *getPosition() const { return position; }
		inline const Texture *getNormals() const { return normals; }
		inline const Texture *getAlbedo() const { return albedo; }

		inline uint getWidth() const { return width; }
		inline uint getHeight() const { return height; }

	private:
		void createTextures();
		void createShaders();

	private:
		uint width;
		uint height;

		const Texture *defaultNormal;
		const Texture *defaultSpecular;

		const Texture *depth;
		const Texture *position;
		const Texture *normals;
		const Texture *albedo;

		FrameBuffer *buffer;

		const Shader *geometry;
		const Shader *accumulation;
	};

}

#endif //X808_GBUFFER_HPP
