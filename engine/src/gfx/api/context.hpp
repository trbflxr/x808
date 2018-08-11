//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_CONTEXT_HPP
#define X808_CONTEXT_HPP


#include "xeint.hpp"
#include "common.hpp"

namespace xe { namespace api {

	enum class RenderAPI {
		NONE, OPENGL, DIRECT3D
	};

	class XE_API Context {
	public:
		static void create(void *deviceContext);

		static RenderAPI getRenderAPI() { return api; }
		static uint getRenderAPIVersion() { return apiVersion; };

		static void setRenderAPI(RenderAPI api, uint version) {
			Context::api = api;
			Context::apiVersion = version;
		}

	protected:
		static Context *context;
		static RenderAPI api;
		static uint apiVersion;
	};

}}


#endif //X808_CONTEXT_HPP
