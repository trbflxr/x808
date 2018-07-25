//
// Created by FLXR on 7/25/2018.
//

#include "forwardrenderershader.hpp"

namespace xe { namespace gfx {

	ForwardRendererShader::ForwardRendererShader(api::Shader *shader) :
			shader(shader),
			diffuse(nullptr),
			normalMap(nullptr),
			dispMap(nullptr) {

		init();
	}

	ForwardRendererShader::~ForwardRendererShader() {
		delete shader;
	}

	void ForwardRendererShader::init() {
		const api::ShaderUniformBufferVec &vssu = shader->getVSUniforms();
		for (auto &&ub : vssu) {
			api::UniformBuffer buffer(new byte[ub->getSize()], ub->getSize());
			vsUniformBuffers.push_back(buffer);

			for (auto &&uniform: ub->getUniforms()) {
				vsUniforms.emplace_back(uniform->getName().c_str(), buffer, uniform->getOffset());
			}
		}

		const api::ShaderUniformBufferVec &fssu = shader->getFSUniforms();
		for (auto &&ub : fssu) {
			api::UniformBuffer buffer(new byte[ub->getSize()], ub->getSize());
			fsUniformBuffers.push_back(buffer);

			for (auto &&uniform: ub->getUniforms()) {
				fsUniforms.emplace_back(uniform->getName().c_str(), buffer, uniform->getOffset());
			}
		}
	}

	void ForwardRendererShader::bind() const {
		shader->bind();
	}

	void ForwardRendererShader::unbind() const {
		unbindSamplers();
		shader->unbind();
	}

	void ForwardRendererShader::updateUniforms() {
		for (uint i = 0; i < vsUniformBuffers.size(); i++) {
			shader->setVSUniformBuffer(vsUniformBuffers[i].buffer, vsUniformBuffers[i].size, i);
		}

		for (uint i = 0; i < fsUniformBuffers.size(); i++) {
			shader->setFSUniformBuffer(fsUniformBuffers[i].buffer, fsUniformBuffers[i].size, i);
		}
	}

	void ForwardRendererShader::setUniforms(const Material *material, const Transform &transform,
	                                        const Camera *camera) {
		mat4 world = transform.toMatrix();
		mat4 mvp = camera->getProjectionMatrix() * camera->getViewMatrix() * world;

		setUniform("sys_MVP", &mvp.elements, sizeof(mat4), api::Shader::VERT);
		setUniform("sys_Model", &world.elements, sizeof(mat4), api::Shader::VERT);
		setUniform("sys_EyePos", &camera->getPosition(), sizeof(vec3), api::Shader::FRAG);

		float specularPower = material->getSpecularIntensity();
		float specularIntensity = material->getSpecularPower();
		float dispScale = material->getDispMapScale();
		float dispBias = material->getDispMapBias();
		setUniform("sys_SpecularIntensity", &specularIntensity, sizeof(float), api::Shader::FRAG);
		setUniform("sys_SpecularPower", &specularPower, sizeof(float), api::Shader::FRAG);
		setUniform("sys_DispMapScale", &dispScale, sizeof(float), api::Shader::FRAG);
		setUniform("sys_DispMapBias", &dispBias, sizeof(float), api::Shader::FRAG);

		setUserUniforms();

		bindSamplers(material);
	}

	void ForwardRendererShader::setUniform(const char *name, const void *data, size_t size, uint shaderType) {
		switch (shaderType) {

			case api::Shader::UNDEFINED:

			case api::Shader::VERT: {
				for (auto &&uniform : vsUniforms) {
					if (strcmp(uniform.name, name) == 0) {
						memcpy(uniform.buffer.buffer + uniform.offset, data, size);
						return;
					}
				}
			}

			case api::Shader::FRAG: {
				for (auto &&uniform : fsUniforms) {
					if (strcmp(uniform.name, name) == 0) {
						memcpy(uniform.buffer.buffer + uniform.offset, data, size);
						return;
					}
				}
			}

			default: break;
		}

//		XE_FATAL("[ForwardRendererShader]: Uniform '", name, "' not found!");
	}

	void ForwardRendererShader::bindSamplers(const Material *material) {
		for (auto &&sampler : shader->getResources()) {
			if (sampler->getName() == "diffuse") {
				diffuse = material->getTexture();
				diffuse->bind(sampler->getRegister());
			}

			if (sampler->getName() == "normalMap") {
				normalMap = material->getNormalMap();
				normalMap->bind(sampler->getRegister());
			}

			if (sampler->getName() == "dispMap") {
				dispMap = material->getDispMap();
				dispMap->bind(sampler->getRegister());
			}
		}
	}

	void ForwardRendererShader::unbindSamplers() const {
		for (auto &&sampler : shader->getResources()) {
			if (sampler->getName() == "diffuse") {
				diffuse->unbind(sampler->getRegister());
			}

			if (sampler->getName() == "normalMap") {
				normalMap->unbind(sampler->getRegister());
			}

			if (sampler->getName() == "dispMap") {
				dispMap->unbind(sampler->getRegister());
			}
		}
	}

	uint ForwardRendererShader::getSamplerLocation(const char *name) {
		for (auto &&sampler : shader->getResources()) {
			if (sampler->getName() == name) {
				return sampler->getRegister();
			}
		}
		return 0;
	}

}}