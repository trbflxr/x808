//
// Created by FLXR on 7/4/2018.
//

#include "shader.hpp"
#include "context.hpp"
#include "utils/log.hpp"
#include "platform/opengl/glshader.hpp"

namespace xe { namespace api {

	Shader *Shader::createFromFile(const std::string_view &name, const std::string_view &path, void *address) {
		//todo: implement
		XE_ASSERT(false, "not implemented");

		switch (Context::getRenderAPI()) {
//		case RenderAPI::OPENGL: {
//			GLShader *result = address ? new(address) GLShader(name, source) : new GLShader(name, source);
//			result->file = path;
//			return result;
//		}
			default: return nullptr;
		}

	}

	Shader *Shader::createFromSource(const std::string_view &name, const std::string &source, void *address) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL:
				return address ? new(address) GLShader(name, source) : new GLShader(name, source);

			default: return nullptr;
		}
	}

	bool Shader::tryCompile(const std::string &source, std::string &error) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL: return GLShader::tryCompile(source, error);

			default: return false;
		}
	}

	bool Shader::tryCompileFromFile(const std::string &file, std::string &error) {
		//todo: implement
		XE_ASSERT(false, "not implemented");
	}

}}