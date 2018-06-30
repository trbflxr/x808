//
// Created by FLXR on 6/29/2018.
//

#include "basicshader.hpp"

xe::gfx::api::BasicShader::BasicShader() {
	std::string vertex = R"(
		#version 330 core

		layout(location = 0) in vec4 position;
		layout(location = 1) in vec2 uv;
		layout(location = 2) in float tid;
		layout(location = 3) in vec4 color;

		uniform mat4 projectionMatrix;

		out vec2 uv0;
		out float tid0;
		out vec4 color0;

		void main() {
		  gl_Position = projectionMatrix * position;

		  uv0 = uv;
		  tid0 = tid;
		  color0 = color;
		}
    )";

	std::string fragment = R"(
		#version 330 core

		layout (location = 0) out vec4 color;

		in vec2 uv0;
		in float tid0;
		in vec4 color0;

		uniform vec2 cursorPos = vec2(0,0);

		uniform sampler2D textures[32];

		void main() {
		  vec4 texColor = color0;
		  if (tid0 > 0.0) {
		    texColor *= texture2D(textures[int(tid0 - 0.5)], uv0);
		  }

		  color = texColor;
		}
    )";

	addVertexShader(vertex);
	addFragmentShader(fragment);
	compile();

	addUniform("projectionMatrix");
	addUniform("textures");
}

void xe::gfx::api::BasicShader::updateUniforms(const xe::gfx::Camera &camera) {
	setUniformMat4("projectionMatrix", camera.getProjectionMatrix()* camera.getViewMatrix());
}
