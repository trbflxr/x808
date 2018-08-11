//
// Created by FLXR on 7/4/2018.
//

#include "baseshader.hpp"
#include "context.hpp"
#include "utils/log.hpp"
#include "platform/opengl/glshader.hpp"

namespace xe { namespace api {

	BaseShader::BaseShader(const std::string_view &name) :
			name(name) { }

	BaseShader::~BaseShader() {
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

	BaseShader *BaseShader::create(const std::string_view &name,
	                       const std::vector<ShaderFile *> &shaderPipeline,
	                       void *address) {

		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL:
				return address ? new(address) GLShader(name, shaderPipeline) : new GLShader(name, shaderPipeline);

			default: return nullptr;
		}
	}

}}