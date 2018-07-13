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

		void setUniform(uint index, const void *data, size_t size);

	protected:
		explicit BaseLight(api::Shader *shader);

	protected:
		api::Shader *shader;

		std::vector<api::Uniform> uniforms;
		std::vector<api::UniformBuffer> uniformBuffers;
	};

}}


#endif //X808_BASELIGHT_HPP
