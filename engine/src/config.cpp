//
// Created by FLXR on 6/28/2018.
//

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "config.hpp"

void writeKeyValue(xe::Config &config, const char *key, const char *value) {
	if (strcmp(key, "width") == 0) {
		config.width = (uint) atoi(value);
	} else if (strcmp(key, "height") == 0) {
		config.height = (uint) atoi(value);
	} else if (strcmp(key, "title") == 0) {
		strcpy(config.title, value);
	} else if (strcmp(key, "fullScreen") == 0) {
		config.fullScreen = (bool) atoi(value);
	} else if (strcmp(key, "vSync") == 0) {
		config.vSync = (bool) atoi(value);
	} else if (strcmp(key, "ups") == 0) {
		config.ups = (uint) atoi(value);
	}
}

bool xe::Config::load(xe::Config &config, const char *path) {
	FILE *cfgFile = fopen(path, "rb");

	if (!cfgFile) {
		fclose(cfgFile);
		return false;
	}

	char *key;
	char *value;
	const char *search = "=";

	char line[128];
	while (fgets(line, sizeof(line), cfgFile) != nullptr) {
		key = strtok(line, search);
		value = strtok(nullptr, search);

		writeKeyValue(config, key, value);
	}

	fclose(cfgFile);

	return true;
}