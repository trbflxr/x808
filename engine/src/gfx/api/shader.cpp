//
// Created by FLXR on 7/4/2018.
//

#include "shader.hpp"
#include "context.hpp"
#include "utils/log.hpp"
#include "platform/opengl/glshader.hpp"

namespace xe { namespace api {

	Shader::Shader(const std::string_view &name) :
			name(name) { }

	Shader::~Shader() {
		for (auto &&s : structs) {
			delete s;
		}

		for (auto &&r : resources) {
			delete r;
		}

		for (auto &&u : uniformBuffers) {
			delete u;
		}
	}

	Shader *Shader::create(const std::string_view &name,
	                       const std::vector<ShaderFile *> &shaderPipeline,
	                       void *address) {

		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL:
				return address ? new(address) GLShader(name, shaderPipeline) : new GLShader(name, shaderPipeline);

			default: return nullptr;
		}
	}

}}