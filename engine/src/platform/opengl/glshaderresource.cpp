//
// Created by FLXR on 7/6/2018.
//

#include "glshaderresource.hpp"

xe::gfx::api::GLShaderResource::GLShaderResource(Type type, const std::string_view &name, uint count) :
		type(type),
		name(name),
		count(count) { }


xe::gfx::api::GLShaderResource::Type xe::gfx::api::GLShaderResource::stringToType(const std::string_view &type) {
	if (type == "sampler2D") return Type::TEXTURE2D;
	if (type == "samplerCube") return Type::TEXTURECUBE;
	if (type == "samplerShadow") return Type::TEXTURESHADOW;

	return Type::NONE;
}

std::string xe::gfx::api::GLShaderResource::typeToString(xe::gfx::api::GLShaderResource::Type type) {
	switch (type) {
		case Type::TEXTURE2D: return "sampler2D";
		case Type::TEXTURECUBE: return "samplerCube";
		case Type::TEXTURESHADOW: return "samplerShadow";
		default:return "invalid";
	}
}
