//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_BASELIGHT_HPP
#define X808_BASELIGHT_HPP


#include "gfx/api/shader.hpp"
#include "gfx/color.hpp"
#include "gfx/model.hpp"
#include "gfx/camera/camera.hpp"

namespace xe { namespace gfx {

	class XE_API BaseLight {
	protected:
		struct BaseLightStruct {
			vec4 color;
			float intensity;
		};

	public:
		virtual ~BaseLight();

		inline void bind() { shader->bind(); }
		inline void unbind() { shader->unbind(); }

		void updateUniforms();

		virtual void setUniforms(const Model *model, const Camera *camera) = 0;

		void setUniform(const char *name, const void *data, size_t size,
		                api::ShaderType shader = api::ShaderType::NONE);

		inline vec4 getColor() const { return baseLight.color; }
		void setColor(uint color);

		inline float getIntensity() const { return baseLight.intensity; }
		void setIntensity(float intensity);

	protected:
		explicit BaseLight(api::Shader *shader, float intensity, uint color = color::WHITE);

		void init();

		virtual void setUniformsInternal() = 0;

	protected:
		BaseLightStruct baseLight;

		api::Shader *shader;

		std::vector<api::Uniform> vsUniforms;
		std::vector<api::UniformBuffer> vsUniformBuffers;

		std::vector<api::Uniform> fsUniforms;
		std::vector<api::UniformBuffer> fsUniformBuffers;
	};

}}


#endif //X808_BASELIGHT_HPP
