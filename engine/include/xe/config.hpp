//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_CONFIG_HPP
#define X808_CONFIG_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>

namespace xe {

	struct Config {
		uint width;
		uint height;
		bool fullScreen;
		bool vSync;

		uint ups;
		uint fps;

		bool useSRGB;

		RenderAPI renderApi;
		uint apiVersion;
		uint maxTextureUnits;

		uint maxPointLights2D;
	};

	extern Config gConfig;

}


#endif //X808_CONFIG_HPP
