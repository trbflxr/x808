//
// Created by FLXR on 8/6/2018.
//

#include <sstream>
#include <vector>
#include <xe/gfx/context.hpp>
#include <xe/utils/string.hpp>
#include "glshaderfile.hpp"
#include "glcommon.hpp"
#include "glenums.hpp"
#include "glshadersampler.hpp"
#include "glshaderuniform.hpp"


namespace xe { namespace internal {

	GLShaderFile::GLShaderFile(bool fromSource, ShaderType type, const string &pathOrSource,
	                           const std::vector<string> &dependencies,
	                           const std::vector<string> &extensions) :
			ShaderFile(fromSource, type, pathOrSource, dependencies, extensions) {

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
		++addedLines;

		shaderAdditions << "#version " << Context::getRenderAPIVersion() << "\n";
		shaderAdditions << shaderExtensions.str() << "\n";
		shaderAdditions << MATH_PI << "\n";
		shaderAdditions << MATH_HALF_PI << "\n";
		shaderAdditions << MATH_2_PI << "\n ";

		string source;
		if (createFromSource) {
			source = pathOrSource;

			if (!dependencies.empty()) {
				for (auto &&dependency : dependencies) {
					shaderAdditions << "\n" << dependency;
				}
				++addedLines;
			}

		} else {
			source = loadFromFile(pathOrSource.data());

			if (!dependencies.empty()) {
				for (auto &&dependency : dependencies) {
					shaderAdditions << "\n" << loadFromFile(dependency.c_str());
				}
				++addedLines;
			}
		}

		setConstants(source);

		shaderSource << shaderAdditions.str() << "\n";
		shaderSource << source;

		auto vec = utils::splitString(shaderAdditions.str(), '\n');
		addedLines += vec.size();

		fullSource = shaderSource.str();
	}

	uint GLShaderFile::compile() {
		glCall(uint id = glCreateShader(shaderTypeToGL(type)));

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

			string errorMessage(&error[0]);
			string line;

			//get error line
			for (int i = 2; i < error.size(); ++i) {
				if (error[i] == ')') break;
				line += error[i];
			}
			uint lineNumber = std::stoul(line) - addedLines;

			XE_FATAL("[GLShaderFile]: Failed to compile ", typeToString(type), " shader.");
			XE_FATAL("[GLShaderFile]: Line: ", lineNumber);
			XE_FATAL("[GLShaderFile]: ", errorMessage);

			glCall(glDeleteShader(id));
			return 0;
		}

		return id;
	}

	void GLShaderFile::parse(ShaderUniformBufferVec &buffers,
	                         ShaderSamplerVec &samplers,
	                         ShaderStructVec &structs) {

		const char *token;
		const char *source;

		//structs
		source = fullSource.c_str();
		while ((token = utils::findToken(source, "struct"))) {
			parseUniformStruct(utils::getBlock(token, &source), structs);
		}

		//uniforms
		source = fullSource.c_str();
		while ((token = utils::findToken(source, "uniform"))) {
			parseUniform(utils::getStatement(token, &source), buffers, samplers, structs);
		}
	}

	void GLShaderFile::parseUniform(const string &statement,
	                                ShaderUniformBufferVec &buffers,
	                                ShaderSamplerVec &samplers,
	                                ShaderStructVec &structs) {

		std::vector<string> tokens = utils::tokenize(statement);
		uint index = 0;

		index++; // "uniform"
		string typeStr = tokens[index++];
		string name = tokens[index];

		// Strip ; from Name if present
		if (const char *s = strstr(name.c_str(), ";")) {
			name = string(name.c_str(), s - name.c_str());
		}

		string n(name);
		uint count = 1;
		const char *nameStr = n.c_str();

		if (const char *s = strstr(nameStr, "[")) {
			name = string(nameStr, s - nameStr);

			const char *end = strstr(nameStr, "]");
			string c(s + 1, end - s);
			count = static_cast<uint>(atoi(c.c_str()));
		}

		if (GLShaderSampler::isTypeStrSampler(typeStr)) {
			auto *decl = new GLShaderSampler(GLShaderSampler::stringToType(typeStr), name, count);
			samplers.push_back(decl);
		} else if (name != "{" && name != "{\n" && name != "{\r") {
			GLShaderUniform::Type t = GLShaderUniform::stringToType(typeStr);
			GLShaderUniform *uniform = nullptr;

			if (t == GLShaderUniform::Type::None) {
				// Find struct
				ShaderStruct *s = nullptr;
				for (auto &&st : structs) {
					if (st->getName() == typeStr) {
						s = st;
						break;
					}
				}

				XE_ASSERT(s, "[GLShaderFile]: Could not find struct: ", typeStr, " ", name);
				uniform = new GLShaderUniform(s, name, count);
			} else {
				uniform = new GLShaderUniform(t, name, count);
			}

			dynamic_cast<GLShaderUniformBuffer *>(buffers.front())->pushUniform(uniform);
		}
	}

	void GLShaderFile::parseUniformStruct(const string &block, ShaderStructVec &structs) {
		std::vector<string> tokens = utils::tokenize(block);

		uint index = 1; // struct

		string name = tokens[index++];
		ShaderStruct *uniformStruct = new ShaderStruct(name);

		index++; // {
		while (index < tokens.size()) {
			if (tokens[index] == "}") break;

			string type = tokens[index++];
			name = tokens[index++];

			// Strip ; from shaderName if present
			if (const char *s = strstr(name.c_str(), ";")) {
				name = string(name.c_str(), s - name.c_str());
			}

			uint count = 1;
			const char *namestr = name.c_str();
			if (const char *s = strstr(namestr, "[")) {
				const char *end = strstr(namestr, "]");
				string c(s + 1, end - s);
				count = static_cast<uint>(atoi(c.c_str()));
				name = string(namestr, s - namestr);
			}

			auto *field = new GLShaderUniform(GLShaderUniform::stringToType(type), name, count);
			uniformStruct->addField(field);
		}

		structs.push_back(uniformStruct);
	}

	void GLShaderFile::setConstants(string &source) {
		const string str = "@MAX_TEXTURES";
		const size_t pos = source.find(str);
		if (pos != string::npos) {
			source.replace(pos, str.size(), std::to_string(Context::getMaxTextureUnits()));
		}
	}

}}