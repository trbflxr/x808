//
// Created by FLXR on 8/11/2018.
//

#ifndef X808_SHADER_HPP
#define X808_SHADER_HPP


#include <unordered_map>
#include <xe/common.hpp>
#include <xe/resources/shaderfile.hpp>

namespace xe {

	namespace internal {
		class PlatformBaseShader;
	}

	struct UniformData {
		byte *buffer;
		uint size;

		UniformData() = default;
		explicit UniformData(uint size);
	};

	struct Uniform {
		const char *name;
		UniformData data;
		uint offset;

		Uniform() = default;
		explicit Uniform(const char *name, const UniformData &data, uint offset) :
				name(name), data(data), offset(offset) { }
	};

	class XE_API Shader {
	public:
		explicit Shader(const string &name, const std::vector<ShaderFile *> &shaderPipeline);
		virtual ~Shader();

		void setSourceConstant(ShaderType type, const string &valueName, const string &value) const;

		void updateUniforms() const;
		void setUniform(const string &name, const void *data, size_t size) const;

		uint getSampler(const string &name) const;

		void bind() const;
		void unbind() const;

		void setUniformBuffer(byte *data, uint size, uint slot) const;

		void bindUniformBlock(const char *blockName, uint location) const;

		const string &getName() const;
		uint getHandle() const;
		const ShaderSamplerVec &getSamplers() const;
		const ShaderUniformBufferVec &getUniforms() const;
		const std::unordered_map<ShaderType, string> &getSources() const;

	private:
		void init();

	protected:
		internal::PlatformBaseShader *base;

		std::vector<Uniform> uniforms;
		std::vector<UniformData> uniformData;
	};

}

#endif //X808_SHADER_HPP
