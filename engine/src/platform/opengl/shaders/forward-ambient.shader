R"(
#shader vertex
#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;

uniform mat4 sys_MVP;

out vec2 uv0;

void main() {
  gl_Position = sys_MVP * position;
  uv0 = uv;
}

#shader fragment
#version 330

in vec2 uv0;

out vec4 color;

uniform vec4 sys_Color;
uniform float sys_Intensity;

uniform sampler2D sampler;

void main() {
  color = texture(sampler, uv0) * sys_Intensity * sys_Color;
}
)"
