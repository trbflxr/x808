//
// Created by FLXR on 8/16/2018.
//

#ifndef X808_CONTEXT_HPP
#define X808_CONTEXT_HPP

#include <xe/xeint.hpp>
#include <xe/common.hpp>

namespace xe {

	struct GAPIInfo {
		char vendor[256];
		char renderer[256];
		char version[256];
		char shadingLevel[256];

		int32 maxTexSize;
		int32 maxTexUnits;
		int32 maxTexImgUnits;
	};

	class XE_API Context {
	public:
		static void create(void *deviceContext);

		static inline RenderAPI getRenderAPI() { return api; }
		static inline uint getRenderAPIVersion() { return apiVersion; };

		static inline void setRenderAPI(RenderAPI api, uint version) {
			Context::api = api;
			Context::apiVersion = version;
		}

		static GAPIInfo getInfo() { return context->getInfoInternal(); }

	protected:
		virtual uint getMaxTexUnits() const = 0;

		virtual GAPIInfo getInfoInternal() const = 0;

	protected:
		static Context *context;
		static RenderAPI api;
		static uint apiVersion;
	};

}


#endif //X808_CONTEXT_HPP
