//
// Created by FLXR on 8/6/2018.
//

#ifndef X808_GLSHADERFILE_HPP
#define X808_GLSHADERFILE_HPP


#include <xe/resources/shaderfile.hpp>

namespace xe { namespace internal {

	class GLShaderFile : public ShaderFile {
	public:
		explicit GLShaderFile(bool fromSource, ShaderType type, const string &pathOrSource,
		                      const std::vector<string> &dependencies,
		                      const std::vector<string> &extensions);

		~GLShaderFile() override = default;

		uint compile() override;

		void parse(ShaderUniformBufferVec &buffers,
		           ShaderSamplerVec &samplers,
		           ShaderStructVec &structs) override;

		void parseUniform(const string &statement,
		                  ShaderUniformBufferVec &buffers,
		                  ShaderSamplerVec &samplers,
		                  ShaderStructVec &structs) override;

		void parseUniformStruct(const string &block, ShaderStructVec &structs) override;
	};

}}


#endif //X808_GLSHADERFILE_HPP
