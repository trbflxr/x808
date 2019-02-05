//
// Created by FLXR on 8/11/2018.
//

#include <cstring>
#include <xe/gfx/context.hpp>
#include <gfx/platform/opengl/glbaseshader.hpp>
#include <xe/utils/logger.hpp>
#include <xe/resources/shadermanager.hpp>
#include <xe/gfx/shader.hpp>

namespace xe {

	UniformData::UniformData(uint size) : size(size) {
		buffer = new byte[size];
		memset(buffer, 0, size);
	}

	Shader::Shader(const string &name, const std::vector<ShaderFile *> &shaderPipeline) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OpenGL : {
				base = new internal::GLBaseShader(name, shaderPipeline);
				break;
			}

			default: {
				XE_CORE_FATAL("[BaseShader]: selected render API is not supported");
				base = nullptr;
				break;
			}
		}

		init();
	}

	Shader::~Shader() {
		for (auto &&data : uniformData) {
			delete[] data.buffer;
		}

		delete base;
	}

	void Shader::init() {
		const ShaderUniformBufferVec &shaderUniforms = base->getUniforms();
		for (const auto &ub : shaderUniforms) {
			const UniformData buffer(ub->getSize());
			uniformData.push_back(buffer);

			for (const auto &uniform: ub->getUniforms()) {
				uniforms.emplace_back(uniform->getName().c_str(), buffer, uniform->getOffset());
			}
		}
	}

	void Shader::bind() const {
		base->bind();
	}

	void Shader::unbind() const {
		base->unbind();
	}

	void Shader::updateUniforms() const {
		for (uint i = 0; i < uniformData.size(); i++) {
			base->setUniformBuffer(uniformData[i].buffer, uniformData[i].size, i);
		}
	}

	void Shader::setUniform(const string &name, const void *data, size_t size) const {
		for (auto &&uniform : uniforms) {
			if (uniform.name == name) {
				memcpy(uniform.data.buffer + uniform.offset, data, size);
				return;
			}
		}

		XE_CORE_FATAL("[Shader]: Uniform '", name,"' not found!");
	}

	uint Shader::getSampler(const string &name) const {
		for (auto &&s : base->getSamplers()) {
			if (s->getName() == name) {
				return s->getLocation();
			}
		}
		return 0;
	}

	void Shader::setUniformBuffer(byte *data, uint size, uint slot) const {
		base->setUniformBuffer(data, size, slot);
	}

	void Shader::bindUniformBlock(const char *blockName, uint location) const {
		base->bindUniformBlock(blockName, location);
	}

	const string &Shader::getName() const {
		return base->getName();
	}

	uint Shader::getHandle() const {
		return base->getHandle();
	}

	const ShaderSamplerVec &Shader::getSamplers() const {
		return base->getSamplers();
	}

	const ShaderUniformBufferVec &Shader::getUniforms() const {
		return base->getUniforms();
	}

	const std::unordered_map<string, string> &Shader::getSources() const {
		return base->getSources();
	}

}