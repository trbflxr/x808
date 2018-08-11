R"(
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;

out vec2 uv0;
out mat3 tbnMat0;
out vec3 worldPos0;
out vec4 shadowMapUV0;

uniform mat4 model;
uniform mat4 MVP;
uniform mat4 lightMat;

void main() {
  gl_Position = MVP * position;
  uv0 = uv;
  shadowMapUV0 = lightMat * position;
  worldPos0 = (model * position).xyz;

  vec3 n = normalize((model * vec4(normal, 0.0)).xyz);
  vec3 t = normalize((model * vec4(tangent, 0.0)).xyz);
  t = normalize(t - dot(t, n) * n);
  vec3 bitangent = cross(t, n);

  tbnMat0 = mat3(t, bitangent, n);
}
)"
