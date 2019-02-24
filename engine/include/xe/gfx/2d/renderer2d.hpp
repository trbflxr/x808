//
// Created by FLXR on 9/6/2018.
//

#ifndef X808_RENDERER2D_HPP
#define X808_RENDERER2D_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/gfx/camera.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/indexbuffer.hpp>
#include <xe/gfx/vertexarray.hpp>
#include <xe/gfx/uniformbuffer.hpp>
#include <xe/gfx/2d/text.hpp>
#include <xe/gfx/2d/irenderable2d.hpp>
#include <xe/gfx/2d/light2d.hpp>

namespace xe {

#define XE_R2D_MAX_SPRITES 120000

	class XE_API Renderer2D {
	private:
		struct VertexData {
			vec3 vertex;
			vec2 uv;
			uint color;
			int32 useTexture;
			int32 text;
		};

	public:
		explicit Renderer2D(uint width, uint height, Camera *camera,
		                    bool enableLighting = false,
		                    const Shader *customShader = nullptr);
		virtual ~Renderer2D();

		void submit(const IRenderable2D *target);
		void submit(const Text *text);

		void begin();
		void end();
		void flush();

		void push(const mat4 &matrix, bool override = false);
		void pop();

		void useLight(const Light2D *light);
		void setAmbientLight(const vec3 &color);

		inline uint getWidth() const { return width; }
		inline void setWidth(uint width) { Renderer2D::width = width; }

		inline uint getHeight() const { return height; }
		inline void setHeight(uint height) { Renderer2D::height = height; }

		inline const Camera *getCamera() const { return camera; }
		inline void setCamera(Camera *camera) { Renderer2D::camera = camera; }

		inline const Shader *getShader() const { return shader; }

		inline void enableWireframe(bool flag) { Renderer2D::enableWireframe_ = flag; }

	private:
		void beginInternal();

		void setupBuffer();

		void updateCamera();
		void updateIndexBuffer();

		int32 submitTexture(const Texture *texture);

		void releaseBuffer();

		void appendIndices(const uint *indices, uint size, uint offset);

		void submitString(const string &str, const Font *font, uint color,
		                  float scale, const mat4 &transform, float &x, float &y);

	private:
		uint width;
		uint height;

		Camera *camera;
		const Shader *shader;

		IndexBuffer *indexBuffer;
		uint *indices;
		uint indicesSize;
		uint indicesOffset;

		VertexArray *vertexArray;

		std::vector<mat4> transformationStack;
		const mat4 *transformationBack;

		uint sampler0;
		const Texture *activeTexture;

		bool enableWireframe_;

		VertexData *buffer;

		//light stuff
		bool enableLighting;
		vec3 ambient;
		UniformBuffer *lightUBO;

		std::vector<const Light2D *> lights;
	};
}


#endif //X808_RENDERER2D_HPP
