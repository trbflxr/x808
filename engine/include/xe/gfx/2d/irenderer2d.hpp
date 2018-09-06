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

	class XE_API IRenderer2D {
	protected:
		struct VertexData {
			vec3 vertex;
			vec2 uv;
			float tid;
			uint color;
		};

#define RENDERER2D_VERTEX_SIZE sizeof(VertexData)

#define RENDERER2D_MAX_SPRITES     60000
#define RENDERER2D_SPRITE_SIZE     (RENDERER2D_VERTEX_SIZE * 4)
#define RENDERER2D_BUFFER_SIZE     (RENDERER2D_SPRITE_SIZE * RENDERER2D_MAX_SPRITES)
#define RENDERER2D_INDICES_SIZE    (RENDERER2D_MAX_SPRITES * 6)
#define RENDERER2D_MAX_TEXTURES    32

	public:
		explicit IRenderer2D(uint width, uint height);
		virtual ~IRenderer2D();

		virtual void begin() = 0;
		virtual void end() = 0;

		virtual void flush() = 0;

		virtual void setCamera(Camera *camera);

		inline uint getWidth() const { return width; }
		inline void setWidth(uint width) { IRenderer2D::width = width; }

		inline uint getHeight() const { return height; }
		inline void setHeight(uint height) { IRenderer2D::height = height; }

	protected:
		void push(const mat4 &matrix, bool override = false);
		void pop();

		float submitTexture(const Texture *texture);

		void releaseBuffer();

	protected:
		Camera *camera;
		Shader *shader;

		VertexArray *vertexArray;
		IndexBuffer *indexBuffer;
		uint indexCount;
		VertexData *buffer;

		uint width;
		uint height;

		std::vector<mat4> transformationStack;
		const mat4 *transformationBack;

		std::vector<const Texture *> textures;
	};

}


#endif //X808_IRENDERER2D_HPP
