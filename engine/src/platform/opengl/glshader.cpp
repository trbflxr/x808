//
// Created by FLXR on 7/6/2018.
//

#include "glshader.hpp"
#include "glcommon.hpp"
#include "utils/log.hpp"
#include "utils/string.hpp"


xe::gfx::api::GLShader::GLShader(const std::string_view &name, const std::string &source) :
		name(name),
		source(source),
		vsUserUniformBuffer(nullptr),
		fsUserUniformBuffer(nullptr) {

	std::string *shaders[2] = {&vertexSource, &fragmentSource};
	preProcess(source, shaders);

	parse(vertexSource, fragmentSource);

	ShaderErrorInfo *info = new ShaderErrorInfo();

	handle = compile(shaders, info);
	if (!handle) {
		XE_FATAL(info->message[info->shader]);
	}

	delete info;

	XE_ASSERT(handle);

	resolveUniforms();
	validateUniforms();
}

xe::gfx::api::GLShader::~GLShader() {
	glCall(glDeleteProgram(handle));
}

void xe::gfx::api::GLShader::bind() const {
	glCall(glUseProgram(handle));
}

void xe::gfx::api::GLShader::unbind() const {
	glCall(glUseProgram(0));
}

void xe::gfx::api::GLShader::setVSSystemUniformBuffer(byte *data, uint size, uint slot) {
	bind();
	XE_ASSERT(vsUniformBuffers.size() > slot);
	resolveAndSetUniforms(vsUniformBuffers[slot], data, size);
}

void xe::gfx::api::GLShader::setFSSystemUniformBuffer(byte *data, uint size, uint slot) {
	bind();
	XE_ASSERT(fsUniformBuffers.size() > slot);
	resolveAndSetUniforms(fsUniformBuffers[slot], data, size);
}

void xe::gfx::api::GLShader::setVSUserUniformBuffer(byte *data, uint size) {
	resolveAndSetUniforms(vsUserUniformBuffer, data, size);
}

void xe::gfx::api::GLShader::setFSUserUniformBuffer(byte *data, uint size) {
	resolveAndSetUniforms(fsUserUniformBuffer, data, size);
}

void xe::gfx::api::GLShader::setUniform(const std::string_view &name, byte *data) {
	ShaderUniform *uniform = findUniform(name);
	if (!uniform) {
		XE_ERROR("Cannot find uniform in ", name, " shader with shaderName '", GLShader::name, "'");
		return;
	}
	resolveAndSetUniform((GLShaderUniform *) uniform, data, 0);
}

void xe::gfx::api::GLShader::resolveAndSetUniformField(const GLShaderUniform &field, byte *data, int32 offset) {
	switch (field.getType()) {
		case GLShaderUniform::Type::FLOAT32: setUniform1f(field.getLocation(), *(float *) &data[offset]);
			break;
		case GLShaderUniform::Type::INT32: setUniform1i(field.getLocation(), *(int32 *) &data[offset]);
			break;
		case GLShaderUniform::Type::VEC2: setUniform2f(field.getLocation(), *(vec2 *) &data[offset]);
			break;
		case GLShaderUniform::Type::VEC3: setUniform3f(field.getLocation(), *(vec3 *) &data[offset]);
			break;
		case GLShaderUniform::Type::VEC4: setUniform4f(field.getLocation(), *(vec4 *) &data[offset]);
			break;
		case GLShaderUniform::Type::MAT4: setUniformMat4(field.getLocation(), *(mat4 *) &data[offset]);
			break;
		default: XE_ASSERT(false, "Unknown type!");
	}
}

uint xe::gfx::api::GLShader::compile(std::string **shaders, xe::gfx::api::ShaderErrorInfo *info) {
	const char *vertexSource = shaders[0]->c_str();
	const char *fragmentSource = shaders[1]->c_str();

	glCall(uint
			       program = glCreateProgram());
	glCall(GLuint
			       vertex = glCreateShader(GL_VERTEX_SHADER));
	glCall(GLuint
			       fragment = glCreateShader(GL_FRAGMENT_SHADER));

	glCall(glShaderSource(vertex, 1, &vertexSource, nullptr));
	glCall(glCompileShader(vertex));

	GLint result;
	glCall(glGetShaderiv(vertex, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		if (info) {
			GLint length;
			glCall(glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length));

			std::vector<char> error(static_cast<uint>(length));
			glCall(glGetShaderInfoLog(vertex, length, &length, &error[0]));

			std::string errorMessage(&error[0]);

			info->shader = 0;
			info->message[info->shader] += "Failed to compile vertex shader!\n";
			info->message[info->shader] += errorMessage;
		}

		glCall(glDeleteShader(vertex));
		return 0;
	}

	glCall(glShaderSource(fragment, 1, &fragmentSource, nullptr));
	glCall(glCompileShader(fragment));

	glCall(glGetShaderiv(fragment, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		if (info) {
			GLint length;
			glCall(glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length));

			std::vector<char> error(static_cast<uint>(length));
			glCall(glGetShaderInfoLog(fragment, length, &length, &error[0]));

			std::string errorMessage(&error[0], static_cast<uint>(length));
			uint lineNumber;
			sscanf(&error[0], "%*s %*d:%d", &lineNumber);

			info->shader = 1;
			info->message[info->shader] += "Failed to compile fragment shader!\n";
			info->line[info->shader] = lineNumber;
			info->message[info->shader] += errorMessage;
		}

		glCall(glDeleteShader(fragment));
		return 0;
	}

	glCall(glAttachShader(program, vertex));
	glCall(glAttachShader(program, fragment));

	glCall(glLinkProgram(program));
	glCall(glValidateProgram(program));

	glCall(glDetachShader(program, vertex));
	glCall(glDetachShader(program, fragment));

	glCall(glDeleteShader(vertex));
	glCall(glDeleteShader(fragment));

	return program;
}

void xe::gfx::api::GLShader::preProcess(const std::string &source, std::string **shaders) {
	int32 type = -1;

	std::vector<std::string> lines = utils::getLines(source);
	for (auto &&line : lines) {
		const char *str = line.c_str();
		if (strstr(str, "#shader")) {
			if (strstr(str, "vertex")) {
				type = 0;
			} else if (strstr(str, "fragment")) {
				type = 1;
			}
		} else if (type != -1) {
			shaders[type]->append(str);
			shaders[type]->append("\n");
		}
	}
}

void xe::gfx::api::GLShader::parse(const std::string &vertexSource, const std::string &fragmentSource) {
	vsUniformBuffers.push_back(new GLShaderUniformBuffer("Global", 0));
	fsUniformBuffers.push_back(new GLShaderUniformBuffer("Global", 1));

	const char *token;
	const char *vstr;
	const char *fstr;

	// Vertex Shader
	vstr = vertexSource.c_str();
	while ((token = utils::findToken(vstr, "struct"))) {
		parseUniformStruct(utils::getBlock(token, &vstr), 0);
	}

	vstr = vertexSource.c_str();
	while ((token = utils::findToken(vstr, "uniform"))) {
		parseUniform(utils::getStatement(token, &vstr), 0);
	}

	// Fragment Shader
	fstr = fragmentSource.c_str();
	while ((token = utils::findToken(fstr, "struct"))) {
		parseUniformStruct(utils::getBlock(token, &fstr), 1);
	}

	fstr = fragmentSource.c_str();
	while ((token = utils::findToken(fstr, "uniform"))) {
		parseUniform(utils::getStatement(token, &fstr), 1);
	}
}

void xe::gfx::api::GLShader::parseUniform(const std::string &statement, uint shaderType) {
	std::vector<std::string> tokens = utils::tokenize(statement);
	uint index = 0;

	index++; // "uniform"
	std::string typeStr = tokens[index++];
	std::string name = tokens[index++];

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
		auto *declaration = new GLShaderResource(GLShaderResource::stringToType(typeStr), name, count);
		resources.push_back(declaration);
	} else {
		GLShaderUniform::Type t = GLShaderUniform::stringToType(typeStr);
		GLShaderUniform *uniform = nullptr;

		if (t == GLShaderUniform::Type::NONE) {
			// Find struct
			ShaderStruct *s = findStruct(typeStr);
			XE_ASSERT(s);
			uniform = new GLShaderUniform(s, name, count);
		} else {
			uniform = new GLShaderUniform(t, name, count);
		}

		if (utils::startsWith(name, "sys_")) {
			if (shaderType == 0) {
				dynamic_cast<GLShaderUniformBuffer *>(vsUniformBuffers.front())->pushUniform(uniform);
			} else if (shaderType == 1) {
				dynamic_cast<GLShaderUniformBuffer *>(fsUniformBuffers.front())->pushUniform(uniform);
			}
		} else {
			if (shaderType == 0) {
				if (vsUserUniformBuffer == nullptr) {
					vsUserUniformBuffer = new GLShaderUniformBuffer("", 0);
				}

				vsUserUniformBuffer->pushUniform(uniform);
			} else if (shaderType == 1) {
				if (fsUserUniformBuffer == nullptr) {
					fsUserUniformBuffer = new GLShaderUniformBuffer("", 1);
				}

				fsUserUniformBuffer->pushUniform(uniform);
			}
		}
	}
}

void xe::gfx::api::GLShader::parseUniformStruct(const std::string &block, uint shaderType) {
	std::vector<std::string> tokens = utils::tokenize(block);

	uint index = 0;
	index++; // struct

	std::string name = tokens[index++];
	ShaderStruct *uniformStruct = new ShaderStruct(name);

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

		auto *field = new GLShaderUniform(GLShaderUniform::stringToType(type), name, count);
		uniformStruct->addField(field);
	}

	structs.push_back(uniformStruct);
}

bool xe::gfx::api::GLShader::isTypeStringResource(const std::string &type) {
	if (type == "sampler2D") return true;
	if (type == "samplerCube") return true;
	return type == "sampler2DShadow";
}

xe::gfx::api::ShaderStruct *xe::gfx::api::GLShader::findStruct(const std::string &name) {
	for (ShaderStruct *s : structs) {
		if (s->getName() == name) return s;
	}
	return nullptr;
}

void xe::gfx::api::GLShader::resolveUniforms() {
	bind();

	for (auto &&vsBuffer : vsUniformBuffers) {
		GLShaderUniformBuffer *decl = (GLShaderUniformBuffer *) vsBuffer;

		for (auto &&u : decl->getUniforms()) {
			GLShaderUniform *uniform = (GLShaderUniform *) u;

			if (uniform->getType() == GLShaderUniform::Type::STRUCT) {
				const ShaderStruct &s = uniform->getShaderUniformStruct();

				for (auto &&f : s.getFields()) {
					GLShaderUniform *field = (GLShaderUniform *) f;
					field->location = getUniformLocation(uniform->name + "." + field->name);
				}
			} else {
				uniform->location = getUniformLocation(uniform->name);
			}
		}

		for (auto &&fsBuffer : fsUniformBuffers) {
			decl = (GLShaderUniformBuffer *) fsBuffer;

			for (auto &&u : decl->getUniforms()) {
				GLShaderUniform *uniform = (GLShaderUniform *) u;

				if (uniform->getType() == GLShaderUniform::Type::STRUCT) {
					const ShaderStruct &s = uniform->getShaderUniformStruct();

					for (auto &&f : s.getFields()) {
						GLShaderUniform *field = (GLShaderUniform *) f;
						field->location = getUniformLocation(uniform->name + "." + field->name);
					}
				} else {
					uniform->location = getUniformLocation(uniform->name);
				}
			}
		}

		if (vsUserUniformBuffer) {
			for (auto &&u : vsUserUniformBuffer->getUniforms()) {
				GLShaderUniform *uniform = (GLShaderUniform *) u;

				if (uniform->getType() == GLShaderUniform::Type::STRUCT) {
					const ShaderStruct &s = uniform->getShaderUniformStruct();

					for (auto &&f : s.getFields()) {
						GLShaderUniform *field = (GLShaderUniform *) f;
						field->location = getUniformLocation(uniform->name + "." + field->name);
					}
				} else {
					uniform->location = getUniformLocation(uniform->name);
				}
			}
		}


		if (fsUserUniformBuffer) {
			for (auto &&u : fsUserUniformBuffer->getUniforms()) {
				GLShaderUniform *uniform = (GLShaderUniform *) u;

				if (uniform->getType() == GLShaderUniform::Type::STRUCT) {
					const ShaderStruct &s = uniform->getShaderUniformStruct();

					for (auto &&f : s.getFields()) {
						GLShaderUniform *field = (GLShaderUniform *) f;
						field->location = getUniformLocation(uniform->name + "." + field->name);
					}
				} else {
					uniform->location = getUniformLocation(uniform->name);
				}
			}
		}


		uint sampler = 0;
		for (auto &res : resources) {
			GLShaderResource *resource = (GLShaderResource *) res;

			uint location = getUniformLocation(resource->name);
			if (resource->count == 1) {
				resource->register_ = sampler;
				setUniform1i(location, sampler++);

			} else if (resource->count > 1) {
				resource->register_ = 0;

				uint count = resource->count;
				int32 *samplers = new int32[count];

				for (uint s = 0; s < count; s++) {
					samplers[s] = s;
				}

				setUniform1iv(resource->getName(), samplers, count);
				delete[] samplers;
			}
		}

		unbind();
	}
}

void xe::gfx::api::GLShader::validateUniforms() { }

bool xe::gfx::api::GLShader::isSystemUniform(xe::gfx::api::ShaderUniform *uniform) const {
	return utils::startsWith(uniform->getName(), "sys_");
}

uint xe::gfx::api::GLShader::getUniformLocation(const std::string_view &name) {
	glCall(GLint result = glGetUniformLocation(handle, name.data()));
	if (result == -1) {
		XE_ERROR(GLShader::name, ": could not find uniform ", name, " in shader!");
	}

	return static_cast<uint>(result);
}

xe::gfx::api::ShaderUniform *xe::gfx::api::GLShader::findUniform(const std::string_view &name,
                                                                 const ShaderUniformBuffer *buff) {
	for (auto &&uniform : buff->getUniforms()) {
		if (uniform->getName() == name) return uniform;
	}
	return nullptr;
}

xe::gfx::api::ShaderUniform *xe::gfx::api::GLShader::findUniform(const std::string_view &name) {
	ShaderUniform *result = nullptr;

	for (auto &&buffer : vsUniformBuffers) {
		result = findUniform(name, buffer);
		if (result) return result;
	}

	for (auto &&buffer : fsUniformBuffers) {
		result = findUniform(name, buffer);
		if (result) return result;
	}

	result = findUniform(name, vsUserUniformBuffer);
	if (result) return result;

	result = findUniform(name, fsUserUniformBuffer);
	if (result) return result;

	return result;
}

void xe::gfx::api::GLShader::resolveAndSetUniforms(ShaderUniformBuffer *buffer, byte *data, uint size) {
	const ShaderUniformVec &uniforms = buffer->getUniforms();
	for (auto &&uniform : uniforms) {
		resolveAndSetUniform((GLShaderUniform *) uniform, data, size);
	}
}

void xe::gfx::api::GLShader::resolveAndSetUniform(xe::gfx::api::GLShaderUniform *uniform, byte *data, uint size) {
	if (uniform->getLocation() == -1) return;

	uint offset = uniform->getOffset();
	switch (uniform->getType()) {
		case GLShaderUniform::Type::FLOAT32: setUniform1f(uniform->getLocation(), *(float *) &data[offset]);
			break;
		case GLShaderUniform::Type::INT32: setUniform1i(uniform->getLocation(), *(int32 *) &data[offset]);
			break;
		case GLShaderUniform::Type::VEC2: setUniform2f(uniform->getLocation(), *(vec2 *) &data[offset]);
			break;
		case GLShaderUniform::Type::VEC3: setUniform3f(uniform->getLocation(), *(vec3 *) &data[offset]);
			break;
		case GLShaderUniform::Type::VEC4: setUniform4f(uniform->getLocation(), *(vec4 *) &data[offset]);
			break;
		case GLShaderUniform::Type::MAT4: setUniformMat4(uniform->getLocation(), *(mat4 *) &data[offset]);
			break;
		case GLShaderUniform::Type::STRUCT: setUniformStruct(uniform, data, offset);
			break;
		default: XE_ASSERT(false, "Unknown type!");
	}
}

void xe::gfx::api::GLShader::setUniformStruct(xe::gfx::api::GLShaderUniform *uniform, byte *data, int32 offset) {
	const ShaderStruct &s = uniform->getShaderUniformStruct();
	const auto &fields = s.getFields();

	for (auto &&field : fields) {
		auto &&f = (GLShaderUniform *) field;

		resolveAndSetUniformField(*f, data, offset);
		offset += field->getSize();
	}
}

void xe::gfx::api::GLShader::setUniform1f(const std::string_view &name, float value) {
	setUniform1f(getUniformLocation(name), value);
}

void xe::gfx::api::GLShader::setUniform1fv(const std::string_view &name, float *value, int32 count) {
	setUniform1fv(getUniformLocation(name), value, count);
}

void xe::gfx::api::GLShader::setUniform1i(const std::string_view &name, int32 value) {
	setUniform1i(getUniformLocation(name), value);
}

void xe::gfx::api::GLShader::setUniform1iv(const std::string_view &name, int32 *value, int32 count) {
	setUniform1iv(getUniformLocation(name), value, count);
}

void xe::gfx::api::GLShader::setUniform2f(const std::string_view &name, const xe::vec2 &vector) {
	setUniform2f(getUniformLocation(name), vector);
}

void xe::gfx::api::GLShader::setUniform3f(const std::string_view &name, const xe::vec3 &vector) {
	setUniform3f(getUniformLocation(name), vector);
}

void xe::gfx::api::GLShader::setUniform4f(const std::string_view &name, const xe::vec4 &vector) {
	setUniform4f(getUniformLocation(name), vector);
}

void xe::gfx::api::GLShader::setUniformMat4(const std::string_view &name, const xe::mat4 &matrix) {
	setUniformMat4(getUniformLocation(name), matrix);
}

void xe::gfx::api::GLShader::setUniform1f(uint location, float value) {
	glCall(glUniform1f(location, value));
}

void xe::gfx::api::GLShader::setUniform1fv(uint location, float *value, int32 count) {
	glCall(glUniform1fv(location, count, value));
}

void xe::gfx::api::GLShader::setUniform1i(uint location, int32 value) {
	glCall(glUniform1i(location, value));
}

void xe::gfx::api::GLShader::setUniform1iv(uint location, int32 *value, int32 count) {
	glCall(glUniform1iv(location, count, value));
}

void xe::gfx::api::GLShader::setUniform2f(uint location, const xe::vec2 &vector) {
	glCall(glUniform2f(location, vector.x, vector.y));
}

void xe::gfx::api::GLShader::setUniform3f(uint location, const xe::vec3 &vector) {
	glCall(glUniform3f(location, vector.x, vector.y, vector.z));
}

void xe::gfx::api::GLShader::setUniform4f(uint location, const xe::vec4 &vector) {
	glCall(glUniform4f(location, vector.x, vector.y, vector.z, vector.w));
}

void xe::gfx::api::GLShader::setUniformMat4(uint location, const xe::mat4 &matrix) {
	glCall(glUniformMatrix4fv(location, 1, GL_TRUE, matrix.elements));
}

bool xe::gfx::api::GLShader::tryCompile(const std::string &source, std::string &error) {
	return false;
}

bool xe::gfx::api::GLShader::tryCompileFromFile(const std::string &file, std::string &error) {
	return false;
}
