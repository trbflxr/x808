R"(
#shader vertex
#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

out vec2 uv0;

uniform mat4 sys_ProjectionMatrix;
uniform mat4 sys_ViewMatrix;

void main() {
  gl_Position = (sys_ProjectionMatrix * sys_ViewMatrix) * position;
  uv0 = uv;
}

#shader fragment
#version 330

in vec2 uv0;

uniform sampler2D sampler;

void main() {
  vec4 textureColor = texture(sampler, uv0);
  if (textureColor == 0) {
    gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
  } else {
    gl_FragColor = texture(sampler, uv0);
  }
}
)"