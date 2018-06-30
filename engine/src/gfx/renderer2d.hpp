//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_RENDERER2D_HPP
#define X808_RENDERER2D_HPP


#include "common.hpp"
#include "xeint.hpp"
#include "gfx/camera/camera.hpp"
#include "color.hpp"
#include "renderable2d.hpp"
#include "gfx/api/vertexarray.hpp"
#include "gfx/api/indexbuffer.hpp"
#include "gfx/api/shader.hpp"

namespace xe { namespace gfx {

	class XE_API Renderer2D {
	public:
		explicit Renderer2D(uint width, uint height);
		explicit Renderer2D(const vec2u &screenSize);
		~Renderer2D();

		void push(const mat4 &matrix, bool override = false);
		void pop();

		void setCamera(Camera *camera);

		void begin();
		void submit(const Renderable2D *renderable);
		void end();
		void flush();

		void drawLine(float x0, float y0, float x1, float y1, uint color = color::WHITE, float thickness = 0.02f);
		void drawLine(const vec2 &start, const vec2 &end, uint color = color::WHITE, float thickness = 0.02f);
		void drawRect(float x, float y, float width, float height, uint color = color::WHITE);
		void drawRect(const vec2 &position, const vec2 &size, uint color = color::WHITE);
		void drawRect(const rect &rectangle, uint color = color::WHITE);

		void fillRect(float x, float y, float width, float height, uint color = color::WHITE);
		void fillRect(const vec2 &position, const vec2 &size, uint color = color::WHITE);
		void fillRect(const rect &rectangle, uint color = color::WHITE);

		//todo: draw string function

		inline const vec2u &getScreenSize() const { return screenSize; }
		inline void setScreenSize(const vec2u &size) { screenSize = size; }

		inline const vec2u &getViewportSize() const { return viewportSize; }
		inline void setViewportSize(const vec2u &size) { viewportSize = size; }

	private:
		void init();
		float submitTexture(api::Texture *texture);

	private:
		std::vector<mat4> transformationStack;
		const mat4 *transformationBack;

		api::Shader *shader;

		api::VertexArray *vertexArray;
		api::IndexBuffer *indexBuffer;
		uint indexCount;
		VertexData *buffer;
		std::vector<api::Texture *> textures;

		vec2u screenSize;
		vec2u viewportSize;

		api::VertexArray *screenQuad;
		Camera *camera;
	};

}}


#endif //X808_RENDERER2D_HPP
