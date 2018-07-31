//
// Created by FLXR on 7/30/2018.
//

#include "shadowmapblurshader.hpp"

namespace xe { namespace gfx {

	ShadowMapBlurShader::ShadowMapBlurShader(api::Shader *shader) :
			ForwardRendererShader(shader) {

		setUniformsInternal();
	}

	void ShadowMapBlurShader::setUniforms(const Material *m, const Transform &transform, Camera *camera) {
		mat4 world = transform.toMatrix();
		mat4 mvp = camera->getViewProjection() * world;

		setUniform("sys_MVP", &mvp.elements, sizeof(mat4), api::Shader::VERT);

		setUserUniforms();

		bindSamplers(m);
	}

}}