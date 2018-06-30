//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_SHADER_HPP
#define X808_SHADER_HPP


#include <string>
#include <unordered_map>
#include "common.hpp"
#include "xeint.hpp"
#include "math/math.hpp"
#include "gfx/camera/camera.hpp"

namespace xe { namespace gfx { namespace api {

	class XE_API Shader {
	public:
		virtual ~Shader();

		void bind() const;
		void unbind() const;

		void addUniform(const std::string_view &uniform);

		void setUniform1f(const std::string_view &uniform, float value);
		void setUniform1i(const std::string_view &uniform, int32 value);
		void setUniform1iv(const std::string_view &uniform, uint size, const int32 *value);
		void setUniform1uiv(const std::string_view &uniform, uint size, const uint *value);
		void setUniform2f(const std::string_view &uniform, const vec2 &vector);
		void setUniform3f(const std::string_view &uniform, const vec3 &vector);
		void setUniformMat4(const std::string_view &uniform, const mat4 &matrix);

		virtual void updateUniforms(const Camera &camera) { }

	protected:
		explicit Shader();

		void compile();

		void addVertexShader(const std::string &shader);
		void addFragmentShader(const std::string &shader);
		void addGeometryShader(const std::string &shader);

	private:
		void addProgram(const std::string &text, uint type);
		void validateProgram(uint type);

		int findUniform(const std::string_view &uniform);

	private:
		uint handle;
		std::unordered_map<std::string, int32> uniforms;
	};

}}}


#endif //X808_SHADER_HPP
