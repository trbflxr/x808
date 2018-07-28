R"(
#shader vertex
#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;

out vec2 uv0;
out mat3 tbnMat0;
out vec3 worldPos0;

uniform mat4 sys_Model;
uniform mat4 sys_MVP;

void main() {
  gl_Position = sys_MVP * position;
  uv0 = uv;
  worldPos0 = (sys_Model * position).xyz;

  vec3 n = normalize((sys_Model * vec4(normal, 0.0)).xyz);
  vec3 t = normalize((sys_Model * vec4(tangent, 0.0)).xyz);
  t = normalize(t - dot(t, n) * n);
  vec3 bitangent = cross(t, n);

  tbnMat0 = mat3(t, bitangent, n);
}
)"
