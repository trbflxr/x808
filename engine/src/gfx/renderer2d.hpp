//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_RENDERER2D_HPP
#define X808_RENDERER2D_HPP


#include "common.hpp"
#include "xeint.hpp"
#include "color.hpp"
#include "renderable2d.hpp"
#include "gfx/camera/camera.hpp"
#include "gfx/api/vertexarray.hpp"
#include "gfx/api/indexbuffer.hpp"
#include "gfx/api/shader.hpp"
#include "text.hpp"

namespace xe { namespace gfx {

	struct UniformBuffer {
		byte *buffer;
		uint size;

		UniformBuffer() = default;
		explicit UniformBuffer(byte *buffer, uint size) :
				buffer(buffer), size(size) {
			memset(buffer, 0, size);
		}
	};

	struct R2DSysUniform {
		UniformBuffer buffer;
		uint offset;

		R2DSysUniform() = default;
		explicit R2DSysUniform(const UniformBuffer &buffer, uint offset) :
				buffer(buffer), offset(offset) { }
	};

	class XE_API Renderer2D {
	public:
		explicit Renderer2D(uint width, uint height);
		explicit Renderer2D(const vec2u &screenSize);
		~Renderer2D();

		void push(const mat4 &matrix, bool override = false);
		void pop();

		void setCamera(Camera *camera);

		void begin();
		void flush();

		void submit(const Renderable2D *renderable);
		void submitText(const Text *text);

		void drawLine(float x0, float y0, float x1, float y1, float z,
		              uint color = color::WHITE, float thickness = 0.02f);

		void drawLine(const vec2 &start, const vec2 &end, float z,
		              uint color = color::WHITE, float thickness = 0.02f);

		void drawRect(float x, float y, float width, float height, float z, uint color = color::WHITE);
		void drawRect(const vec2 &position, const vec2 &size, float z, uint color = color::WHITE);
		void drawRect(const rect &rectangle, float z, uint color = color::WHITE);

		void fillRect(float x, float y, float width, float height, float z, uint color = color::WHITE);
		void fillRect(const vec2 &position, const vec2 &size, float z, uint color = color::WHITE);
		void fillRect(const rect &rectangle, float z, uint color = color::WHITE);

		inline const vec2u &getScreenSize() const { return screenSize; }
		inline void setScreenSize(const vec2u &size) { screenSize = size; }

		inline const vec2u &getViewportSize() const { return viewportSize; }
		inline void setViewportSize(const vec2u &size) { viewportSize = size; }

	private:
		void init();
		float submitTexture(const api::Texture *texture);

		void submitInternal(const Renderable2D *renderable);
		void submitTextInternal(const Text *text);

		void end();
		void flushInternal();

	private:
		std::vector<mat4> transformationStack;
		const mat4 *transformationBack;

		api::Shader *shader;
		std::vector<R2DSysUniform> systemUniforms;
		std::vector<UniformBuffer> systemUniformBuffers;

		api::VertexArray *vertexArray;
		api::IndexBuffer *indexBuffer;
		uint indexCount;
		VertexData *buffer;

		std::vector<const api::Texture *> textures;

		vec2u screenSize;
		vec2u viewportSize;

		api::VertexArray *screenQuad;
		Camera *camera;

		std::vector<const Renderable2D *> targets;
		std::vector<const Text *> text;
	};

}}


#endif //X808_RENDERER2D_HPP
