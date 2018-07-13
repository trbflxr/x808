//
// Created by FLXR on 7/6/2018.
//

#include "glcommon.hpp"
#include "glrenderer.hpp"

namespace xe { namespace gfx {

	uint rendererBufferToGL(uint buffer) {
		uint result = 0;

		if (buffer & RENDERER_BUFFER_COLOR) {
			result |= GL_COLOR_BUFFER_BIT;
		}
		if (buffer & RENDERER_BUFFER_DEPTH) {
			result |= GL_DEPTH_BUFFER_BIT;
		}
		if (buffer & RENDERER_BUFFER_STENCIL) {
			result |= GL_STENCIL_BUFFER_BIT;
		}
		return result;
	}

	uint rendererBlendFunctionToGL(BlendFunction function) {
		switch (function) {
			case BlendFunction::ZERO: return GL_ZERO;
			case BlendFunction::ONE: return GL_ONE;
			case BlendFunction::SOURCE_ALPHA: return GL_SRC_ALPHA;
			case BlendFunction::DESTINATION_ALPHA: return GL_DST_ALPHA;
			case BlendFunction::ONE_MINUS_SOURCE_ALPHA: return GL_ONE_MINUS_SRC_ALPHA;
			default:return 0;
		}
	}

	uint rendererDepthFunctionToGL(DepthFunction function) {
		switch (function) {
			case DepthFunction::EQUAL: return GL_EQUAL;
			case DepthFunction::LESS: return GL_LESS;
			default:return 0;
		}
	}

	uint rendererCullFaceToGL(CullFace cullFace) {
		switch (cullFace) {
			case CullFace::FRONT: return GL_FRONT;
			case CullFace::BACK: return GL_BACK;
			default:return 0;
		}
	}

	GLRenderer::GLRenderer() {
		context = api::GLContext::get();
	}

	void GLRenderer::initInternal() {
		enableDepthTesting(true);
		enableBlend(true);
		setBlendFunction(BlendFunction::SOURCE_ALPHA, BlendFunction::ONE_MINUS_SOURCE_ALPHA);

		glCall(glEnable(GL_CULL_FACE));
		glCall(glFrontFace(GL_CCW));
		glCall(glCullFace(GL_BACK));
	}

	void GLRenderer::clearInternal(uint buffer) {
		glCall(glClear(rendererBufferToGL(buffer)));
	}

	void GLRenderer::flushInternal() {
		context->swapBuffers();
	}

	void GLRenderer::enableDepthTestingInternal(bool enabled) {
		if (enabled) {
			glCall(glEnable(GL_DEPTH_TEST));
		} else {
			glCall(glDisable(GL_DEPTH_TEST));
		}
	}

	void GLRenderer::enableBlendInternal(bool enabled) {
		if (enabled) {
			glCall(glEnable(GL_BLEND));
		} else {
			glCall(glDisable(GL_BLEND));
		}
	}

	void GLRenderer::enableDepthMaskInternal(bool enabled) {
		if (enabled) {
			glCall(glDepthMask(GL_TRUE));
		} else {
			glCall(glDepthMask(GL_FALSE));
		}
	}

	void GLRenderer::enableCullFaceInternal(bool enabled) {
		if (enabled) {
			glCall(glEnable(GL_CULL_FACE));
		} else {
			glCall(glDisable(GL_CULL_FACE));
		}
	}

	void GLRenderer::enableDepthClampInternal(bool enabled) {
		if (enabled) {
			glCall(glEnable(GL_DEPTH_CLAMP));
		} else {
			glCall(glDisable(GL_DEPTH_CLAMP));
		}
	}

	void GLRenderer::setViewportInternal(uint x, uint y, uint width, uint height) {
		glCall(glViewport(x, y, width, height));
	}

	void GLRenderer::setBlendFunctionInternal(BlendFunction source, BlendFunction destination) {
		glCall(glBlendFunc(rendererBlendFunctionToGL(source), rendererBlendFunctionToGL(destination)));
	}

	void GLRenderer::setBlendEquationInternal(BlendEquation equation) {
		XE_ASSERT(false, "Not implemented");
	}

	void GLRenderer::setDepthFunctionInternal(DepthFunction function) {
		glCall(glDepthFunc(rendererDepthFunctionToGL(function)));
	}
	void GLRenderer::setCullFaceInternal(CullFace cullFace) {
		glCall(glCullFace(rendererCullFaceToGL(cullFace)));
	}

}}
