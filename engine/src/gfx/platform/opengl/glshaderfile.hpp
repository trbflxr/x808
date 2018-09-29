//
// Created by FLXR on 8/6/2018.
//

#ifndef X808_GLSHADERFILE_HPP
#define X808_GLSHADERFILE_HPP


#include <sstream>
#include <xe/resources/shaderfile.hpp>

namespace xe { namespace internal {

	class GLShaderFile : public ShaderFile {
	public:
		explicit GLShaderFile(ShaderType type, const string &source,
		                      const std::vector<string> &dependenciesSource,
		                      const std::vector<string> &extensions);

		explicit GLShaderFile(ShaderType type, const wstring &path,
		                      const std::vector<wstring> &dependencies,
		                      const std::vector<string> &extensions);

		inline ShaderType getType() const override { return type; }
		inline const string &getSource() const override { return source; }

		uint compile() override;

		void parse(ShaderUniformBufferVec &buffers,
		           ShaderSamplerVec &samplers,
		           ShaderStructVec &structs) override;

		void parseUniform(const string &statement,
		                  ShaderUniformBufferVec &buffers,
		                  ShaderSamplerVec &samplers,
		                  ShaderStructVec &structs) override;

		void parseUniformStruct(const string &block, ShaderStructVec &structs) override;

	protected:
		void setConstants(string &source) override;

	private:
		void appendConstants(std::stringstream &stream);
		void appendExtensions(std::stringstream &stream, const std::vector<string> &extensions);
		void appendDependencies(std::stringstream &stream, const std::vector<string> &dependencies);

	private:
		ShaderType type;

		string source;
		uint addedLines;
	};

}}


#endif //X808_GLSHADERFILE_HPP
