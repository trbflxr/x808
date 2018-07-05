//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLRENDERER_HPP
#define X808_GLRENDERER_HPP


#include "gfx/renderer.hpp"
#include "glcontext.hpp"

namespace xe { namespace gfx {

	class XE_API GLRenderer : public Renderer {
	public:
		explicit GLRenderer();

	protected:
		void initInternal() override;

		void clearInternal(uint buffer) override;
		void flushInternal() override;

		void setDepthTestingInternal(bool enabled) override;
		void setBlendInternal(bool enabled) override;

		void setViewportInternal(uint x, uint y, uint width, uint height) override;

		void setBlendFunctionInternal(BlendFunction source, BlendFunction destination) override;
		void setBlendEquationInternal(BlendEquation equation) override;

	private:
		api::GLContext *context;
	};

}}


#endif //X808_GLRENDERER_HPP
