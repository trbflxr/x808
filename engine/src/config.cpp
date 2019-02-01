//
// Created by FLXR on 6/28/2018.
//

#include <cstring>
#include <cstdlib>
//#include <cstdio>
#include <xe/core/filesystem.hpp>
#include <xe/config.hpp>

namespace xe {

	Config gConfig;

	void writeKeyValue(Config &config, const char *key, const char *value) {
		if (strcmp(key, "width") == 0) {
			config.width = (uint) atoi(value);
		} else if (strcmp(key, "height") == 0) {
			config.height = (uint) atoi(value);
		} else if (strcmp(key, "fullScreen") == 0) {
			config.fullScreen = (bool) atoi(value);
		} else if (strcmp(key, "vSync") == 0) {
			config.vSync = (bool) atoi(value);
		} else if (strcmp(key, "ups") == 0) {
			config.ups = (uint) atoi(value);
		} else if (strcmp(key, "fps") == 0) {
			config.fps = (uint) atoi(value);
		} else if (strcmp(key, "srgb") == 0) {
			config.useSRGB = (bool) atoi(value);
		} else if (strcmp(key, "renderApi") == 0) {
			config.renderApi = stringToRenderApi(value);
		} else if (strcmp(key, "apiVersion") == 0) {
			config.apiVersion = (uint) atoi(value);
		} else if (strcmp(key, "maxTextureUnits") == 0) {
			config.maxTextureUnits = (uint) atoi(value);
		}
	}

	bool Config::load(Config &config, const char *path) {
		int64 size = FileSystem::size(path);
		if (size == -1) return false;

		string cfg(size, '\0');

		bool r = FileSystem::read(path, &cfg[0], size);
		if (!r) return false;

		std::vector<string> lines = splitString(cfg, "\n\r");

		const char *search = "=";
		for (auto &&l : lines) {
			char *key = strtok(&l[0], search);
			char *value = strtok(nullptr, search);

			writeKeyValue(config, key, value);
		}

		gConfig = config;

		return true;
	}

}