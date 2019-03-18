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
#include <xe/gfx/shaderconstant.hpp>
#include <xe/string.hpp>

namespace xe {

	class XE_API ShaderFile {
	public:
		virtual ~ShaderFile() = default;

		virtual ShaderType getType() const = 0;
		virtual const string &getSource() const = 0;

		static void parseConstants(const string &source, ShaderConstantVec &constants);

		static ShaderFile *fromPreparedSource(ShaderType type, const string &source);

		static ShaderFile *fromSource(ShaderType type, const string &source,
		                              const std::vector<string> &dependenciesSource = { },
		                              const std::vector<string> &extensions = { });

		static ShaderFile *fromFile(ShaderType type, const string &path,
		                            const std::vector<string> &dependencies = { },
		                            const std::vector<string> &extensions = { });

		static const char *typeToString(ShaderType type);
	};

}


#endif //X808_SHADERFILE_HPP
