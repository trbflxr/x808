//
// Created by FLXR on 7/25/2018.
//

#ifndef X808_FORWARDRENDERERSHADER_HPP
#define X808_FORWARDRENDERERSHADER_HPP


#include "gfx/api/shader.hpp"
#include "gfx/camera/camera.hpp"
#include "gfx/model.hpp"

namespace xe { namespace gfx {

	class XE_API ForwardRendererShader {
	public:
		virtual ~ForwardRendererShader();

		void bind() const;
		void unbind() const;

		void updateUniforms();

		void setUniforms(const Model *model, const Camera *camera);

	protected:
		explicit ForwardRendererShader(api::Shader *shader);

		void init();

		void setUniform(const char *name, const void *data, size_t size, uint shaderType);

		void bindSamplers(const Material *material);
		void unbindSamplers() const;

		virtual void setUniformsInternal() = 0;

		virtual void setUserUniforms() { }

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
