//
// Created by FLXR on 6/29/2018.
//

#include "shader.hpp"
#include "gfx/glcommon.hpp"

xe::gfx::api::Shader::Shader() {

	glCall(handle = glCreateProgram());

	if (!handle) {
		XE_FATAL("Shader creation failed");
	}
}

xe::gfx::api::Shader::~Shader() {
	glCall(glDeleteProgram(handle));
}

void xe::gfx::api::Shader::bind() const {
	glCall(glUseProgram(handle));
}

void xe::gfx::api::Shader::unbind() const {
	glCall(glUseProgram(0));
}

void xe::gfx::api::Shader::addVertexShader(const std::string &shader) {
	addProgram(shader, GL_VERTEX_SHADER);
}

void xe::gfx::api::Shader::addFragmentShader(const std::string &shader) {
	addProgram(shader, GL_FRAGMENT_SHADER);
}

void xe::gfx::api::Shader::addGeometryShader(const std::string &shader) {
	addProgram(shader, GL_GEOMETRY_SHADER);
}

void xe::gfx::api::Shader::addProgram(const std::string &text, uint type) {
	glCall(uint shader = glCreateShader(type));

	if (!shader) {
		XE_FATAL("Shader creation failed");
	}

	const char *shaderSource = text.data();

	glCall(glShaderSource(shader, 1, &shaderSource, nullptr));
	glCall(glCompileShader(shader));

	int32 result;
	glCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE) {
		int32 length;
		glCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));

		char message[length];
		glCall(glGetShaderInfoLog(shader, length, &length, message));

		glCall(glDeleteShader(shader));

		XE_FATAL(message, type);
	}

	glCall(glAttachShader(handle, shader));
}

void xe::gfx::api::Shader::compile() {
	glCall(glLinkProgram(handle));
	validateProgram(GL_LINK_STATUS);

	glCall(glValidateProgram(handle));
	validateProgram(GL_VALIDATE_STATUS);
}

void xe::gfx::api::Shader::validateProgram(uint type) {
	int32 result;
	glCall(glGetProgramiv(handle, type, &result));
	if (result == GL_FALSE) {
		int32 length;
		glCall(glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length));

		char message[length];
		glCall(glGetProgramInfoLog(handle, length, &length, message));

		glCall(glDeleteProgram(handle));

		XE_FATAL("Shader: ", message, type);
	}
}

int xe::gfx::api::Shader::findUniform(const std::string_view &uniform) {
	auto u = uniforms.find(uniform.data());

	if (u == uniforms.end()) {
		XE_FATAL("Shader: unable to find uniform '", uniform, "'");
	}

	return u->second;
}

void xe::gfx::api::Shader::addUniform(const std::string_view &uniform) {
	glCall(int32 location = glGetUniformLocation(handle, uniform.data()));
	if (location == -1) {
		XE_FATAL("Could not find uniform: ", uniform);
	}
	uniforms.emplace(uniform, location);
}

void xe::gfx::api::Shader::setUniform1f(const std::string_view &uniform, float value) {
	glCall(glUniform1f(findUniform(uniform), value));
}

void xe::gfx::api::Shader::setUniform1i(const std::string_view &uniform, int32 value) {
	glCall(glUniform1i(findUniform(uniform), value));
}

void xe::gfx::api::Shader::setUniform1iv(const std::string_view &uniform, uint size, const int32 *value) {
	glCall(glUniform1iv(findUniform(uniform), (int)size, value));
}

void xe::gfx::api::Shader::setUniform1uiv(const std::string_view &uniform, uint size, const uint *value) {
	glCall(glUniform1uiv(findUniform(uniform), (int)size, value));
}

void xe::gfx::api::Shader::setUniform2f(const std::string_view &uniform, const xe::vec2 &vector) {
	glCall(glUniform2f(findUniform(uniform), vector.x, vector.y));
}

void xe::gfx::api::Shader::setUniform3f(const std::string_view &uniform, const xe::vec3 &vector) {
	glCall(glUniform3f(findUniform(uniform), vector.x, vector.y, vector.z));
}

void xe::gfx::api::Shader::setUniformMat4(const std::string_view &uniform, const xe::mat4 &matrix) {
	glCall(glUniformMatrix4fv(findUniform(uniform), 1, GL_FALSE, matrix.elements));
}
