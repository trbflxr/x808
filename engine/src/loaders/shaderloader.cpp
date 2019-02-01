//
// Created by FLXR on 9/29/2018.
//

#include <xe/utils/log.hpp>
#include <xe/loaders/shaderloader.hpp>

namespace xe {

	string ShaderLoader::load(const string &path) {
		return load(path.c_str());
	}

	string ShaderLoader::load(const char *path) {
		FILE *file = fopen(path, "rb");

		if (!file) {
			fclose(file);
			XE_FATAL("[ShaderFile]: file '", path, "' not found.");
			return "";
		}

		//get file size
		fseek(file, 0, SEEK_END);
		const size_t size = static_cast<size_t>(ftell(file));
		fseek(file, 0, SEEK_SET);

		string source(size, '\0');

		fread(&source[0], size, 1, file);

		fclose(file);

		return source;
	}

}
