//
// Created by FLXR on 8/16/2018.
//

#ifndef X808_CONTEXT_HPP
#define X808_CONTEXT_HPP

#include <xe/xeint.hpp>
#include <xe/common.hpp>

namespace xe {

	class XE_API Context {
	public:
		static void create(void *deviceContext);

		static inline RenderAPI getRenderAPI() { return api; }
		static inline uint getRenderAPIVersion() { return apiVersion; };

		static inline void setRenderAPI(RenderAPI api, uint version) {
			Context::api = api;
			Context::apiVersion = version;
		}

		static inline uint getMaxTextureUnits() { return maxTextureUnits; }
		static void setMaxTextureUnits(uint size);

	protected:
		virtual uint getMaxTexUnits() = 0;

	protected:
		static Context *context;
		static RenderAPI api;
		static uint apiVersion;

		static uint maxTextureUnits;
	};

}


#endif //X808_CONTEXT_HPP
