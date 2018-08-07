//
// Created by FLXR on 8/6/2018.
//

#include <sstream>
#include "glshaderfile.hpp"
#include "glcommon.hpp"
#include "utils/string.hpp"
#include "glshaderuniform.hpp"
#include "glshaderresource.hpp"

namespace xe {

	GLShaderFile::GLShaderFile(bool fromSource, ShaderType type, const std::string_view &pathOrSource,
	                           const std::vector<std::string> &dependencies,
	                           const std::vector<std::string> &extensions) :
			ShaderFile(fromSource, type, pathOrSource, dependencies, extensions) { }

	uint GLShaderFile::compile(uint version) {
		std::stringstream shaderSource;
		std::stringstream shaderAdditions;
		std::stringstream shaderExtensions;

		//constants
		const char *MATH_PI = "#define MATH_PI 3.1415926535897932384626433832795";
		const char *MATH_HALF_PI = "#define MATH_HALF_PI 1.57079632679489661923132169163975";
		const char *MATH_2_PI = "#define MATH_2_PI 6.283185307179586476925286766559";

		//extensions
		if (!extensions.empty()) {
			for (auto &&extension : extensions) {
				shaderExtensions << extension << "\n";
			}
		}

		shaderAdditions << "#version " << version << "\n";
		shaderAdditions << shaderExtensions.str() << "\n";
		shaderAdditions << MATH_PI << "\n";
		shaderAdditions << MATH_HALF_PI << "\n";
		shaderAdditions << MATH_2_PI << "\n";

		glCall(uint id = glCreateShader(typeToGL(type)));

		std::string source;
		if (createFromSource) {
			source = pathOrSource;

			if (!dependencies.empty()) {
				for (auto &&dependency : dependencies) {
					shaderAdditions << dependency << "\n";
				}
			}

		} else {
			source = loadFromFile(pathOrSource.c_str());

			if (!dependencies.empty()) {
				for (auto &&dependency : dependencies) {
					shaderAdditions << loadFromFile(dependency.c_str()) << "\n";
				}
			}
		}

		shaderSource << shaderAdditions.str() << "\n";
		shaderSource << source << "\n";

		fullSource = shaderSource.str();
		const char *sourcePtr = fullSource.c_str();

		glCall(glShaderSource(id, 1, &sourcePtr, nullptr));
		glCall(glCompileShader(id));

		GLint result;
		glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE) {
			GLint length;
			glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

			std::vector<char> error(static_cast<uint>(length));
			glCall(glGetShaderInfoLog(id, length, &length, &error[0]));

			std::string errorMessage(&error[0]);

			uint lineNumber;
			sscanf(&error[0], "%*s %*d:%d", &lineNumber);

			XE_FATAL("[GLShaderFile]: Failed to compile ", typeToString(type), " shader.");
			XE_FATAL("[GLShaderFile]: Line: ", lineNumber);
			XE_FATAL("[GLShaderFile]: ", errorMessage);

			glCall(glDeleteShader(id));
			return 0;
		}

		return id;
	}

	void GLShaderFile::parse(api::ShaderUniformBufferVec &uniformBuffers,
	                         api::ShaderResourceVec &resources,
	                         api::ShaderStructVec &structs) {

		const char *token;
		const char *source;

		// Vertex Shader
		source = fullSource.c_str();
		while ((token = utils::findToken(source, "struct"))) {
			parseUniformStruct(utils::getBlock(token, &source), structs);
		}

		source = fullSource.c_str();
		while ((token = utils::findToken(source, "uniform"))) {
			parseUniform(utils::getStatement(token, &source), uniformBuffers, resources, structs);
		}
	}

	void GLShaderFile::parseUniform(const std::string &statement,
	                                api::ShaderUniformBufferVec &uniformBuffers,
	                                api::ShaderResourceVec &resources,
	                                api::ShaderStructVec &structs) {

		std::vector<std::string> tokens = utils::tokenize(statement);
		uint index = 0;

		index++; // "uniform"
		std::string typeStr = tokens[index++];
		std::string name = tokens[index];

		// Strip ; from Name if present
		if (const char *s = strstr(name.c_str(), ";")) {
			name = std::string(name.c_str(), s - name.c_str());
		}

		std::string n(name);
		uint count = 1;
		const char *namestr = n.c_str();

		if (const char *s = strstr(namestr, "[")) {
			name = std::string(namestr, s - namestr);

			const char *end = strstr(namestr, "]");
			std::string c(s + 1, end - s);
			count = static_cast<uint>(atoi(c.c_str()));
		}

		if (isTypeStringResource(typeStr)) {
			auto *decl = new api::GLShaderResource(api::GLShaderResource::stringToType(typeStr), name, count);
			resources.push_back(decl);
		} else {
			api::GLShaderUniform::Type t = api::GLShaderUniform::stringToType(typeStr);
			api::GLShaderUniform *uniform = nullptr;

			if (t == api::GLShaderUniform::Type::NONE) {
				// Find struct
				api::ShaderStruct *s = nullptr;
				for (auto &&st : structs) {
					if (st->getName() == typeStr) {
						s = st;
						break;
					}
				}

				XE_ASSERT(s);
				uniform = new api::GLShaderUniform(s, name, count);
			} else {
				uniform = new api::GLShaderUniform(t, name, count);
			}

			dynamic_cast<api::GLShaderUniformBuffer *>(uniformBuffers.front())->pushUniform(uniform);
		}
	}

	void GLShaderFile::parseUniformStruct(const std::string &block, api::ShaderStructVec &structs) {
		std::vector<std::string> tokens = utils::tokenize(block);

		uint index = 0;
		index++; // struct

		std::string name = tokens[index++];
		api::ShaderStruct *uniformStruct = new api::ShaderStruct(name);

		index++; // {
		while (index < tokens.size()) {
			if (tokens[index] == "}") break;

			std::string type = tokens[index++];
			name = tokens[index++];

			// Strip ; from shaderName if present
			if (const char *s = strstr(name.c_str(), ";")) {
				name = std::string(name.c_str(), s - name.c_str());
			}

			uint count = 1;
			const char *namestr = name.c_str();
			if (const char *s = strstr(namestr, "[")) {
				name = std::string(namestr, s - namestr);

				const char *end = strstr(namestr, "]");
				std::string c(s + 1, end - s);
				count = static_cast<uint>(atoi(c.c_str()));
			}

			auto *field = new api::GLShaderUniform(api::GLShaderUniform::stringToType(type), name, count);
			uniformStruct->addField(field);
		}

		structs.push_back(uniformStruct);
	}

	bool GLShaderFile::isTypeStringResource(const std::string &type) {
		if (type == "image2D") return true;
		if (type == "image3D") return true;
		if (type == "sampler2D") return true;
		if (type == "samplerCube") return true;
		return type == "sampler2DShadow";
	}


}