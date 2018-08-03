R"(
#shader vertex
#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;

out vec2 uv0;

uniform mat4 sys_MVP;

void main() {
  gl_Position = sys_MVP * position;
  uv0 = vec2(uv.x, 1.0 - uv.y);
}

#shader fragment
#version 330

in vec2 uv0;

out vec4 out_Color;

uniform sampler2D diffuse;

void main() {
    out_Color = texture(diffuse, uv0);
}
)"
