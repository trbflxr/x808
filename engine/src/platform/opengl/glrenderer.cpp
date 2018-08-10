//
// Created by FLXR on 7/6/2018.
//

#include "glcommon.hpp"
#include "glrenderer.hpp"
#include "glenums.hpp"

namespace xe {

	GLRenderer::GLRenderer() {
		context = api::GLContext::get();
	}

	void GLRenderer::initInternal() {
		enableDepthTesting(true);
		enableBlend(true);
		setBlendFunction(BlendFunction::SourceAlpha, BlendFunction::OneMinusSourceAlpha);

		glCall(glEnable(GL_CULL_FACE));
		glCall(glFrontFace(GL_CCW));
		glCall(glCullFace(GL_BACK));
	}

	void GLRenderer::clearInternal(uint buffer) {
		glCall(glClear(api::rendererBufferToGL(buffer)));
	}

	void GLRenderer::flushInternal() {
		context->swapBuffers();
	}

	void GLRenderer::setClearColorInternal(const vec4 &color) {
		glCall(glClearColor(color.x, color.y, color.z, color.w));
	}

	void GLRenderer::enableVsyncInternal(bool enabled) {
		context->enableVsync(enabled);
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
		glCall(glBlendFunc(api::blendFunctionToGL(source), api::blendFunctionToGL(destination)));
	}

	void GLRenderer::setBlendEquationInternal(BlendEquation equation) {
		glCall(glBlendEquation(api::blendEquationToGL(equation)));
	}

	void GLRenderer::setDepthFunctionInternal(DepthFunction function) {
		glCall(glDepthFunc(api::depthFunctionToGL(function)));
	}
	void GLRenderer::setCullFaceInternal(CullFace cullFace) {
		glCall(glCullFace(api::cullFaceToGL(cullFace)));
	}

}
