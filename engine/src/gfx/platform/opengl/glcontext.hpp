//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLCONTEXT_HPP
#define X808_GLCONTEXT_HPP


#include <xe/gfx/context.hpp>

namespace xe { namespace internal {

	class GLContext : public Context {
	public:
		explicit GLContext(void *deviceContext);

		void swapBuffers();

		void enableVsync(bool enabled);

		inline static GLContext *get() { return (GLContext *) context; }
	};

}}


#endif //X808_GLCONTEXT_HPP
