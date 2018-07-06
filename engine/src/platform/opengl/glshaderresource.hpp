//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLSHADERRESOURCE_HPP
#define X808_GLSHADERRESOURCE_HPP


#include "gfx/api/shaderresource.hpp"

namespace xe { namespace gfx { namespace api {

	class GLShaderResource : public ShaderResource {
	private:
		friend class GLShader;

	public:
		enum class Type {
			NONE, TEXTURE2D, TEXTURECUBE, TEXTURESHADOW
		};

	public:
		explicit GLShaderResource(Type type, const std::string_view &name, uint count);

		inline const std::string &getName() const override { return name; }
		inline uint getRegister() const override { return register_; }
		inline uint getCount() const override { return count; }

		inline Type getType() const { return type; }

		static Type stringToType(const std::string_view &type);
		static std::string typeToString(Type type);

	private:
		std::string name;
		uint register_;
		uint count;
		Type type;
	};

}}}


#endif //X808_GLSHADERRESOURCE_HPP
