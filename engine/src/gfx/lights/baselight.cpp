//
// Created by FLXR on 7/13/2018.
//

#include "baselight.hpp"
#include "utils/log.hpp"

namespace xe { namespace gfx {

	BaseLight::BaseLight(api::Shader *shader, float intensity, uint color) :
			shader(shader),
			intensity(intensity),
			color(color) {

		const api::ShaderUniformBufferVec &vssu = shader->getVSSystemUniforms();

		for (auto &&ub : vssu) {
			api::UniformBuffer buffer(new byte[ub->getSize()], ub->getSize());
			vsUniformBuffers.push_back(buffer);

			for (auto &&uniform: ub->getUniforms()) {
				vsUniforms.emplace_back(uniform->getName().c_str(), buffer, uniform->getOffset());
			}
		}

		const api::ShaderUniformBufferVec &fssu = shader->getFSSystemUniforms();

		for (auto &&ub : fssu) {
			api::UniformBuffer buffer(new byte[ub->getSize()], ub->getSize());
			fsUniformBuffers.push_back(buffer);

			for (auto &&uniform: ub->getUniforms()) {
				fsUniforms.emplace_back(uniform->getName().c_str(), buffer, uniform->getOffset());
			}
		}
	}

	BaseLight::~BaseLight() {
		delete shader;
	}

	void BaseLight::updateUniforms() {

		for (uint i = 0; i < vsUniformBuffers.size(); i++) {
			shader->setVSSystemUniformBuffer(vsUniformBuffers[i].buffer, vsUniformBuffers[i].size, i);
		}

		for (uint i = 0; i < fsUniformBuffers.size(); i++) {
			shader->setFSSystemUniformBuffer(fsUniformBuffers[i].buffer, fsUniformBuffers[i].size, i);
		}
	}

	void BaseLight::setUniform(const char *name, const void *data, size_t size, api::ShaderType shader) {
		switch (shader) {
			case api::ShaderType::NONE:

			case api::ShaderType::VERT: {
				for (auto &&uniform :  vsUniforms) {
					if (strcmp(uniform.name, name) == 0) {
						memcpy(uniform.buffer.buffer + uniform.offset, data, size);
						return;
					}
				}
			}

			case api::ShaderType::FRAG: {
				for (auto &&uniform :  fsUniforms) {
					if (strcmp(uniform.name, name) == 0) {
						memcpy(uniform.buffer.buffer + uniform.offset, data, size);
						return;
					}
				}
			}
		}

		XE_FATAL("[BaseLight]: Uniform '", name, "' not found!");
	}

	void BaseLight::setColor(uint color) {
		BaseLight::color = color;
		setUniformsInternal();
	}

	void BaseLight::setIntensity(float intensity) {
		BaseLight::intensity = intensity;
		setUniformsInternal();
	}

}}