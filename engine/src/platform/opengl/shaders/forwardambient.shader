R"(
#shader vertex
#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;

uniform mat4 sys_ProjectionMatrix;
uniform mat4 sys_ViewMatrix;
//uniform mat4 sys_ModelMatrix;

uniform vec3 u_AmbientIntensity;

out vec2 uv0;
out vec3 ambientIntensity0;

void main() {
  gl_Position = (sys_ProjectionMatrix * sys_ViewMatrix) * position;
  uv0 = uv;
  ambientIntensity0 = u_AmbientIntensity;
}

#shader fragment
#version 330

in vec2 uv0;
in vec3 ambientIntensity0;

uniform sampler2D sampler;

void main() {
  gl_FragColor = texture(sampler, uv0) * vec4(ambientIntensity0, 1.0);
}
)"
