//
// Created by FLXR on 7/6/2018.
//

#include "glshaderresource.hpp"

namespace xe { namespace api {

	GLShaderResource::GLShaderResource(Type type, const std::string_view &name, uint count) :
			type(type),
			name(name),
			count(count) { }


	GLShaderResource::Type GLShaderResource::stringToType(const std::string_view &type) {
		if (type == "sampler2D") return Type::TEXTURE2D;
		if (type == "samplerCube") return Type::TEXTURECUBE;
		if (type == "samplerShadow") return Type::TEXTURESHADOW;

		return Type::NONE;
	}

	std::string GLShaderResource::typeToString(GLShaderResource::Type type) {
		switch (type) {
			case Type::TEXTURE2D: return "sampler2D";
			case Type::TEXTURECUBE: return "samplerCube";
			case Type::TEXTURESHADOW: return "samplerShadow";
			default:return "invalid";
		}
	}

}}