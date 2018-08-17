//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_RENDERER_HPP
#define X808_RENDERER_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/gfx/color.hpp>
#include <xe/gfx/enums.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

	class XE_API Renderer {
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

		static void setPolygonMode(MaterialFace face, PolygonMode mode) {
			instance->setPolygonModeInternal(face, mode);
		}

		static uint getDC() { return dc; }
		static uint resetDC() { dc = 0; }
		static uint incDC() { ++dc; }

	protected:
		Renderer() = default;

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
		virtual void setPolygonModeInternal(MaterialFace face, PolygonMode mode) = 0;

	private:
		static Renderer *instance;
		static uint dc;
	};

}


#endif //X808_RENDERER_HPP
