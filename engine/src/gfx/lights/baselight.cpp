//
// Created by FLXR on 7/13/2018.
//

#include "baselight.hpp"

namespace xe { namespace gfx {

	BaseLight::BaseLight(api::Shader *shader) :
			shader(shader) {

		const api::ShaderUniformBufferVec &vssu = shader->getVSSystemUniforms();

		for (auto &&ub : vssu) {
			api::UniformBuffer buffer(new byte[ub->getSize()], ub->getSize());
			uniformBuffers.push_back(buffer);

			for (auto &&uniform: ub->getUniforms()) {
				uniforms.emplace_back(buffer, uniform->getOffset());
			}
		}
	}

	BaseLight::~BaseLight() {
		delete shader;
	}

	void BaseLight::bindAndSetUniforms() {
		shader->bind();

		for (uint i = 0; i < uniformBuffers.size(); i++) {
			shader->setVSSystemUniformBuffer(uniformBuffers[i].buffer, uniformBuffers[i].size, i);
		}
	}

	void BaseLight::setUniform(uint index, const void *data, size_t size) {
		memcpy(uniforms[index].buffer.buffer + uniforms[index].offset, data, size);
	}

}}