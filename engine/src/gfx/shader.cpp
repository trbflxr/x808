//
// Created by FLXR on 8/11/2018.
//

#include <xe/gfx/shader.hpp>

#include "xe/gfx/shader.hpp"
#include "xe/resources/shadermanager.hpp"
#include "xe/utils/log.hpp"

namespace xe {

	Shader::Shader(BaseShader *shader, bool deleteBase) :
			shader(shader),
			deleteBase(deleteBase) {

		init();
	}

	Shader::Shader(const string &nameInShaderManager) :
			shader(GETSHADER(nameInShaderManager)),
			deleteBase(false) {

		init();
	}

	Shader::~Shader() {
		for (auto &&data : uniformData) {
			delete[] data.buffer;
		}

		if (deleteBase) {
			delete shader;
		}
	}

	void Shader::init() {
		const ShaderUniformBufferVec &shaderUniforms = shader->getUniforms();
		for (auto &&ub : shaderUniforms) {
			UniformData buffer(ub->getSize());
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

	void Shader::updateUniforms() const {
		for (uint i = 0; i < uniformData.size(); i++) {
			shader->setUniformBuffer(uniformData[i].buffer, uniformData[i].size, i);
		}
	}

	void Shader::setUniform(const string &name, const void *data, size_t size) {
		for (auto &&uniform : uniforms) {
			if (uniform.name == name) {
				memcpy(uniform.data.buffer + uniform.offset, data, size);
				return;
			}
		}

		XE_FATAL("[Shader]: Uniform '", name, "' not found!");
	}

	uint Shader::getSampler(const string &name) {
		for (auto &&resource : shader->getSamplers()) {
			if (resource->getName() == name) {
				return resource->getLocation();
			}
		}

		return 0;
	}

	void Shader::bindUniformBlock(const char *blockName, uint location) const {
		shader->bindUniformBlock(blockName, location);
	}

}