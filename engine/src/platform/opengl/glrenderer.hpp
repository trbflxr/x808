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

		void enableDepthTestingInternal(bool enabled) override;
		void enableBlendInternal(bool enabled) override;
		void enableDepthMaskInternal(bool enabled) override;
		void enableCullFaceInternal(bool enabled) override;
		void enableDepthClampInternal(bool enabled) override;

		void setViewportInternal(uint x, uint y, uint width, uint height) override;

		void setBlendFunctionInternal(BlendFunction source, BlendFunction destination) override;
		void setBlendEquationInternal(BlendEquation equation) override;
		void setDepthFunctionInternal(DepthFunction function) override;
		void setCullFaceInternal(CullFace cullFace) override;

	private:
		api::GLContext *context;
	};

}}


#endif //X808_GLRENDERER_HPP
