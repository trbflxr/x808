//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_RENDERER2D_HPP
#define X808_RENDERER2D_HPP


#include "common.hpp"
#include "xeint.hpp"
#include "camera.hpp"
#include "gfx/api/vertexarray.hpp"
#include "gfx/api/indexbuffer.hpp"
#include "gfx/api/shader.hpp"

namespace xe { namespace gfx {

	//todo: move to "renderable"
	struct VertexData {
		vec3 vertex;
		vec2 uv;
		float tid;
		uint color;
	};
#define RENDERER_VERTEX_SIZE sizeof(VertexData)

	class XE_API Renderer2D {
	public:
		explicit Renderer2D(uint width, uint height);
		explicit Renderer2D(const vec2u &screenSize);
		~Renderer2D();

		void push(const mat4 &matrix, bool override = false);
		void pop();

		void setCamera(Camera *camera);

		void begin();
		//todo: submit renderable
		void end();
		void flush();

		void drawLine(float x0, float y0, float x1, float y1, uint color = 0xffffffff, float thickness = 0.02f);
		void drawLine(const vec2 &start, const vec2 &end, uint color = 0xffffffff, float thickness = 0.02f);
		void drawRect(float x, float y, float width, float height, uint color = 0xffffffff);
		void drawRect(const vec2 &position, const vec2 &size, uint color = 0xffffffff);
		void drawRect(const rect &rectangle, uint color = 0xffffffff);

		void fillRect(float x, float y, float width, float height, uint color = 0xffffffff);
		void fillRect(const vec2 &position, const vec2 &size, uint color = 0xffffffff);
		void fillRect(const rect &rectangle, uint color = 0xffffffff);

		//todo: draw string function

		inline const vec2u &getScreenSize() const { return screenSize; }
		inline void setScreenSize(const vec2u &size) { screenSize = size; }

		inline const vec2u &getViewportSize() const { return viewportSize; }
		inline void setViewportSize(const vec2u &size) { viewportSize = size; }

	private:
		void init();

	private:
		std::vector<mat4> transformationStack;
		const mat4 *transformationBack;

		api::Shader *shader;

		api::VertexArray *vertexArray;
		api::IndexBuffer *indexBuffer;
//		unsigned vbo;
//		unsigned vao;
		uint indexCount;
		VertexData *buffer;

		vec2u screenSize;
		vec2u viewportSize;

		api::VertexArray *screenQuad;
		Camera *camera;
	};

}}


#endif //X808_RENDERER2D_HPP
