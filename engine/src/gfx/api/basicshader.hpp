//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_BASICSHADER_HPP
#define X808_BASICSHADER_HPP


#include "shader.hpp"

namespace xe { namespace gfx { namespace api {

	class XE_API BasicShader : public Shader {
	public:
		explicit BasicShader();

		void updateUniforms(const Camera &camera) override;
	};

}}}


#endif //X808_BASICSHADER_HPP
