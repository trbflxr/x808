//
// Created by FLXR on 8/6/2018.
//

#ifndef X808_SHADERFILE_HPP
#define X808_SHADERFILE_HPP


#include <vector>
#include <string>
#include "xeint.hpp"
#include "common.hpp"
#include "gfx/api/shaderuniform.hpp"
#include "gfx/api/shaderresource.hpp"

namespace xe {

	enum class ShaderType {
		UNDEFINED = 0, VERT, FRAG, GEOM, TESS_EVAL, TESS_CONTROL, COMPUTE
	};

	class XE_API ShaderFile {
	public:
		friend class GLShader;

	public:
		inline ShaderType getType() const { return type; }
		inline const std::string &getPathOrSource() const { return pathOrSource; }
		inline const std::vector<std::string> &getDependencies() const { return dependencies; }
		inline const std::vector<std::string> &getExtensions() const { return extensions; }

		virtual uint compile() = 0;

		virtual void parse(api::ShaderUniformBufferVec &buffers,
		                   api::ShaderResourceVec &resources,
		                   api::ShaderStructVec &structs) = 0;

		virtual void parseUniform(const std::string &statement,
		                          api::ShaderUniformBufferVec &buffers,
		                          api::ShaderResourceVec &resources,
		                          api::ShaderStructVec &structs) = 0;

		virtual void parseUniformStruct(const std::string &block, api::ShaderStructVec &structs) = 0;

		static ShaderFile *fromSource(ShaderType type, const std::string_view &source,
		                              const std::vector<std::string> &dependenciesSource,
		                              const std::vector<std::string> &extensions = { });

		static ShaderFile *fromFile(ShaderType type, const std::string_view &path,
		                            const std::vector<std::string> &dependencies,
		                            const std::vector<std::string> &extensions = { });

		static uint typeToGL(ShaderType type);
		static uint typeToDX(ShaderType type);
		static const char *typeToString(ShaderType type);

	protected:
		explicit ShaderFile(bool fromSource, ShaderType type, const std::string_view &pathOrSource,
		                    const std::vector<std::string> &dependencies,
		                    const std::vector<std::string> &extensions);

		std::string loadFromFile(const char *path);

	protected:
		bool createFromSource;

		ShaderType type;

		std::string pathOrSource;
		std::vector<std::string> dependencies;
		std::vector<std::string> extensions;

		std::string fullSource;
	};

}


#endif //X808_SHADERFILE_HPP
