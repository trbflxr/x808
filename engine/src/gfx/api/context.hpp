//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_CONTEXT_HPP
#define X808_CONTEXT_HPP


#include "config.hpp"

namespace xe { namespace gfx { namespace api {

	enum class RenderAPI {
		NONE, OPENGL, DIRECT3D
	};

	class XE_API Context {
	public:
		static void create(void *deviceContext);

		static RenderAPI getRenderAPI() { return api; }
		static void setRenderAPI(RenderAPI api) { Context::api = api; }

	protected:
		static Context *context;
		static RenderAPI api;
	};

}}}


#endif //X808_CONTEXT_HPP
