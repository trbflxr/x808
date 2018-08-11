//
// Created by FLXR on 7/25/2018.
//

#ifndef X808_FORWARDRENDERERSHADER_HPP
#define X808_FORWARDRENDERERSHADER_HPP


#include "math/transform.hpp"
#include "gfx/api/baseshader.hpp"
#include "camera.hpp"
#include "material.hpp"

namespace xe {

	class XE_API ForwardRendererShader {
	private:
		friend class ForwardRenderer;

	public:
		explicit ForwardRendererShader(api::BaseShader *shader);
		~ForwardRendererShader();

		void bind() const;
		void unbind() const;

		void updateUniforms();

		virtual void setUniforms(const Material *material, const Transform &transform, Camera *camera);

		inline api::BaseShader *getShader() { return shader; }

	protected:
		void init();

		void setUniform(const char *name, const void *data, size_t size);

		void bindSamplers(const Material *material);
		void unbindSamplers() const;

		virtual void setUniformsInternal() { };

		virtual void setUserUniforms() { }

	private:
		api::BaseShader *shader;

		std::vector<api::Uniform> uniforms;
		std::vector<api::UniformData> uniformData;

		const api::Texture *diffuse;
		const api::Texture *normalMap;
		const api::Texture *dispMap;
	};

}


#endif //X808_FORWARDRENDERERSHADER_HPP
