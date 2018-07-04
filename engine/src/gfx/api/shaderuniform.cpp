//
// Created by FLXR on 7/4/2018.
//

#include "shaderuniform.hpp"
#include "utils/log.hpp"

///ShaderStruct
void xe::gfx::api::ShaderStruct::addField(xe::gfx::api::ShaderUniform *field) {
	size += field->getSize();
	uint offset = 0;
	if (!fields.empty()) {
		ShaderUniform *previous = fields.back();
		offset = previous->getOffset() + previous->getSize();
	}
	field->setOffset(offset);
	fields.push_back(field);
}

///ShaderUniform
xe::gfx::api::ShaderUniform::ShaderUniform(Type type, const std::string_view &name, uint count) :
		type(type),
		name(name),
		count(count),
		struct_(nullptr),
		size(sizeOfUniformType(type) * count) { }

xe::gfx::api::ShaderUniform::ShaderUniform(ShaderStruct *uniformStruct,
                                           const std::string_view &name, uint count) :
		type(Type::STRUCT),
		name(name),
		count(count),
		struct_(uniformStruct),
		size(uniformStruct->getSize() * count) { }

const xe::gfx::api::ShaderStruct &xe::gfx::api::ShaderUniform::getShaderUniformStruct() const {
	XE_ASSERT(struct_);
	return *struct_;
}

uint xe::gfx::api::ShaderUniform::sizeOfUniformType(xe::gfx::api::ShaderUniform::Type type) {
	switch (type) {
		case Type::INT32: return 4;
		case Type::FLOAT32: return 4;
		case Type::VEC2: return 4 * 2;
		case Type::VEC3: return 4 * 3;
		case Type::VEC4: return 4 * 4;
		case Type::MAT4: return 4 * 4 * 4;
		default: return 0;
	}
}

xe::gfx::api::ShaderUniform::Type xe::gfx::api::ShaderUniform::stringToType(const std::string_view &type) {
	if (type == "int32") return Type::INT32;
	if (type == "float") return Type::FLOAT32;
	if (type == "vec2") return Type::VEC2;
	if (type == "vec3") return Type::VEC3;
	if (type == "vec4") return Type::VEC4;
	if (type == "mat4") return Type::MAT4;

	return Type::NONE;
}

std::string xe::gfx::api::ShaderUniform::typeToString(xe::gfx::api::ShaderUniform::Type type) {
	switch (type) {
		case Type::INT32: return "int32";
		case Type::FLOAT32: return "float";
		case Type::VEC2: return "vec2";
		case Type::VEC3: return "vec3";
		case Type::VEC4: return "vec4";
		case Type::MAT4: return "mat4";
		default: return "invalid";
	}
}

void xe::gfx::api::ShaderUniform::setOffset(uint offset) {
	if (type == Type::STRUCT) {
		struct_->setOffset(offset);
	}
	ShaderUniform::offset = offset;
}

///ShaderUniformBuffer
xe::gfx::api::ShaderUniformBuffer::ShaderUniformBuffer(const std::string_view &name, uint shaderType) :
		name(name), shaderType(shaderType), size(0), register_(0) { }

void xe::gfx::api::ShaderUniformBuffer::pushUniform(xe::gfx::api::ShaderUniform *uniform) {
	uint offset = 0;

	if (!uniforms.empty()) {
		auto &&prev = uniforms.back();
		offset = prev->offset + prev->size;
	}

	uniform->setOffset(offset);
	size += uniform->size;
	uniforms.push_back(uniform);
}

xe::gfx::api::ShaderUniform *xe::gfx::api::ShaderUniformBuffer::findUniform(const std::string_view &name) {
	for (auto &&uniform : uniforms) {
		if (uniform->name == name) return uniform;
	}
	return nullptr;
}
