//
// Created by FLXR on 8/11/2018.
//

#include "shader.hpp"
#include "resources/shadermanager.hpp"
#include "utils/log.hpp"

namespace xe {

	Shader::Shader(api::BaseShader *shader) :
			shader(shader) {

		init();
	}

	Shader::Shader(const std::string_view &nameInShaderManager) :
			shader(GETSHADER(nameInShaderManager)) {

		init();
	}

	Shader::~Shader() {
		for (auto &&data : uniformData) {
			delete[] data.buffer;
		}
		uniformData.clear();
		uniforms.clear();
	}

	void Shader::init() {
		const api::ShaderUniformBufferVec &shaderUniforms = shader->getUniforms();
		for (auto &&ub : shaderUniforms) {
			api::UniformData buffer(ub->getSize());
			uniformData.push_back(buffer);

			for (auto &&uniform: ub->getUniforms()) {
				uniforms.emplace_back(uniform->getName().c_str(), buffer, uniform->getOffset());
			}
		}
	}

	void Shader::bind() const {
		shader->bind();
	}

	void Shader::unbind() const {
		shader->unbind();
	}

	void Shader::updateUniforms() {
		for (uint i = 0; i < uniformData.size(); i++) {
			shader->setUniformBuffer(uniformData[i].buffer, uniformData[i].size, i);
		}
	}

	void Shader::setUniform(const std::string_view &name, const void *data, size_t size) {
		for (auto &&uniform : uniforms) {
			if (uniform.name == name) {
				memcpy(uniform.data.buffer + uniform.offset, data, size);
				return;
			}
		}

		XE_FATAL("[Shader]: Uniform '", name, "' not found!");
	}

	uint Shader::getResource(const std::string_view &name) {
		for (auto &&resource : shader->getResources()) {
			if (resource->getName() == name) {
				return resource->getRegister();
			}
		}

		return 0;
	}

}