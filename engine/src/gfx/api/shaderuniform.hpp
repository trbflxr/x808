//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_SHADERUNIFORM_HPP
#define X808_SHADERUNIFORM_HPP


#include <vector>
#include <string>
#include "common.hpp"
#include "xeint.hpp"

namespace xe { namespace gfx { namespace api {

	//todo: move ShaderStruct to file
	class ShaderUniform;

	class ShaderStruct {
	private:
		friend class Shader;

	public:
		explicit ShaderStruct(const std::string_view &name) : name(name), size(0), offset(0) { }

		void addField(ShaderUniform *field);

		inline void setOffset(uint offset) { ShaderStruct::offset = offset; }

		inline const std::string &getName() const { return name; }
		inline uint getSize() const { return size; }
		inline uint getOffset() const { return offset; }
		inline const std::vector<ShaderUniform *> &getFields() const { return fields; }

	private:
		std::string name;
		std::vector<ShaderUniform *> fields;
		uint size;
		uint offset;
	};
	typedef std::vector<ShaderStruct *> ShaderStructVec;


	class XE_API ShaderUniform {
	private:
		friend class Shader;
		friend class ShaderUniformBuffer;
		friend class ShaderStruct;

	public:
		enum class Type {
			NONE, FLOAT32, VEC2, VEC3, VEC4, MAT4, INT32, STRUCT
		};

	public:
		explicit ShaderUniform(Type type, const std::string_view &name, uint count = 1);
		explicit ShaderUniform(ShaderStruct *uniformStruct, const std::string_view &name, uint count = 1);

		inline const std::string &getName() const { return name; }
		inline uint getSize() const { return size; }
		inline uint getCount() const { return count; }
		inline uint getOffset() const { return offset; }
		inline uint getAbsoluteOffset() const { return struct_ ? struct_->getOffset() + offset : offset; }

		uint getLocation() const { return location; }
		inline Type getType() const { return type; }
		const ShaderStruct &getShaderUniformStruct() const;

		static uint sizeOfUniformType(Type type);
		static Type stringToType(const std::string_view &type);
		static std::string typeToString(Type type);

	protected:
		void setOffset(uint offset);

	private:
		std::string name;
		uint size;
		uint count;
		uint offset;

		Type type;
		ShaderStruct *struct_;
		mutable uint location;
	};
	typedef std::vector<ShaderUniform *> ShaderUniformVec;


	struct ShaderUniformField {
		ShaderUniform::Type type;
		std::string name;
		uint count;
		mutable uint size;
		mutable int32 location;
	};


	class ShaderUniformBuffer {
	private:
		friend class Shader1;

	private:
		std::string name;
		ShaderUniformVec uniforms;
		uint register_;
		uint size;
		uint shaderType; // 0 = VS, 1 = FS
	public:
		explicit ShaderUniformBuffer(const std::string_view &name, uint shaderType);

		void pushUniform(ShaderUniform *uniform);

		inline const std::string &getName() const { return name; }
		inline uint getRegister() const { return register_; }
		inline uint getShaderType() const { return shaderType; }
		inline uint getSize() const { return size; }
		inline const ShaderUniformVec &getUniforms() const { return uniforms; }

		ShaderUniform *findUniform(const std::string_view &name);
	};
	typedef std::vector<ShaderUniformBuffer *> ShaderUniformBufferVec;

}}}


#endif //X808_SHADERUNIFORM_HPP
