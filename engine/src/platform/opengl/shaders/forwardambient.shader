R"(
#shader vertex
#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;

uniform mat4 sys_ProjectionMatrix;
uniform mat4 sys_ViewMatrix;

out vec2 uv0;

void main() {
  gl_Position = (sys_ProjectionMatrix * sys_ViewMatrix) * position;
  uv0 = uv;
}

#shader fragment
#version 330

in vec2 uv0;

uniform vec3 sys_AmbientIntensity;

uniform sampler2D sampler;

void main() {
  gl_FragColor = texture(sampler, uv0) * vec4(sys_AmbientIntensity, 1.0);
}
)"
