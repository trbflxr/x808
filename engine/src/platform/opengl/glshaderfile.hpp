//
// Created by FLXR on 8/6/2018.
//

#ifndef X808_GLSHADERFILE_HPP
#define X808_GLSHADERFILE_HPP


#include "resources/shaderfile.hpp"

namespace xe {

	class GLShaderFile : public ShaderFile {
	public:
		explicit GLShaderFile(bool fromSource, ShaderType type, const std::string_view &pathOrSource,
		                      const std::vector<std::string> &dependencies,
		                      const std::vector<std::string> &extensions);

		uint compile() override;

		void parse(api::ShaderUniformBufferVec &buffers,
		           api::ShaderResourceVec &resources,
		           api::ShaderStructVec &structs) override;

		void parseUniform(const std::string &statement,
		                  api::ShaderUniformBufferVec &buffers,
		                  api::ShaderResourceVec &resources,
		                  api::ShaderStructVec &structs) override;

		void parseUniformStruct(const std::string &block, api::ShaderStructVec &structs) override;

	private:
		bool isTypeStringResource(const std::string &type);
	};

}


#endif //X808_GLSHADERFILE_HPP
