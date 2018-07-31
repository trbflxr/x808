R"(
#shader vertex
#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;

out vec2 uv0;

uniform mat4 sys_MVP;

void main() {
  gl_Position = sys_MVP * position;
  uv0 = uv;
}

#shader fragment
#version 330

in vec2 uv0;

out vec4 out_Color;

uniform vec2 sys_BlurScale;

//diffuse in this case = filterTexture
uniform sampler2D diffuse;

void main() {
  out_Color = vec4(0.0);

  out_Color += texture(diffuse, uv0 + (vec2(-3.0) * sys_BlurScale)) * (1.0 / 64.0);
  out_Color += texture(diffuse, uv0 + (vec2(-2.0) * sys_BlurScale)) * (6.0 / 64.0);
  out_Color += texture(diffuse, uv0 + (vec2(-1.0) * sys_BlurScale)) * (15.0 / 64.0);
  out_Color += texture(diffuse, uv0 + (vec2(0.0) * sys_BlurScale)) * (20.0 / 64.0);
  out_Color += texture(diffuse, uv0 + (vec2(1.0) * sys_BlurScale)) * (15.0 / 64.0);
  out_Color += texture(diffuse, uv0 + (vec2(2.0) * sys_BlurScale)) * (6.0 / 64.0);
  out_Color += texture(diffuse, uv0 + (vec2(3.0) * sys_BlurScale)) * (1.0 / 64.0);
}
)"
