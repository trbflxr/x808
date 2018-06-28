//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_CONTEXT_HPP
#define X808_CONTEXT_HPP


#include "config.hpp"
#include "utils/singleton.hpp"

namespace xe { namespace gfx { namespace api {

	class XE_API Context : public utils::Singleton<Context> {
	public:
		static void create(void *deviceContext, bool vSync = false);

		void swapBuffers();

	protected:
		static Context *context;
	};

}}}


#endif //X808_CONTEXT_HPP
