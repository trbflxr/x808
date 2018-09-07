layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec2 uv;

out vec3 vWorldPosition0;
out vec2 vUV0;
out vec3 vNormal0;
out vec3 vTangent0;

uniform mat4 model;

void main() {
  vec4 vPos = vec4(position, 1.0);
  vec4 vNormal = vec4(normal, 0.0);
  vec4 vTangent = vec4(tangent, 0.0);

  vWorldPosition0 = (model * vPos).xyz;
  vUV0 = uv;
  vNormal0 = normalize((model * vNormal).xyz);
  vTangent0 = normalize((model * vTangent).xyz);
}
