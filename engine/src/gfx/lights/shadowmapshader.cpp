//
// Created by FLXR on 7/26/2018.
//

#include "shadowmapshader.hpp"

namespace xe { namespace gfx {

	ShadowMapShader::ShadowMapShader(api::Shader *shader) :
			ForwardRendererShader(shader) {

		setUniformsInternal();
	}

	void ShadowMapShader::setUniforms(const Material *m, const xe::Transform &transform, const Camera *camera) {
		mat4 world = transform.toMatrix();
		mat4 mvp = camera->getViewProjection() * world;

		setUniform("sys_MVP", &mvp.elements, sizeof(mat4), api::Shader::VERT);

		setUserUniforms();
	}

}}
