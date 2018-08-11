//
// Created by FLXR on 8/11/2018.
//

#ifndef X808_SHADER_HPP
#define X808_SHADER_HPP


#include "gfx/api/baseshader.hpp"

namespace xe {

	class XE_API Shader {
	public:
		explicit Shader(api::BaseShader *shader);
		explicit Shader(const std::string_view &nameInShaderManager);
		virtual ~Shader();

		virtual void bind() const;
		virtual void unbind() const;

		void updateUniforms();

		void setUniform(const std::string_view &name, const void *data, size_t size);

		uint getResource(const std::string_view &name);

		inline api::BaseShader *getBaseShader() { return shader; }

		virtual void setUniformsInternal() { };
		virtual void setUserUniforms() { }

	private:
		void init();

	protected:
		api::BaseShader *shader;

		std::vector<api::Uniform> uniforms;
		std::vector<api::UniformData> uniformData;
	};

}

#endif //X808_SHADER_HPP
