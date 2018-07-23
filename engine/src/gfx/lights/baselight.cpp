//
// Created by FLXR on 7/13/2018.
//

#include "baselight.hpp"
#include "utils/log.hpp"

namespace xe { namespace gfx {

	BaseLight::BaseLight(api::Shader *shader, float intensity, uint color) :
			shader(shader),
			enabled(true) {

		baseLight.color = color::decode(color);
		baseLight.intensity = intensity;

		init();
	}

	BaseLight::~BaseLight() {
		delete shader;
	}

	void BaseLight::init() {
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

	void BaseLight::updateUniforms() {
		for (uint i = 0; i < vsUniformBuffers.size(); i++) {
			shader->setVSSystemUniformBuffer(vsUniformBuffers[i].buffer, vsUniformBuffers[i].size, i);
		}

		for (uint i = 0; i < fsUniformBuffers.size(); i++) {
			shader->setFSSystemUniformBuffer(fsUniformBuffers[i].buffer, fsUniformBuffers[i].size, i);
		}
	}

	void BaseLight::setUniforms(const Model *model, const Camera *camera) {
		mat4 world = model->transform.toMatrix();
		mat4 mvp = camera->getProjectionMatrix() * camera->getViewMatrix() * world;

		setUniform("sys_MVP", &mvp.elements, sizeof(mat4), api::ShaderType::VERT);
		setUniform("sys_Model", &world.elements, sizeof(mat4), api::ShaderType::VERT);

		float specularPower = model->material->getSpecularIntensity();
		float specularIntensity = model->material->getSpecularPower();
		float dispScale = model->material->getDispMapScale();
		float dispBias = model->material->getDispMapBias();
		setUniform("sys_SpecularIntensity", &specularIntensity, sizeof(float), api::ShaderType::FRAG);
		setUniform("sys_SpecularPower", &specularPower, sizeof(float), api::ShaderType::FRAG);
		setUniform("sys_DispMapScale", &dispScale, sizeof(float), api::ShaderType::FRAG);
		setUniform("sys_DispMapBias", &dispBias, sizeof(float), api::ShaderType::FRAG);
		setUniform("sys_EyePos", &camera->getPosition(), sizeof(vec3), api::ShaderType::FRAG);
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
		baseLight.color = color::decode(color);
		setUniformsInternal();
	}

	void BaseLight::setIntensity(float intensity) {
		baseLight.intensity = intensity;
		setUniformsInternal();
	}

}}