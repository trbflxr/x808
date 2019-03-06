//
// Created by FLXR on 8/6/2018.
//

#include <gfx/platform/opengl/glshaderfile.hpp>
#include <xe/gfx/context.hpp>
#include <xe/utils/logger.hpp>
#include <xe/resources/shaderfile.hpp>

namespace xe {

	ShaderFile *ShaderFile::fromPreparedSource(ShaderType type, const string &source) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OpenGL :
				return new internal::GLShaderFile(type, source);

			default: return nullptr;
		}
	}

	ShaderFile *ShaderFile::fromSource(ShaderType type, const string &source,
	                                   const std::vector<string> &dependenciesSource,
	                                   const std::vector<string> &extensions) {

		switch (Context::getRenderAPI()) {
			case RenderAPI::OpenGL :
				return new internal::GLShaderFile(type, source, dependenciesSource, extensions);

			default: return nullptr;
		}
	}

	ShaderFile *ShaderFile::fromFile(ShaderType type, const string &path,
	                                 const std::vector<string> &dependencies,
	                                 const std::vector<string> &extensions) {

		switch (Context::getRenderAPI()) {
			case RenderAPI::OpenGL : return new internal::GLShaderFile(type, path, dependencies, extensions, false);

			default: return nullptr;
		}
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