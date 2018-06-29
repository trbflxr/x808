//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_RENDERER_HPP
#define X808_RENDERER_HPP


#include "common.hpp"
#include "xeint.hpp"
#include "utils/singleton.hpp"
#include "api/context.hpp"

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

	class XE_API Renderer : public utils::Singleton<Renderer> {
	public:
		void init();

		void clear(uint buffer);
		void flush();

		void setDepthTesting(bool enabled);
		void setBlend(bool enabled);

		void setViewport(uint x, uint y, uint width, uint height);

		void setBlendFunction(BlendFunction source, BlendFunction destination);
		void setBlendEquation(BlendEquation equation);

	private:
		api::Context *context;
	};

}}


#endif //X808_RENDERER_HPP
