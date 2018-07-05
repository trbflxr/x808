//
// Created by FLXR on 7/6/2018.
//

#include "glcommon.hpp"
#include "glrenderer.hpp"

uint rendererBufferToGL(uint buffer) {
	uint result = 0;

	if (buffer & xe::gfx::RENDERER_BUFFER_COLOR) {
		result |= GL_COLOR_BUFFER_BIT;
	}
	if (buffer & xe::gfx::RENDERER_BUFFER_DEPTH) {
		result |= GL_DEPTH_BUFFER_BIT;
	}
	if (buffer & xe::gfx::RENDERER_BUFFER_STENCIL) {
		result |= GL_STENCIL_BUFFER_BIT;
	}
	return result;
}

uint rendererBlendFunctionToGL(xe::gfx::BlendFunction function) {
	switch (function) {
		case xe::gfx::BlendFunction::ZERO: return GL_ZERO;
		case xe::gfx::BlendFunction::ONE: return GL_ONE;
		case xe::gfx::BlendFunction::SOURCE_ALPHA: return GL_SRC_ALPHA;
		case xe::gfx::BlendFunction::DESTINATION_ALPHA: return GL_DST_ALPHA;
		case xe::gfx::BlendFunction::ONE_MINUS_SOURCE_ALPHA: return GL_ONE_MINUS_SRC_ALPHA;
		default:return 0;
	}
}

xe::gfx::GLRenderer::GLRenderer() {
	context = api::GLContext::get();
}

void xe::gfx::GLRenderer::initInternal() {
	setDepthTesting(true);
	setBlend(true);
	setBlendFunction(BlendFunction::SOURCE_ALPHA, BlendFunction::ONE_MINUS_SOURCE_ALPHA);

	glCall(glEnable(GL_CULL_FACE));
	glCall(glFrontFace(GL_CCW));
	glCall(glCullFace(GL_BACK));
}

void xe::gfx::GLRenderer::clearInternal(uint buffer) {
	glCall(glClear(rendererBufferToGL(buffer)));
}

void xe::gfx::GLRenderer::flushInternal() {
	context->swapBuffers();
}

void xe::gfx::GLRenderer::setDepthTestingInternal(bool enabled) {
	if (enabled) {
		glCall(glEnable(GL_DEPTH_TEST));
	} else {
		glCall(glDisable(GL_DEPTH_TEST));
	}
}

void xe::gfx::GLRenderer::setBlendInternal(bool enabled) {
	if (enabled) {
		glCall(glEnable(GL_BLEND));
	} else {
		glCall(glDisable(GL_BLEND));
	}
}

void xe::gfx::GLRenderer::setViewportInternal(uint x, uint y, uint width, uint height) {
	glCall(glViewport(x, y, width, height));
}

void xe::gfx::GLRenderer::setBlendFunctionInternal(BlendFunction source, BlendFunction destination) {
	glCall(glBlendFunc(rendererBlendFunctionToGL(source), rendererBlendFunctionToGL(destination)));
}

void xe::gfx::GLRenderer::setBlendEquationInternal(BlendEquation equation) {
	XE_ASSERT(false, "Not implemented");
}
