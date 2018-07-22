R"(
#shader vertex
#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

out vec2 uv0;
out vec3 normal0;
out vec3 worldPos0;

uniform mat4 sys_Model;
uniform mat4 sys_MVP;

void main() {
  gl_Position = sys_MVP * position;
  uv0 = uv;
  worldPos0 = (sys_Model * position).xyz;
  normal0 = normalize((sys_Model * vec4(normal, 0.0)).xyz);
}
)"
