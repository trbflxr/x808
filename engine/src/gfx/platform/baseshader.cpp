//
// Created by FLXR on 7/4/2018.
//

#include <xe/gfx/baseshader.hpp>
#include <xe/gfx/context.hpp>
#include <xe/utils/log.hpp>
#include <gfx/platform/opengl/glbaseshader.hpp>

namespace xe {

	BaseShader::BaseShader(const string &name, const std::vector<ShaderFile *> &shaderPipeline) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : {
				shader = new internal::GLBaseShader(name, shaderPipeline);
				break;
			}

			default: {
				XE_FATAL("[BaseShader]: selected render API is not supported");
				shader = nullptr;
				break;
			}
		}
	}

	BaseShader::~BaseShader() {
		delete shader;
	}

	void BaseShader::bind() const {
		shader->bind();
	}

	void BaseShader::unbind() const {
		shader->unbind();
	}

	void BaseShader::setUniformBuffer(byte *data, uint size, uint slot) {
		shader->setUniformBuffer(data, size, slot);
	}

	const ShaderUniformBufferVec &BaseShader::getUniforms() const {
		return shader->getUniforms();
	}

	const ShaderSamplerVec &BaseShader::getSamplers() const {
		return shader->getSamplers();
	}

	const string &BaseShader::getName() const {
		return shader->getName();
	}

}