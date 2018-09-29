//
// Created by FLXR on 8/6/2018.
//

#ifndef X808_SHADERFILE_HPP
#define X808_SHADERFILE_HPP


#include <vector>
#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/gfx/enums.hpp>
#include <xe/gfx/shaderuniform.hpp>
#include <xe/gfx/shadersampler.hpp>
#include <xe/utils/string.hpp>

namespace xe {

	class XE_API ShaderFile {
	public:
		virtual ~ShaderFile() = default;

		virtual ShaderType getType() const = 0;
		virtual const string &getSource() const = 0;

		virtual uint compile() = 0;

		virtual void parse(ShaderUniformBufferVec &buffers,
		                   ShaderSamplerVec &samplers,
		                   ShaderStructVec &structs) = 0;

		virtual void parseUniform(const string &statement,
		                          ShaderUniformBufferVec &buffers,
		                          ShaderSamplerVec &samplers,
		                          ShaderStructVec &structs) = 0;

		virtual void parseUniformStruct(const string &block, ShaderStructVec &structs) = 0;

		static ShaderFile *fromSource(ShaderType type, const string &source,
		                              const std::vector<string> &dependenciesSource = { },
		                              const std::vector<string> &extensions = { });

		static ShaderFile *fromFile(ShaderType type, const wstring &path,
		                            const std::vector<wstring> &dependencies = { },
		                            const std::vector<string> &extensions = { });

		static const char *typeToString(ShaderType type);

	protected:
		virtual void setConstants(string &source) { }
	};

}


#endif //X808_SHADERFILE_HPP
