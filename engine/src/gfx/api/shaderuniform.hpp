//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_SHADERUNIFORM_HPP
#define X808_SHADERUNIFORM_HPP


#include <vector>
#include <string>
#include "common.hpp"
#include "xeint.hpp"

namespace xe { namespace api {

	class XE_API ShaderUniform {
	private:
		friend class BaseShader;
		friend class GLShader;
		friend class ShaderStruct;

	public:
		virtual const std::string &getName() const = 0;
		virtual uint getSize() const = 0;
		virtual uint getCount() const = 0;
		virtual uint getOffset() const = 0;

	protected:
		virtual void setOffset(uint offset) = 0;
	};
	typedef std::vector<ShaderUniform *> ShaderUniformVec;


	///---------------------------///
	class XE_API ShaderUniformBuffer {
	public:
		virtual const std::string &getName() const = 0;
		virtual uint getRegister() const = 0;
		virtual uint getSize() const = 0;
		virtual const ShaderUniformVec &getUniforms() const = 0;

		virtual ShaderUniform *findUniform(const std::string_view &name) = 0;
	};
	typedef std::vector<ShaderUniformBuffer *> ShaderUniformBufferVec;


	///---------------------------///
	class ShaderStruct {
	private:
		friend class BaseShader;

	public:
		explicit ShaderStruct(const std::string_view &name) : name(name), size(0), offset(0) { }

		void addField(ShaderUniform *field) {
			size += field->getSize();
			uint offset = 0;
			if (!fields.empty()) {
				ShaderUniform *previous = fields.back();
				offset = previous->getOffset() + previous->getSize();
			}
			field->setOffset(offset);
			fields.push_back(field);
		}

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

}}


#endif //X808_SHADERUNIFORM_HPP
