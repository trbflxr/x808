//
// Created by FLXR on 9/6/2018.
//

#ifndef X808_IRENDERER2D_HPP
#define X808_IRENDERER2D_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/math/mat4.hpp>
#include <xe/gfx/texture.hpp>
#include <xe/gfx/vertexarray.hpp>
#include <xe/gfx/indexbuffer.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/camera.hpp>

namespace xe {

#define XE_RENDERER2D_MAX_SPRITES 120000

	class XE_API IRenderer2D {
	protected:
		struct VertexData {
			vec3 vertex;
			vec2 uv;
			float tid;
			uint color;
		};

	public:
		explicit IRenderer2D(uint width, uint height, Camera *camera);
		virtual ~IRenderer2D();

		virtual void begin() = 0;
		virtual void end() = 0;

		virtual void flush() = 0;

		void push(const mat4 &matrix, bool override = false);
		void pop();

		inline uint getWidth() const { return width; }
		inline void setWidth(uint width) { IRenderer2D::width = width; }

		inline uint getHeight() const { return height; }
		inline void setHeight(uint height) { IRenderer2D::height = height; }

	protected:
		void updateCamera();
		void updateIndexBuffer();

		float submitTexture(const Texture *texture);

		void releaseBuffer();

		void appendIndices(const uint *indices, uint size, uint offset);

	protected:
		friend class BatchRenderer2D;

		Camera *camera;
		Shader *shader;

		IndexBuffer *indexBuffer;
		uint *indices;
		uint indicesSize;
		uint indicesOffset;

		VertexArray *vertexArray;

		uint width;
		uint height;

		std::vector<mat4> transformationStack;
		const mat4 *transformationBack;

		std::vector<const Texture *> textures;

		//constants
		const uint maxTextureUnits;
	};

}


#endif //X808_IRENDERER2D_HPP
