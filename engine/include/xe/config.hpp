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

		bool srgb;

		RenderAPI renderApi;
		uint apiVersion;

		uint maxSpotShadows;
		uint maxPointShadows;

		Config() :
				width(1),
				height(1),
				fullScreen(false),
				vSync(false),
				ups(0),
				fps(0),
				srgb(true),
				renderApi(RenderAPI::OpenGL),
				apiVersion(330),
				maxSpotShadows(1),
				maxPointShadows(1) { }

		static const Config &get() {
			static Config cfg;
			return cfg;
		}
	};

}


#endif //X808_CONFIG_HPP
