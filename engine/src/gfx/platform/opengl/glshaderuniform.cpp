//
// Created by FLXR on 7/6/2018.
//

#include <xe/utils/log.hpp>
#include <xe/utils/assert.hpp>
#include "glshaderuniform.hpp"

namespace xe { namespace internal {

	///------ GLShaderUniform ------///
	GLShaderUniform::GLShaderUniform(GLShaderUniform::Type type, const string &name, uint count) :
			type(type),
			name(name),
			count(count),
			size(sizeOfUniformType(type) * count),
			struct_(nullptr) { }

	GLShaderUniform::GLShaderUniform(ShaderStruct *uniformStruct, const string &name, uint count) :
			type(Type::Struct),
			name(name),
			count(count),
			size(uniformStruct->getSize() * count),
			struct_(uniformStruct) { }


	const ShaderStruct &GLShaderUniform::getShaderUniformStruct() const {
		XE_ASSERT(struct_);
		return *struct_;
	}

	uint GLShaderUniform::sizeOfUniformType(GLShaderUniform::Type type) {
		switch (type) {
			case Type::Int32: return 4;
			case Type::Float32: return 4;
			case Type::Vec2: return 4 * 2;
			case Type::Vec3: return 4 * 3;
			case Type::Vec4: return 4 * 4;
			case Type::Mat4: return 4 * 4 * 4;
			case Type::Image2D: return 4;
			case Type::Image3D: return 4;
			default: return 0;
		}
	}

	GLShaderUniform::Type GLShaderUniform::stringToType(const string &type) {
		if (type == "int") return Type::Int32;
		if (type == "float") return Type::Float32;
		if (type == "vec2") return Type::Vec2;
		if (type == "vec3") return Type::Vec3;
		if (type == "vec4") return Type::Vec4;
		if (type == "mat4") return Type::Mat4;
		if (type == "image2D") return Type::Image2D;
		if (type == "image3D") return Type::Image3D;

		return Type::None;
	}

	string GLShaderUniform::typeToString(GLShaderUniform::Type type) {
		switch (type) {
			case Type::Int32: return "int";
			case Type::Float32: return "float";
			case Type::Vec2: return "vec2";
			case Type::Vec3: return "vec3";
			case Type::Vec4: return "vec4";
			case Type::Mat4: return "mat4";
			case Type::Image2D: return "image2D";
			case Type::Image3D: return "image3D";
			default: return "invalid";
		}
	}

	void GLShaderUniform::setOffset(uint offset) {
		if (type == Type::Struct) {
			struct_->setOffset(offset);
		}
		GLShaderUniform::offset = offset;
	}

	///------ GLShaderUniform ------///
	GLShaderUniformBuffer::GLShaderUniformBuffer(const string &name) :
			name(name),
			size(0),
			location(0) { }


	void GLShaderUniformBuffer::pushUniform(GLShaderUniform *uniform) {
		uint offset = 0;

		if (!uniforms.empty()) {
			GLShaderUniform *previous = (GLShaderUniform *) uniforms.back();
			offset = previous->offset + previous->size;
		}

		uniform->setOffset(offset);
		size += uniform->getSize();
		uniforms.push_back(uniform);
	}

	ShaderUniform *GLShaderUniformBuffer::findUniform(const string &name) {
		for (auto &&uniform : uniforms) {
			if (uniform->getName() == name) return uniform;
		}
		return nullptr;
	}

}}