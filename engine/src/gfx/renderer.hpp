//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_RENDERER_HPP
#define X808_RENDERER_HPP


#include "common.hpp"
#include "xeint.hpp"

namespace xe { namespace gfx {

	enum RendererBufferType {
		RENDERER_BUFFER_NONE = 0,
		RENDERER_BUFFER_COLOR = BIT(0),
		RENDERER_BUFFER_DEPTH = BIT(1),
		RENDERER_BUFFER_STENCIL = BIT(2)
	};

	enum class BlendFunction {
		NONE, ZERO, ONE, SOURCE_ALPHA, DESTINATION_ALPHA, ONE_MINUS_SOURCE_ALPHA
	};

	enum class BlendEquation {
		NONE, ADD, SUBTRACT
	};

	class XE_API Renderer {
	private:
		friend class Renderer2D;

	public:
		static void init();

		static void clear(uint buffer) { instance->clearInternal(buffer); }
		static void flush() { instance->flushInternal(); }

		static void setDepthTesting(bool enabled) { instance->setDepthTestingInternal(enabled); }
		static void setBlend(bool enabled) { instance->setBlendInternal(enabled); }

		static void setViewport(uint x, uint y, uint width, uint height) {
			instance->setViewportInternal(x, y, width, height);
		}

		static void setBlendFunction(BlendFunction source, BlendFunction destination) {
			instance->setBlendFunctionInternal(source, destination);
		}

		static void setBlendEquation(BlendEquation equation) {
			instance->setBlendEquationInternal(equation);
		}

		static uint getDC() { return dc; }
		static uint resetDC() { dc = 0; }

	protected:
		virtual void initInternal() = 0;

		virtual void clearInternal(uint buffer) = 0;
		virtual void flushInternal() = 0;

		virtual void setDepthTestingInternal(bool enabled) = 0;
		virtual void setBlendInternal(bool enabled) = 0;

		virtual void setViewportInternal(uint x, uint y, uint width, uint height) = 0;

		virtual void setBlendFunctionInternal(BlendFunction source, BlendFunction destination) = 0;
		virtual void setBlendEquationInternal(BlendEquation equation) = 0;

	private:
		static Renderer *instance;
		static uint dc;
	};

}}


#endif //X808_RENDERER_HPP
