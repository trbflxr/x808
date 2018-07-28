//
// Created by FLXR on 7/25/2018.
//

#ifndef X808_FORWARDRENDERERSHADER_HPP
#define X808_FORWARDRENDERERSHADER_HPP


#include "math/transform.hpp"
#include "gfx/api/shader.hpp"
#include "camera.hpp"
#include "material.hpp"

namespace xe { namespace gfx {

	class XE_API ForwardRendererShader {
	private:
		friend class ForwardRenderer;

	public:
		explicit ForwardRendererShader(api::Shader *shader);

		void bind() const;
		void unbind() const;

		void updateUniforms();

		virtual void setUniforms(const Material *material, const Transform &transform, const Camera *camera) = 0;

	protected:
		void init();

		void setUniform(const char *name, const void *data, size_t size, uint shaderType);

		void bindSamplers(const Material *material);
		void unbindSamplers() const;

		virtual void setUniformsInternal() = 0;

		virtual void setUserUniforms() { }

	private:
		uint getSamplerLocation(const char *name);

	private:
		api::Shader *shader;

		std::vector<api::Uniform> vsUniforms;
		std::vector<api::UniformBuffer> vsUniformBuffers;

		std::vector<api::Uniform> fsUniforms;
		std::vector<api::UniformBuffer> fsUniformBuffers;

		const api::Texture *diffuse;
		const api::Texture *normalMap;
		const api::Texture *dispMap;
	};

}}


#endif //X808_FORWARDRENDERERSHADER_HPP
