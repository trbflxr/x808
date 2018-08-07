//
// Created by FLXR on 8/6/2018.
//

#include <utility>
#include "shaderfile.hpp"
#include "gfx/api/context.hpp"
#include "utils/log.hpp"
#include "platform/opengl/gltypes.hpp"
#include "platform/opengl/glshaderfile.hpp"

namespace xe {

	ShaderFile::ShaderFile(bool fromSource, ShaderType type, const std::string_view &pathOrSource,
	                       const std::vector<std::string> &dependencies,
	                       const std::vector<std::string> &extensions) :
			createFromSource(fromSource),
			type(type),
			pathOrSource(pathOrSource),
			dependencies(dependencies),
			extensions(extensions) { }

	ShaderFile *ShaderFile::fromSource(ShaderType type, const std::string_view &source,
	                                   const std::vector<std::string> &dependenciesSource,
	                                   const std::vector<std::string> &extensions) {

		switch (api::Context::getRenderAPI()) {
			case api::RenderAPI::OPENGL :
				return new GLShaderFile(true, type, source, dependenciesSource, extensions);

			default: return nullptr;
		}
	}

	ShaderFile *ShaderFile::fromFile(ShaderType type, const std::string_view &path,
	                                 const std::vector<std::string> &dependencies,
	                                 const std::vector<std::string> &extensions) {

		switch (api::Context::getRenderAPI()) {
			case api::RenderAPI::OPENGL : return new GLShaderFile(false, type, path, dependencies, extensions);

			default: return nullptr;
		}
	}

	std::string ShaderFile::loadFromFile(const char *path) {
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

		std::string source(size, '\0');

		fread(&source[0], sizeof(char), size, file);

		fclose(file);

		return source;
	}

	uint ShaderFile::typeToGL(ShaderType type) {
		switch (type) {
			case ShaderType::UNDEFINED: return 0;
			case ShaderType::VERT: return GL_VERTEX_SHADER;
			case ShaderType::FRAG: return GL_FRAGMENT_SHADER;
			case ShaderType::GEOM: return GL_GEOMETRY_SHADER;
			case ShaderType::TESS_EVAL: return GL_TESS_EVALUATION_SHADER;
			case ShaderType::TESS_CONTROL: return GL_TESS_CONTROL_SHADER;
			case ShaderType::COMPUTE: return GL_COMPUTE_SHADER;
		}
	}

	uint ShaderFile::typeToDX(ShaderType type) {
		XE_ASSERT(false, "not implemented");
		return 0;
	}

	const char *ShaderFile::typeToString(ShaderType type) {
		switch (type) {
			case ShaderType::UNDEFINED: return "UNDEFINED";
			case ShaderType::VERT: return "VERT";
			case ShaderType::FRAG: return "FRAG";
			case ShaderType::GEOM: return "GEOM";
			case ShaderType::TESS_EVAL: return "TESS_EVAL";
			case ShaderType::TESS_CONTROL: return "TESS_CONTROL";
			case ShaderType::COMPUTE: return "COMPUTE";
		}
	}

}