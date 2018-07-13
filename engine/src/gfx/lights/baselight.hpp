//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_BASELIGHT_HPP
#define X808_BASELIGHT_HPP


#include "gfx/api/shader.hpp"

namespace xe { namespace gfx {

	class XE_API BaseLight {
	public:
		virtual ~BaseLight();

		void bindAndSetUniforms();

		void setUniform(const char *name, const void *data, size_t size,
		                api::ShaderType shader = api::ShaderType::NONE);

	protected:
		explicit BaseLight(api::Shader *shader);

	protected:
		api::Shader *shader;

		std::vector<api::Uniform> vsUniforms;
		std::vector<api::UniformBuffer> vsUniformBuffers;

		std::vector<api::Uniform> fsUniforms;
		std::vector<api::UniformBuffer> fsUniformBuffers;
	};

}}


#endif //X808_BASELIGHT_HPP
