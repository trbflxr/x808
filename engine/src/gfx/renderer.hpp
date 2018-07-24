//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_RENDERER_HPP
#define X808_RENDERER_HPP


#include "common.hpp"
#include "xeint.hpp"
#include "color.hpp"
#include "math/vec4.hpp"

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

	enum class DepthFunction {
		NONE, EQUAL, LESS
	};

	enum class CullFace {
		NONE, FRONT, BACK
	};

	class XE_API Renderer {
	private:
		friend class Renderer2D;

	public:
		static void init();

		static void clear(uint buffer) { instance->clearInternal(buffer); }
		static void flush() { instance->flushInternal(); }

		static void setClearColor(uint color) { instance->setClearColorInternal(color::decode(color)); }
		static void setClearColor(const vec4 &color) { instance->setClearColorInternal(color); }

		static void enableVsync(bool enabled) { instance->enableVsyncInternal(enabled); }
		static void enableDepthTesting(bool enabled) { instance->enableDepthTestingInternal(enabled); }
		static void enableBlend(bool enabled) { instance->enableBlendInternal(enabled); }
		static void enableDepthMask(bool enabled) { instance->enableDepthMaskInternal(enabled); }
		static void enableCullFace(bool enabled) { instance->enableCullFaceInternal(enabled); }
		static void enableDepthClamp(bool enabled) { instance->enableDepthClampInternal(enabled); }

		static void setViewport(uint x, uint y, uint width, uint height) {
			instance->setViewportInternal(x, y, width, height);
		}

		static void setBlendFunction(BlendFunction source, BlendFunction destination) {
			instance->setBlendFunctionInternal(source, destination);
		}

		static void setBlendEquation(BlendEquation equation) {
			instance->setBlendEquationInternal(equation);
		}

		static void setDepthFunction(DepthFunction function) {
			instance->setDepthFunctionInternal(function);
		}

		static void setCullFace(CullFace cullFace) {
			instance->setCullFaceInternal(cullFace);
		}

		static uint getDC() { return dc; }
		static uint resetDC() { dc = 0; }

	protected:
		virtual void initInternal() = 0;

		virtual void clearInternal(uint buffer) = 0;
		virtual void flushInternal() = 0;

		virtual void setClearColorInternal(const vec4 &color) = 0;

		virtual void enableVsyncInternal(bool enabled) = 0;

		virtual void enableDepthTestingInternal(bool enabled) = 0;
		virtual void enableBlendInternal(bool enabled) = 0;
		virtual void enableDepthMaskInternal(bool enabled) = 0;
		virtual void enableCullFaceInternal(bool enabled) = 0;
		virtual void enableDepthClampInternal(bool enabled) = 0;

		virtual void setViewportInternal(uint x, uint y, uint width, uint height) = 0;

		virtual void setBlendFunctionInternal(BlendFunction source, BlendFunction destination) = 0;
		virtual void setBlendEquationInternal(BlendEquation equation) = 0;
		virtual void setDepthFunctionInternal(DepthFunction function) = 0;
		virtual void setCullFaceInternal(CullFace cullFace) = 0;

	private:
		static Renderer *instance;
		static uint dc;
	};

}}


#endif //X808_RENDERER_HPP
