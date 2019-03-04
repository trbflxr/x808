layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec2 uv;

out vec2 v_uv0;
out vec3 v_normal0;
out vec3 v_tangent0;
out vec4 v_position0;
out vec3 v_worldPosition0;

uniform mat4 model;

void main() {
  vec4 p = vec4(position, 1.0);
  vec4 n = vec4(normal, 0.0);
  vec4 t = vec4(tangent, 0.0);

  v_uv0 = uv;
  v_normal0 = normalize((model * n).xyz);
  v_tangent0 = normalize((model * t).xyz);
  v_worldPosition0 = (model * p).xyz;
  v_position0 = (projection * view * model) * p;
}
