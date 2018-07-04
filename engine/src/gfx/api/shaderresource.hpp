//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_SHADERRESOURCE_HPP
#define X808_SHADERRESOURCE_HPP


#include <vector>
#include <string>
#include "common.hpp"
#include "xeint.hpp"

namespace xe { namespace gfx { namespace api {

	class XE_API ShaderResource {
	private:
		friend class Shader;

	public:
		enum class Type {
			NONE, TEXTURE2D, TEXTURECUBE, TEXTURESHADOW
		};

	public:
		explicit ShaderResource(Type type, const std::string_view &name, uint count);

		inline const std::string &getName() const { return name; }
		inline uint getRegister() const { return register_; }
		inline uint getCount() const { return count; }
		inline Type getType() const { return type; }

		static Type stringToType(const std::string_view &type);
		static std::string typeToString(Type type);

	private:
		std::string name;
		uint register_;
		uint count;
		Type type;
	};

	typedef std::vector<ShaderResource *> ShaderResourceVec;

}}}


#endif //X808_SHADERRESOURCE_HPP
