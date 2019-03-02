layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec2 uv;

uniform mat4 model;

out vec3 position0;
out vec3 normal0;
out vec2 uv0;
out mat3 tbn0;

void main() {
  gl_Position = (projection * view * model) * vec4(position, 1.0);

  position0 = vec3(view * model * vec4(position, 1.0));
  normal0 = mat3(transpose(inverse(view * model))) * normal;
  uv0 = uv;

  vec3 T = normalize(vec3(view * model * vec4(tangent.xyz, 0.0)));
  vec3 B = normalize(vec3(view * model * vec4(tangent.xyz, 0.0)));
  vec3 N = normalize(vec3(view * model * vec4(normal, 0.0)));
  tbn0 = mat3(T, B, N);
}
