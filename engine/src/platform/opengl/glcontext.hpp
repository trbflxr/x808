//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLCONTEXT_HPP
#define X808_GLCONTEXT_HPP


#include "gfx/api/context.hpp"

namespace xe { namespace gfx { namespace api {

	class XE_API GLContext : public Context {
	public:
		explicit GLContext(const WindowProperties &props, void *deviceContext);

		void swapBuffers();

		inline static GLContext *get() { return (GLContext *) context; }
	};

}}}


#endif //X808_GLCONTEXT_HPP
