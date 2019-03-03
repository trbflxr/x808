layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec2 uv;

out vec2 uv0;
out vec3 normal0;
out vec3 tangent0;
out vec4 position0;
out vec3 viewPosition0;
out vec3 worldPosition0;

uniform mat4 model;

void main() {
  vec4 p = vec4(position, 1.0);
  vec4 n = vec4(normal, 0.0);
  vec4 t = vec4(tangent, 0.0);

  uv0 = uv;
  normal0 = normalize((model * n).xyz);
  tangent0 = normalize((model * t).xyz);
  position0 = (projection * view * model) * p;
  worldPosition0 = (model * p).xyz;
  viewPosition0 = (view * p).xyz;

  gl_Position = position0;
}
