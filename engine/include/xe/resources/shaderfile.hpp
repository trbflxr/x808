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

		inline ShaderType getType() const { return type; }
		inline const string &getPathOrSource() const { return pathOrSource; }
		inline const string &getFullSource() const { return fullSource; }
		inline const std::vector<string> &getDependencies() const { return dependencies; }
		inline const std::vector<string> &getExtensions() const { return extensions; }

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

		static ShaderFile *fromFile(ShaderType type, const string &path,
		                            const std::vector<string> &dependencies = { },
		                            const std::vector<string> &extensions = { });

		static const char *typeToString(ShaderType type);

	protected:
		explicit ShaderFile(bool fromSource, ShaderType type, const string &pathOrSource,
		                    const std::vector<string> &dependencies,
		                    const std::vector<string> &extensions);

		string loadFromFile(const char *path);

		virtual void setConstants(string &source) { }

	protected:
		bool createFromSource;

		ShaderType type;

		string pathOrSource;
		std::vector<string> dependencies;
		std::vector<string> extensions;

		string fullSource;

		uint addedLines;
	};

}


#endif //X808_SHADERFILE_HPP
