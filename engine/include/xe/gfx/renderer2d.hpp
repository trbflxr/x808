//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_RENDERER2D_HPP
#define X808_RENDERER2D_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/math/math.hpp>
#include <xe/gfx/camera.hpp>
#include <xe/gfx/baseshader.hpp>
#include <xe/gfx/vertexarray.hpp>
#include <xe/gfx/indexbuffer.hpp>
#include <xe/ecs/components/spritecomponent.hpp>
#include <xe/ecs/components/transform2dcomponent.hpp>
#include <xe/ecs/components/textcomponent.hpp>

namespace xe {

	struct VertexData {
		vec3 vertex;
		vec2 uv;
		float tid;
		uint color;
	};

#define RENDERER_VERTEX_SIZE sizeof(VertexData)

	class XE_API Renderer2D {
	public:
		struct RenderTarget {
			const SpriteComponent *sprite;
			const Transform2DComponent *transform;

			RenderTarget(const SpriteComponent *sprite,
			             const Transform2DComponent *transform) noexcept :
					sprite(sprite), transform(transform) { }
		};

	public:
		explicit Renderer2D(uint width, uint height);
		explicit Renderer2D(const vec2u &screenSize);
		~Renderer2D();

		void push(const mat4 &matrix, bool override = false);
		void pop();

		void setCamera(Camera *camera);

		void begin();
		void flush();

		void submit(const SpriteComponent *sprite, const Transform2DComponent *transform);
		void submitText(const TextComponent *text);

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
		float submitTexture(const Texture *texture);

		void submitInternal(RenderTarget target);
		void submitTextInternal(const TextComponent *component);

		void end();
		void flushInternal();

	private:
		std::vector<mat4> transformationStack;
		const mat4 *transformationBack;

		BaseShader *shader;
		std::vector<Uniform> uniforms;
		std::vector<UniformData> uniformData;

		VertexArray *vertexArray;
		IndexBuffer *indexBuffer;
		uint indexCount;
		VertexData *buffer;

		std::vector<const Texture *> textures;

		vec2u screenSize;
		vec2u viewportSize;

		Camera *camera;

		std::vector<RenderTarget> targets;
		std::vector<const TextComponent *> text;
	};

}


#endif //X808_RENDERER2D_HPP