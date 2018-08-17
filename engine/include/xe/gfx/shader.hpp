//
// Created by FLXR on 8/11/2018.
//

#ifndef X808_SHADER_HPP
#define X808_SHADER_HPP


#include <xe/gfx/baseshader.hpp>

namespace xe {

	class XE_API Shader {
	public:
		explicit Shader(BaseShader *shader);
		explicit Shader(const string &nameInShaderManager);
		virtual ~Shader();

		virtual void bind() const;
		virtual void unbind() const;

		void updateUniforms();

		void setUniform(const string &name, const void *data, size_t size);

		uint getSampler(const string &name);

		inline BaseShader *getBaseShader() { return shader; }

		virtual void setUniformsInternal() { };
		virtual void setUserUniforms() { }

	private:
		void init();

	protected:
		BaseShader *shader;

		std::vector<Uniform> uniforms;
		std::vector<UniformData> uniformData;
	};

}

#endif //X808_SHADER_HPP
