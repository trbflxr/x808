//
// Created by FLXR on 8/6/2018.
//

#include <gfx/platform/opengl/glshaderfile.hpp>
#include <xe/gfx/context.hpp>
#include <xe/utils/log.hpp>
#include <xe/resources/shaderfile.hpp>

namespace xe {

	ShaderFile::ShaderFile(bool fromSource, ShaderType type, const string &pathOrSource,
	                       const std::vector<string> &dependencies,
	                       const std::vector<string> &extensions) :

			createFromSource(fromSource),
			type(type),
			pathOrSource(pathOrSource),
			dependencies(dependencies),
			extensions(extensions),
			addedLines(0) { }

	ShaderFile *ShaderFile::fromSource(ShaderType type, const string &source,
	                                   const std::vector<string> &dependenciesSource,
	                                   const std::vector<string> &extensions) {

		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL :
				return new internal::GLShaderFile(true, type, source, dependenciesSource, extensions);

			default: return nullptr;
		}
	}

	ShaderFile *ShaderFile::fromFile(ShaderType type, const string &path,
	                                 const std::vector<string> &dependencies,
	                                 const std::vector<string> &extensions) {

		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : return new internal::GLShaderFile(false, type, path, dependencies, extensions);

			default: return nullptr;
		}
	}

	string ShaderFile::loadFromFile(const char *path) {
		FILE *file = fopen(path, "rb");

		if (!file) {
			fclose(file);
			XE_FATAL("[ShaderFile]: file '", path, "' not found.");
			return "";
		}

		//get file size
		fseek(file, 0, SEEK_END);
		size_t size = static_cast<size_t>(ftell(file));
		fseek(file, 0, SEEK_SET);

		string source(size, '\0');

		fread(&source[0], sizeof(char), size, file);

		fclose(file);

		return source;
	}

	const char *ShaderFile::typeToString(ShaderType type) {
		switch (type) {
			case ShaderType::Vert: return "Vert";
			case ShaderType::Frag: return "Frag";
			case ShaderType::Geom: return "Geom";
			case ShaderType::TessEval: return "TessEval";
			case ShaderType::TessControl: return "TessControl";
			case ShaderType::Compute: return "Compute";
		}
		return "Invalid";
	}

}